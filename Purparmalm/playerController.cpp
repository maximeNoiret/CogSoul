#include "types.h"
#include "playerController.h"
#include "terminalManagement.h"
#include "mapManagement.h"
#include <cctype>
#include <iostream>

using namespace std;


void moveToken (mapGrid & Mat, const char& move, playerInfo& player) {
    char currPlayer = Mat[player.pos.first][player.pos.second];
    Mat[player.pos.first][player.pos.second] = KEmpty;
    switch (tolower(move)) {
    case 'z':
        if (player.pos.first > 0 && Mat[player.pos.first - 1][player.pos.second] != '#') {
            --player.pos.first;
            ++player.steps;
        }
        break;
    case 'q':
        if (player.pos.second > 0 && Mat[player.pos.first][player.pos.second - 1] != '#') {
            --player.pos.second;
            ++player.steps;
        }
        break;
    case 's':
        if (player.pos.first < Mat.size()-1 && Mat[player.pos.first + 1][player.pos.second] != '#') {
            ++player.pos.first;
            ++player.steps;
        }
        break;
    case 'd':
        if (player.pos.second < Mat[player.pos.first].size()-1 && Mat[player.pos.first][player.pos.second + 1] != '#') {
            ++player.pos.second;
            ++player.steps;
        }
        break;
    }
    Mat[player.pos.first][player.pos.second] = currPlayer;
}


