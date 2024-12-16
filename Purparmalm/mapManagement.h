#ifndef MAPMANAGEMENT_H
#define MAPMANAGEMENT_H

#include <string>
#include "types.h"

/**
 * @brief Places a map from a text file into a mapGrid object
 * @param[in out] roomGrid : a mapGrid object that will store the map from the file
 * @param[in] fileName : the path of the file that contains the map
 */
void loadMapFromFile(mapGrid& roomGrid, const std::string& fileName);

/**
 * @brief Places a room in the map at coordinates x y
 * @param[in out] gameGrid : a mapGrid object that has the entire map
 * @param[in] roomGrid : a mapGrid object that only has the room
 * @param[in] x : x position of upper left of the room in the map
 * @param[in] y : y position of upper left of the room in the map
 * @return 0 if everything went alright, 2 if the room is too tall (y), 3 if the room is too large (x)
 */
int placeRoom(mapGrid& gameGrid, const mapGrid& roomGrid, const size_t& x, const size_t& y);

/**
 * @brief calls loadMapFromFile and placeRoom. Merely a QoL function.
 * @param[in out] gameGrid : a mapGrid object that has the entire map
 * @param[in] fileName : the path of the file that contains the map
 * @param[in] x : x position of upper left of the room in the map
 * @param[in] y : y position of upper left of the room in the map
 * @return same as placeRoom: 0 if everything went alright, 2 if room is too tall (y), 3 if room is too large(x)
 */
int loadAndPlace(mapGrid& gameGrid, const std::string& fileName, const size_t& x, const size_t y);

#endif // MAPMANAGEMENT_H
