#ifndef TERMINALMANAGEMENT_H
#define TERMINALMANAGEMENT_H

#include "types.h"


void reset_input_mode();
void set_input_mode();

void milSleep(const unsigned& milliseconds);

void clearScreen();

void color (const unsigned & col);


void centerOut(const std::string& out);

void renderMainMenu();


/**
 * @brief displays an interactive Main Menu with options to play or go into settings
 * @return the selected option (New Game, Settings, Exit)
 */
unsigned short mainMenu(const settings& config);


void helpMenu(const settings& config);

/**
 * @brief Lets the user input their name in an interactive way
 * @return the name from the user
 */
std::string inputName();

/**
 * @brief generateRender
 * @param[in] gameMap : mapGrid object containing the entire map
 * @param[in] renderDist : unsigned defining render distance
 * @param[in] playerPos : position of the player
 */
/**
 * @brief Generates a render containing the viewport of the game as well as information under it
 * @param[in] gameMap : mapGrid object containing the entire map
 * @param[in] renderDist : render distance (not changeable by user and is 10 by default)
 * @param[in] player : playerInfo object with information about the player (pos)
 * @param[in] config : settings of the game
 */
void generateRender(const mapGrid& gameMap, const unsigned& renderDist, const playerInfo player, const settings& config, std::vector<enemyInfo>& enemies);


void introSequence(const mapGrid& gameMap, const playerInfo& player, const settings& config, std::vector<enemyInfo>& enemies);

#endif // TERMINALMANAGEMENT_H
