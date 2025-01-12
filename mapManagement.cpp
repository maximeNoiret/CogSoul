/**
 * @author Noiret Maxime
 */

#include <iostream>
#include <vector>
#include <fstream>
#include "types.h"
#include "mapManagement.h"

using namespace std;

mapGrid loadMapFromFile(const string& fileName, const settings& config) {
    mapGrid roomGrid;
    ifstream mapFile (fileName);
    if (!mapFile.good()) {
        cerr << "Couldn't access map file! (" << fileName << ")" << endl;
        exit(2);
    }
    size_t height;
    mapFile >> height;
    size_t width;
    mapFile >> width;
    string input;
    getline(mapFile, input);  // gets rid of doors info
    roomGrid.assign(height, mapLine (width, config.KEmpty));
    for (mapGrid::iterator iter = roomGrid.begin(); iter != roomGrid.end() && getline(mapFile, input); ++iter) {
        size_t tmpIndex = 0;
        for (mapLine::iterator subIter = iter->begin(); subIter != iter->end() && tmpIndex < input.size(); ++subIter) {
            if (input[tmpIndex] == '\n') continue;
            *subIter = (input[tmpIndex] == ' ' ? config.KEmpty : input[tmpIndex]);
            ++tmpIndex;
        }
    }
    mapFile.close();
    return roomGrid;
}


// WTF is this FUCKING CURSED ASS SHITTY function???
// look at ALL THESE PARAMETERS like WTF??? We're not in FUCKING PYTHON you IDIOT
int placeRoom(mapGrid& gameGrid, const mapGrid& roomGrid, const size_t& x, const size_t& y, const bool& isUniverse, const char& enemyToken, vector<enemyInfo>& enemies) {
    if (roomGrid.size() + y > gameGrid.size()) return 2;
    if (roomGrid[0].size() + x > gameGrid[0].size()) return 3;
    // check for other rooms
    mapGrid::iterator mapIter = gameGrid.begin() + y + 1;
    if (!isUniverse) {
        for(mapLine::iterator mapLineIter = mapIter->begin() + x + 1;
             mapIter < gameGrid.begin() + y + roomGrid.size() - 1 && *mapLineIter != '#';
             ++mapIter) {
            mapLineIter = mapIter->begin() + x + 1;
            for (;mapLineIter < mapIter->begin() + x + roomGrid[0].size() - 2 && *mapLineIter != '#'; ++mapLineIter);
        }

        if (mapIter < gameGrid.begin() + y + roomGrid.size() - 1) return 4;
    }


    mapIter = gameGrid.begin() + y;
    CPosition potEnemy = {y, x};
    for (const mapLine& lin : roomGrid) {
        mapLine::iterator mapLineIter = mapIter->begin() + x;
        for (const char& car : lin) {
            if (*mapLineIter != '#') *mapLineIter = car;
            if (!isUniverse && *mapLineIter == 'O') {
                *mapLineIter = enemyToken;
                enemies.push_back({CPosition (potEnemy.first, potEnemy.second), false});
            }
            ++mapLineIter;
            ++potEnemy.second;
        }
        ++mapIter;
        potEnemy.second = x;
        ++potEnemy.first;
    }
    return 0;
}


int loadAndPlace(mapGrid& gameGrid, const string& fileName, const size_t& x, const size_t y, const settings& config, vector<enemyInfo>& enemies) {
    mapGrid roomGrid;
    roomGrid = loadMapFromFile(fileName, config);
    return placeRoom(gameGrid, roomGrid, x, y, false, config.KTokenEnemy, enemies);
}

template<typename T>
bool isInVect(const vector<T>& vect, const T elem) {
    typename vector<T>::const_iterator iter = vect.begin();
    for (;iter < vect.end() && *iter != elem;++iter);
    return !(iter == vect.end());
}



void generateRoom(mapGrid& gameGrid, const char& desiredDoor, const CPosition& pos, const settings& config, vector<enemyInfo>& enemies) {
    // Select a random room for the desired direction
    vector<string> blacklistedMaps;
    char desiredDirection;
    bool cannotPlace = false;
    // attempt to place room until able to (or not)
    for(;;) {
        string fileName = "rooms/";
        switch (desiredDoor) {
            case '1':
                if (blacklistedMaps.size() == roomsUp.size()){
                    cannotPlace = true;
                    break;
                }
                fileName += roomsUp[rand() % roomsUp.size()];
                desiredDirection = 'u';
                break;
            case '2':
                if (blacklistedMaps.size() == roomsRight.size()) {
                    cannotPlace = true;
                    break;
                }
                fileName += roomsRight[rand() % roomsRight.size()];
                desiredDirection = 'r';
                break;
            case '3':
                if (blacklistedMaps.size() == roomsDown.size()) {
                    cannotPlace = true;
                    break;
                }
                fileName += roomsDown[rand() % roomsDown.size()];
                desiredDirection = 'd';
                break;
            case '4':
                if (blacklistedMaps.size() == roomsLeft.size()) {
                    cannotPlace = true;
                    break;
                }
                fileName += roomsLeft[rand() % roomsLeft.size()];
                desiredDirection = 'l';
                break;
        };

        if (cannotPlace) break;

        if (isInVect(blacklistedMaps, fileName)) continue;

        // Calculate position of the room in gameGrid with door metadata in file
        ifstream tmpFile (fileName);
        if (!tmpFile.good()) {
            cerr << "Couldn't access map file! (" << fileName << ")" << endl;
            exit(2);
        }
        for (; tmpFile.get() != desiredDirection && tmpFile.peek() != tmpFile.eof(););  // get to desired door metadata
        size_t y;
        tmpFile >> y;  // get door y position relative to room origin
        size_t x;
        tmpFile >> x;  // get door x position relative to room origin
        CPosition roomOrigin = {pos.first - y, pos.second - x};
        if (loadAndPlace(gameGrid, fileName, roomOrigin.second, roomOrigin.first, config, enemies) == 0) break;
        blacklistedMaps.push_back(fileName);  // avoid trying again to place down a map that didn't work once
    }
    // if couldn't place a room, place a wall instead lmao get rekt nob
    if (cannotPlace) {
        // BIG potential for edge cases overflows lmao (get it? edge case? nvm)
        switch (desiredDoor) {
            case '1':
                //moveToken(gameGrid, 's', pos);
                gameGrid[pos.first - 1][pos.second]     = '#';
                gameGrid[pos.first - 1][pos.second + 1] = '#';
                gameGrid[pos.first - 1][pos.second - 1] = '#';
                break;
            case '2':
                gameGrid[pos.first][pos.second + 1]     = '#';
                gameGrid[pos.first + 1][pos.second + 1] = '#';
                gameGrid[pos.first - 1][pos.second + 1] = '#';
                break;
            case '3':
                gameGrid[pos.first + 1][pos.second]     = '#';
                gameGrid[pos.first + 1][pos.second + 1] = '#';
                gameGrid[pos.first + 1][pos.second - 1] = '#';
                break;
            case '4':
                gameGrid[pos.first][pos.second - 1]     = '#';
                gameGrid[pos.first + 1][pos.second - 1] = '#';
                gameGrid[pos.first - 1][pos.second - 1] = '#';
                break;
        };
    }
    else {
        Logs::addLog("Analyzing room...");
    }
}


