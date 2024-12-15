#ifndef TERMINALMANAGEMENT_H
#define TERMINALMANAGEMENT_H

#include <vector>
#include "types.h"

/**
 * @brief Prints a vector of characters. ToDo: generalize function
 * @param[in] vect
 */
void printVect(const std::vector<char>& vect);

/**
 * @brief Prints a mapGrid object. ToDo: generalize function
 * @param[in] gameMap : a mapGrid object, usually the one that contains the entire map
 */
void printGrid(const mapGrid& gameMap);

#endif // TERMINALMANAGEMENT_H
