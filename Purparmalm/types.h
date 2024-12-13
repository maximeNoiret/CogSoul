#ifndef TYPES_H
#define TYPES_H

#include <vector>

/**
 * @brief a vector of characters, representing a line of the map.
 */
typedef std::vector<char> mapLine;

/**
 * @brief a vector of mapLine, representing the game board/map
 */
typedef std::vector<mapLine> mapGrid;

#endif // TYPES_H
