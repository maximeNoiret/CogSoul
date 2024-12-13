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
 * @brief Prints a mapGrid object. ToDo: generalize function (again lol)
 * @param[in] gameMap
 */
void printGrid(const mapGrid& gameMap);

#endif // TERMINALMANAGEMENT_H
