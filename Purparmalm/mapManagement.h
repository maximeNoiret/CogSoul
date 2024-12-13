#ifndef MAPMANAGEMENT_H
#define MAPMANAGEMENT_H

#include <string>
#include "types.h"

/**
 * @brief Places a map from a text file into a mapGrid object
 * @param[in out] gameMap
 * @param[in] fileName
 */
void loadMapFromFile(mapGrid& gameMap, const std::string& fileName);


#endif // MAPMANAGEMENT_H
