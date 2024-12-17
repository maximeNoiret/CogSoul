#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include "types.h"

/**
 * @brief moveToken
 * @param[in out] Mat : mapGrid object containing the entire map
 * @param[in] move : character representing entity's move
 * @param[in out] player : playerInfo object with info about the player
 */
void moveToken (mapGrid & Mat, const char& move, playerInfo& player);




#endif // PLAYERCONTROLLER_H
