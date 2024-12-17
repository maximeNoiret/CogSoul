#include <iostream>
#include <vector>
#include <fstream>
#include "types.h"
#include "mapManagement.h"

using namespace std;

void loadMapFromFile(mapGrid& roomGrid, const string& fileName) {
    ifstream mapFile (fileName);
    if (!mapFile.good()) {
        cerr << "Couldn't access map file! (" << fileName << ")" << endl;
        exit(2);
    }
    size_t height;
    mapFile >> height;
    size_t width;
    mapFile >> width;
    mapFile.get();  // gets rid of newline
    roomGrid.assign(height, mapLine (width, KEmpty));
    string input;
    for (mapGrid::iterator iter = roomGrid.begin(); iter != roomGrid.end() && getline(mapFile, input); ++iter) {
        size_t tmpIndex = 0;
        for (mapLine::iterator subIter = iter->begin(); subIter != iter->end() && tmpIndex < input.size(); ++subIter) {
            if (input[tmpIndex] == '\n') continue;
            *subIter = (input[tmpIndex] == ' ' ? KEmpty : input[tmpIndex]);
            ++tmpIndex;
        }
    }
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
            if (*mapLineIter != '#') *mapLineIter = car;
            ++mapLineIter;
        }
        ++mapIter;
    }
    return 0;
}


int loadAndPlace(mapGrid& gameGrid, const string& fileName, const size_t& x, const size_t y) {
    mapGrid roomGrid;
    loadMapFromFile(roomGrid, fileName);
    return placeRoom(gameGrid, roomGrid, x, y);
}
