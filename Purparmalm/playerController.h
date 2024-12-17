#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include "types.h"

/**
 * @brief moveToken
 * @param[in out] Mat : mapGrid object containing the entire map
 * @param[in] move : character representing entity's move
 * @param[in out] pos : position of the entity
 */
void moveToken (mapGrid & Mat, const char& move, CPosition & pos);

void generateRender(const mapGrid& gameMap, const unsigned& renderDist, const CPosition& playerPos);


#endif // PLAYERCONTROLLER_H
