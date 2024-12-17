#include "types.h"
#include "playerController.h"
#include "terminalManagement.h"
#include "mapManagement.h"
#include <cctype>
#include <iostream>

using namespace std;


void moveToken (mapGrid & Mat, const char& move, CPosition & pos) {
    char currPlayer = Mat[pos.first][pos.second];
    Mat[pos.first][pos.second] = KEmpty;
    switch (tolower(move)) {
    case 'z':
        if (pos.first > 0 && Mat[pos.first - 1][pos.second] != '#') pos.first -= 1;
        break;
    case 'q':
        if (pos.second > 0 && Mat[pos.first][pos.second - 1] != '#') pos.second -= 1;
        break;
    case 's':
        if (pos.first < Mat.size()-1 && Mat[pos.first + 1][pos.second] != '#') pos.first += 1;
        break;
    case 'd':
        if (pos.second < Mat[pos.first].size()-1 && Mat[pos.first][pos.second + 1] != '#') pos.second += 1;
        break;
    }
    Mat[pos.first][pos.second] = currPlayer;
}

void generateRender(const mapGrid& gameMap, const unsigned& renderDist, const CPosition& playerPos) {
    mapGrid universe (gameMap.size()+ 2 * renderDist, mapLine (gameMap[0].size()+ 2 * renderDist, ' '));
    placeRoom(universe, gameMap, renderDist, renderDist);
    CPosition upperLeft = {(playerPos.first + renderDist) - renderDist, (playerPos.second + renderDist) - renderDist};
    CPosition bottomRight = {(playerPos.first + renderDist) + renderDist, (playerPos.second + renderDist) + renderDist};
    for (mapGrid::const_iterator iter = universe.begin() + upperLeft.first;
         iter < universe.begin() + bottomRight.first;
         ++iter) {
        for (mapLine::const_iterator subIter = iter->begin() + upperLeft.second;
             subIter < iter->begin() + bottomRight.second;
             ++subIter) {
            cout << *subIter;
        }
        cout << endl;
    }
}
