/**
 * @author Noiret Maxime
 */

#ifndef SETTINGSMANAGEMENT_H
#define SETTINGSMANAGEMENT_H

#include "types.h"

/**
 * @brief displays an interactive menu to modify the settings of the game
 * @param[in out] config : settings object that contains the different settings
 */
void settingsMenu(settings& config);


/**
 * @brief loads settings from a config file if it exists, creates one with default values if not
 * @param[in out] config : settings object that contains the different settings
 */
void initSettings(settings& config);

#endif // SETTINGSMANAGEMENT_H
