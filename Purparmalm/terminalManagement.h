#ifndef TERMINALMANAGEMENT_H
#define TERMINALMANAGEMENT_H

#include <vector>
#include "types.h"


void reset_input_mode();
void set_input_mode();


void clearScreen();

void color (const unsigned & col);


void centerOut(const std::string& out);

void renderMainMenu();

unsigned short mainMenu();

std::string inputName();

/**
 * @brief Prints a vector of characters. ToDo: generalize function
 * @param[in] vect
 */
void printVect(const std::vector<char>& vect);

/**
 * @brief generateRender
 * @param[in] gameMap : mapGrid object containing the entire map
 * @param[in] renderDist : unsigned defining render distance
 * @param[in] playerPos : position of the player
 */
void generateRender(const mapGrid& gameMap, const unsigned& renderDist, const playerInfo player, const settings& config);

/**
 * @brief Prints a mapGrid object. ToDo: generalize function
 * @param[in] gameMap : a mapGrid object, usually the one that contains the entire map
 */
void printGrid(const mapGrid& gameMap);

#endif // TERMINALMANAGEMENT_H
