#include <iostream>
#include <vector>
#include <fstream>
#include "types.h"
#include "mapManagement.h"
#include "terminalManagement.h"

using namespace std;

void loadMapFromFile(mapGrid& gameMap, const string& fileName) {
    ifstream mapFile (fileName);
    if (!mapFile.good()) {
        cerr << "Couldn't access map file!" << endl;
        exit(2);
    }
    size_t height;
    mapFile >> height;
    size_t width;
    mapFile >> width;
    mapFile.get();  // gets rid of newline
    gameMap.resize(height, mapLine (width, ' '));
    string input;
    for (mapGrid::iterator iter = gameMap.begin(); iter != gameMap.end() && getline(mapFile, input); ++iter) {
        size_t tmpIndex = 0;
        for (mapLine::iterator subIter = iter->begin(); subIter != iter->end() && tmpIndex < input.size(); ++subIter) {
            if (input[tmpIndex] == '\n') continue;
            *subIter = input[tmpIndex];
            ++tmpIndex;
        }
    }
    printGrid(gameMap);
}

// ToDo: add a map building process that uses a seed to procedurally generate a map out of rooms.

int placeRoom(mapGrid& gameGrid, const mapGrid& roomGrid, const size_t& x, const size_t& y) {
    if (roomGrid.size() + y > gameGrid.size()) return 2;
    if (roomGrid[0].size() + x > gameGrid[0].size()) return 3;
    // bool finishedBuilding = false;
    mapGrid::iterator mapIter = gameGrid.begin() + y;

    for (const mapLine& lin : roomGrid) {
        mapLine::iterator mapLineIter = mapIter->begin() + x;
        for (const char& car : lin) {
            *mapLineIter = car;
            ++mapLineIter;
        }
        ++mapIter;
    }
    return 0;
}
