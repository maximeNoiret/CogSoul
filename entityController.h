/**
 * @author Noiret Maxime
 */

#ifndef ENTITYCONTROLLER_H
#define ENTITYCONTROLLER_H

#include <vector>
#include "types.h"


/**
 * @brief moveToken
 * @param[in out] Mat : mapGrid object containing the entire map
 * @param[in] move : character representing entity's move
 * @param[in out] pos : a CPosition object containing an x and y value
 * @param[in] config : settings of the game
 */
void moveToken (mapGrid & Mat, const char& move, CPosition& pos, const settings& config, std::vector<enemyInfo>& enemies);

/**
 * @brief moves every enemies. If one sees the player, it will move towards them, else it will move randomly.
 * @param[in out] gameMap : mapGrid object containing the entire map
 * @param[in out] player : playerInfo object with info about the player
 * @param[in out] enemies : vector containing enemyInfo objects with info about enemies
 * @param[in] config : settings of the game
 */
void moveEnemies(mapGrid& gameMap, playerInfo& player, std::vector<enemyInfo>& enemies, const settings& config);

/**
 * @brief ROUGHLY checks if a wall is present between two positions.
 * @param[in out] Mat : mapGrid object containing the entire map
 * @param[in] pos1 : position from which to begin checking
 * @param[in] pos2 : goal position to check if a wall is between
 * @return true if a wall is present between the two positions, false otherwise
 */
bool isWallBetween(const mapGrid& Mat, const CPosition& pos1, const CPosition& pos2);

/**
 * @brief checks if any enemy can see the player. Takes into account walls (refer to isWallBetween)
 * @param[in] Mat : mapGrid object containing the entire map
 * @param[in out] enemies : vector containing enemyInfo objects with info about enemies
 * @param[in] player : playerInfo object containing info about the player
 * @param[in] config : settings of the game
 * @return true if an enemy can see the player, false otherwise
 */
bool isPlayerSeen(const mapGrid& Mat, std::vector<enemyInfo>& enemies, const playerInfo& player, const settings& config);


#endif // ENTITYCONTROLLER_H
