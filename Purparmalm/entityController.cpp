#include "types.h"
#include "entityController.h"
#include "terminalManagement.h"
#include "mapManagement.h"
#include <cctype>
#include <iostream>

using namespace std;


void moveToken (mapGrid & Mat, const char& move, CPosition& pos) {
    char currPlayer = Mat[pos.first][pos.second];
    Mat[pos.first][pos.second] = KEmpty;
    switch (tolower(move)) {
    case 'z':
        if (pos.first > 0 &&
            Mat[pos.first - 1][pos.second] != '#' &&
            Mat[pos.first - 1][pos.second] != KTokenEnemy) {
            --pos.first;
        }
        break;
    case 'q':
        if (pos.second > 0 &&
            Mat[pos.first][pos.second - 1] != '#' &&
            Mat[pos.first][pos.second - 1] != KTokenEnemy) {
            --pos.second;
        }
        break;
    case 's':
        if (pos.first < Mat.size()-1 &&
            Mat[pos.first + 1][pos.second] != '#' &&
            Mat[pos.first + 1][pos.second] != KTokenEnemy) {
            ++pos.first;
        }
        break;
    case 'd':
        if (pos.second < Mat[pos.first].size()-1 &&
            Mat[pos.first][pos.second + 1] != '#' &&
            Mat[pos.first][pos.second + 1] != KTokenEnemy) {
            ++pos.second;
        }
        break;
    }
    Mat[pos.first][pos.second] = currPlayer;
}

// I FUCKING hate this :) PLEASE FIND A WAY TO OPTIMIZE IT I HATE IT I HATE IT I HATE IT
void moveEnemies(mapGrid& gameMap, playerInfo& player, vector<enemyInfo>& enemies) {
    for (enemyInfo& enemy : enemies) {
        char move;
        if (enemy.sees) {
            if (enemy.pos.first < player.pos.first) {
                if (enemy.pos.second < player.pos.second) {
                    if (player.pos.first - enemy.pos.first < player.pos.second - enemy.pos.second)
                        move = 'd';
                    else
                        move = 's';
                } else if (enemy.pos.second > player.pos.second) {
                    if (player.pos.first - enemy.pos.first < enemy.pos.second - player.pos.second)
                        move= 'q';
                    else
                        move = 's';
                } else
                    move = 's';
            } else if (enemy.pos.first > player.pos.first) {
                if (enemy.pos.second < player.pos.second) {
                    if (enemy.pos.first - player.pos.first < player.pos.second - enemy.pos.second)
                        move = 'd';
                    else
                        move = 'z';
                } else if (enemy.pos.second > player.pos.second) {
                    if (enemy.pos.first - player.pos.first < enemy.pos.second - player.pos.second)
                        move= 'q';
                    else
                        move = 'z';
                } else
                    move = 'z';
            } else if (enemy.pos.second < player.pos.second) move = 'd';
            else if (enemy.pos.second > player.pos.second) move = 'q';
        }else
            move = possibleMoves[rand() % 5];
        moveToken(gameMap, move, enemy.pos);
        if (player.pos == enemy.pos)
            player.dead = true;
    }
}

bool isWallBetween(const mapGrid& Mat, const CPosition& pos1, const CPosition& pos2) {
    CPosition currentPoint = pos1;
    bool isWall = false;
    for (;!isWall && currentPoint != pos2;) {
        if (currentPoint.first < pos2.first) ++currentPoint.first;
        else if (currentPoint.first > pos2.first) --currentPoint.first;
        if (Mat[currentPoint.first][currentPoint.second] == '#') isWall = true;
        if (currentPoint.second < pos2.second) ++currentPoint.second;
        else if (currentPoint.second > pos2.second) --currentPoint.second;
        if (Mat[currentPoint.first][currentPoint.second] == '#') isWall = true;
    }
    return isWall;
}

bool isPlayerSeen(const mapGrid& Mat, vector<enemyInfo>& enemies, const playerInfo& player) {
    unsigned radius = 2;
    mapGrid universe (Mat.size()+ 2 * radius, mapLine (Mat[0].size()+ 2 * radius, ' '));
    placeRoom(universe, Mat, radius, radius);
    bool found = false;
    for (vector<enemyInfo>::iterator enemyIter = enemies.begin(); enemyIter < enemies.end() && !found; ++enemyIter) {
        const CPosition upperLeft = {enemyIter->pos.first, enemyIter->pos.second};
        const CPosition bottomRight = {enemyIter->pos.first + 2 * radius + 1, enemyIter->pos.second + 2 * radius + 1};
        // check around it in a certain radius
        for (mapGrid::const_iterator iter = universe.begin() + upperLeft.first;
             iter < universe.begin() + bottomRight.first && !found;
             ++iter)
            for (mapLine::const_iterator subIter = iter->begin() + upperLeft.second;
                 subIter < iter->begin() + bottomRight.second && !found;
                 ++subIter)
                if (*subIter == KTokenPlayer1) {
                    if (!isWallBetween(Mat, enemyIter->pos, player.pos)) {
                        found = true;
                        enemyIter->sees = true;
                    }
                }
        if (!found) enemyIter->sees = false;
    }
    return found;
}


