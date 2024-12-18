#ifndef ENTITYCONTROLLER_H
#define ENTITYCONTROLLER_H

#include <vector>
#include "types.h"

/**
 * @brief moveToken
 * @param[in out] Mat : mapGrid object containing the entire map
 * @param[in] move : character representing entity's move
 * @param[in out] player : playerInfo object with info about the player
 */
void moveToken (mapGrid & Mat, const char& move, CPosition& pos);

void moveEnemies(mapGrid& gameMap, playerInfo& player, std::vector<enemyInfo>& enemies);

bool isWallBetween(const mapGrid& Mat, const CPosition& pos1, const CPosition& pos2);

bool isPlayerSeen(const mapGrid& Mat, std::vector<enemyInfo>& enemies, const playerInfo& player);


#endif // ENTITYCONTROLLER_H
