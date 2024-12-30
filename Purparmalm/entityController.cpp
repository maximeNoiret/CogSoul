#include "types.h"
#include "entityController.h"
#include "mapManagement.h"
#include <cctype>

using namespace std;


void moveToken (mapGrid & Mat, const char& move, CPosition& pos, const settings& config) {
    char currPlayer = Mat[pos.first][pos.second];
    Mat[pos.first][pos.second] = config.KEmpty;
    switch (tolower(move)) {
    case 'z':
        if (pos.first > 0 &&
            Mat[pos.first - 1][pos.second] != '#' &&
            Mat[pos.first - 1][pos.second] != config.KTokenEnemy) {
            --pos.first;
        }
        if (currPlayer == config.KTokenPlayer1) Logs::addLog("Moving up.");
        break;
    case 'q':
        if (pos.second > 0 &&
            Mat[pos.first][pos.second - 1] != '#' &&
            Mat[pos.first][pos.second - 1] != config.KTokenEnemy) {
            --pos.second;
        }
        if (currPlayer == config.KTokenPlayer1) Logs::addLog("Moving left.");
        break;
    case 's':
        if (pos.first < Mat.size()-1 &&
            Mat[pos.first + 1][pos.second] != '#' &&
            Mat[pos.first + 1][pos.second] != config.KTokenEnemy) {
            ++pos.first;
        }
        if (currPlayer == config.KTokenPlayer1) Logs::addLog("Moving down.");
        break;
    case 'd':
        if (pos.second < Mat[pos.first].size()-1 &&
            Mat[pos.first][pos.second + 1] != '#' &&
            Mat[pos.first][pos.second + 1] != config.KTokenEnemy) {
            ++pos.second;
        }
        if (currPlayer == config.KTokenPlayer1) Logs::addLog("Moving right.");
        break;
    }
    // if player moves on a door
    if (currPlayer == config.KTokenPlayer1 &&
        (Mat[pos.first][pos.second] == '1' ||
         Mat[pos.first][pos.second] == '2' ||
         Mat[pos.first][pos.second] == '3' ||
         Mat[pos.first][pos.second] == '4'))
        generateRoom(Mat, Mat[pos.first][pos.second], pos, config);
    Mat[pos.first][pos.second] = currPlayer;
} // moveToken

// I FUCKING hate this :) PLEASE FIND A WAY TO OPTIMIZE IT I HATE IT I HATE IT I HATE IT
// Considering letting enemies go diagonally, making the game MUCH harder when seen (good) and making this PIECE OF SHIT code better (good)
//     Will contact team about it and ask their opinion on it.
void moveEnemies(mapGrid& gameMap, playerInfo& player, vector<enemyInfo>& enemies, const settings& config) {
    for (enemyInfo& enemy : enemies) {
        char move;
        if (enemy.sees) {
            if (enemy.pos.first < player.pos.first) {
                if (enemy.pos.second < player.pos.second) {
                    if (player.pos.first - enemy.pos.first < player.pos.second - enemy.pos.second &&
                        gameMap[enemy.pos.first][enemy.pos.second + 1] != '#')
                        move = 'd';
                    else
                        move = 's';
                } else if (enemy.pos.second > player.pos.second) {
                    if (player.pos.first - enemy.pos.first < enemy.pos.second - player.pos.second &&
                        gameMap[enemy.pos.first][enemy.pos.second - 1] != '#')
                        move= 'q';
                    else
                        move = 's';
                } else
                    move = 's';
            } else if (enemy.pos.first > player.pos.first) {
                if (enemy.pos.second < player.pos.second) {
                    if (enemy.pos.first - player.pos.first < player.pos.second - enemy.pos.second &&
                        gameMap[enemy.pos.first][enemy.pos.second + 1] != '#')
                        move = 'd';
                    else
                        move = 'z';
                } else if (enemy.pos.second > player.pos.second) {
                    if (enemy.pos.first - player.pos.first < enemy.pos.second - player.pos.second &&
                        gameMap[enemy.pos.first][enemy.pos.second - 1] != '#')
                        move= 'q';
                    else
                        move = 'z';
                } else
                    move = 'z';
            } else if (enemy.pos.second < player.pos.second) move = 'd';
            else if (enemy.pos.second > player.pos.second) move = 'q';
        }else move = possibleMoves[rand() % 5];
        moveToken(gameMap, move, enemy.pos, config);
        if (player.pos == enemy.pos)
            player.dead = true;
    }
} // moveEnemies

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
} // isWallBetween

bool isPlayerSeen(const mapGrid& Mat, vector<enemyInfo>& enemies, const playerInfo& player, const settings& config) {
    unsigned radius = 2;
    mapGrid universe (Mat.size()+ 2 * radius, mapLine (Mat[0].size()+ 2 * radius, ' '));
    placeRoom(universe, Mat, radius, radius, true);
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
                if (*subIter == config.KTokenPlayer1) {
                    if (!isWallBetween(Mat, enemyIter->pos, player.pos)) {
                        found = true;
                        enemyIter->sees = true;
                    }
                }
        if (!found) enemyIter->sees = false;
    }
    return found;
} // isPlayerSeen


