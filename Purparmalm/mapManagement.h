#ifndef MAPMANAGEMENT_H
#define MAPMANAGEMENT_H

#include <string>
#include "types.h"

/**
 * @brief Places a map from a text file into a mapGrid object
 * @param[in] fileName : the path of the file that contains the map
 * @param[in] config : settings of the game
 * @return a mapGrid object containing the map
 */
mapGrid loadMapFromFile(const std::string& fileName, const settings& config);

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
int loadAndPlace(mapGrid& gameGrid, const std::string& fileName, const size_t& x, const size_t y, const settings& config);

/**
 * @brief generates a random room for a desired direction at a specific location
 * @param[in out] gameGrid : a mapGrid object that has the entire map
 * @param[in] desiredDoor : a number that indicates which direction is desired
 * @param[in] pos : position of the door that generates the room
 * @param[in] config : settings of the game
 */
void generateRoom(mapGrid& gameGrid, const char& desiredDoor, const CPosition& pos, const settings& config);

#endif // MAPMANAGEMENT_H
