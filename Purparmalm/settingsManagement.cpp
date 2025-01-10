/**
 * @author Noiret Maxime
 */

#include "settingsManagement.h"
#include "types.h"
#include "terminalManagement.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <unistd.h>

using namespace std;


void trim(string& input) {
    for (string::iterator iter = input.begin(); iter < input.end();)
        if (isspace(*iter)) input.erase(iter);
        else ++iter;
}

void generateConfigFile(const settings& config) {
    ofstream newConfigFile("config.yaml");
    newConfigFile << "# Apperance"                               << '\n'
                  << "KColorEnemy   : " << config.KColorEnemy    << '\n'
                  << "KColorPlayer1 : " << config.KColorPlayer1  << '\n'
                  << "KEmpty        : " << config.KEmpty         << '\n'
                  << "KTokenEnemy   : " << config.KTokenEnemy    << '\n'
                  << "KTokenPlayer1 : " << config.KTokenPlayer1  << '\n'
                  << "KOutBox       : " << config.KOutBox        << '\n'
                  << "# Gameplay"                                << '\n'
                  << "KSkipIntro    : " << config.KSkipIntro     << '\n'
                  << "KSeed         : " << config.KSeed          << '\n'
                  << "# Controls"                                << '\n'
                  << "KMoveUp       : " << config.KMoveUp        << '\n'
                  << "KMoveRight    : " << config.KMoveRight     << '\n'
                  << "KMoveDown     : " << config.KMoveDown      << '\n'
                  << "KMoveLeft     : " << config.KMoveLeft      << '\n'
                  << "KInspect      : " << config.KInspect;

    newConfigFile.close();
}

void initSettings(settings& config) {
    ifstream configFile;
    configFile.open("config.yaml");
    if (!configFile.good()) {
        generateConfigFile(config);
        configFile.close();
        configFile.open("config.yaml");
    }
    map<string, string> configValues;
    for (;;) {
        for(string input;getline(configFile, input);) {
            if (input[0] == '#') continue;  // ignore comments
            trim(input);
            size_t semiColon = input.find(":");
            configValues[input.substr(0, semiColon)] = input.substr(semiColon+1);
        }
        // if config file is not up to date (doesn't have all settings), regenerate it and reload it
        for (const pair<string, string> elem : configValues)
            cout << elem.first << " : " << elem.second << endl;
        if (configValues.size() != 13) {
            cout << "config file incorrect, regenerating..." << endl;
            milSleep(2000);
            generateConfigFile(config);
            configFile.close();
            configFile.open("config.yaml");
        } else break;
    }
    configFile.close();
    // this is ridiculous...
    // Appearance
    config.KColorEnemy = configValues.find("KColorEnemy")->second;
    config.KColorPlayer1 = configValues.find("KColorPlayer1")->second;
    config.KEmpty = configValues.find("KEmpty")->second[0];
    config.KTokenEnemy = configValues.find("KTokenEnemy")->second[0];
    config.KTokenPlayer1 = configValues.find("KTokenPlayer1")->second[0];
    config.KOutBox = stoul(configValues.find("KOutBox")->second);
    // Gameplay
    config.KSkipIntro = (configValues.find("KSkipIntro")->second == "0" ? false : true);
    config.KSeed = configValues.find("KSeed")->second;
    // Controls
    config.KMoveUp = configValues.find("KMoveUp")->second[0];
    config.KMoveRight = configValues.find("KMoveRight")->second[0];
    config.KMoveDown = configValues.find("KMoveDown")->second[0];
    config.KMoveLeft = configValues.find("KMoveLeft")->second[0];
    config.KInspect = configValues.find("KInspect")->second[0];
}

// uh... wtf is this? Monster Energy makes me black out and write code like this????
void renderSettingsMenu(const unsigned short& select, const settings& config){
    clearScreen();
    centerOut("Settings");
    centerOut("If editing config through here is annoying,");
    centerOut("you can edit the config.yaml file next to the executable. lol");
    cout << '\n';
    // Player Character
    cout << left << setw(30) << "Player Character : ";
    color((select == 0 ? Colors.find("Green")->second : Colors.find("Reset")->second));
    cout << config.KTokenPlayer1 << "   ";
    cout << '\n';
    color(Colors.find("Reset")->second);
    // Player Color
    cout << left << setw(30) << "Player Color : ";
    color((select == 1 ? Colors.find("Green")->second : Colors.find("Reset")->second));
    cout << config.KColorPlayer1 << endl;
    color(Colors.find("Reset")->second);
    // Enemy Character
    cout << left << setw(30) << "Enemy Character : ";
    color((select == 2 ? Colors.find("Green")->second : Colors.find("Reset")->second));
    cout << config.KTokenEnemy << "   ";
    cout << '\n';
    color(Colors.find("Reset")->second);
    // Enemy Color
    cout << left << setw(30) << "Enemy Color : ";
    color((select == 3 ? Colors.find("Green")->second : Colors.find("Reset")->second));
    cout << config.KColorEnemy << endl;
    color(Colors.find("Reset")->second);
    // Empty Character
    cout << left << setw(30) << "Empty Character : ";
    color((select == 4 ? Colors.find("Green")->second : Colors.find("Reset")->second));
    cout << config.KEmpty << endl;
    color(Colors.find("Reset")->second);

    // Viewport Outline Style
    cout << left << setw(30) << "Outline Style : ";
    color((select == 5 ? Colors.find("Green")->second : Colors.find("Reset")->second));
    cout << (config.KOutBox == 0 ? "None" :
             config.KOutBox == 1 ? "Ascii" :
             config.KOutBox == 2 ? "Single" : "Double") << endl;
    color(Colors.find("Reset")->second);
    // Skip Intro Sequence Toggle
    cout << left << setw(30) << "Skip Intro Sequence : ";
    color((select == 6 ? Colors.find("Green")->second : Colors.find("Reset")->second));
    cout << (config.KSkipIntro == 0 ? "No" : "Yes") << endl;
    color(Colors.find("Reset")->second);
    // Seed
    cout << left << setw(30) << "Seed : ";
    color((select == 7 ? Colors.find("Green")->second : Colors.find("Reset")->second));
    cout << (config.KSeed.size() == 0 ? "None" : config.KSeed) << endl;
    color(Colors.find("Reset")->second);

    // Move Up Key
    cout << left << setw(30) << "Move Up : ";
    color((select == 8 ? Colors.find("Green")->second : Colors.find("Reset")->second));
    cout << config.KMoveUp << endl;
    color(Colors.find("Reset")->second);
    // Move Right Key
    cout << left << setw(30) << "Move Right : ";
    color((select == 9 ? Colors.find("Green")->second : Colors.find("Reset")->second));
    cout << config.KMoveRight << endl;
    color(Colors.find("Reset")->second);
    // Move Down Key
    cout << left << setw(30) << "Move Down : ";
    color((select == 10 ? Colors.find("Green")->second : Colors.find("Reset")->second));
    cout << config.KMoveDown << endl;
    color(Colors.find("Reset")->second);
    // Move Left Key
    cout << left << setw(30) << "Move Left : ";
    color((select == 11 ? Colors.find("Green")->second : Colors.find("Reset")->second));
    cout << config.KMoveLeft << endl;
    color(Colors.find("Reset")->second);
    // Inspect Key
    cout << left << setw(30) << "Inspect : ";
    color((select == 12 ? Colors.find("Green")->second : Colors.find("Reset")->second));
    cout << config.KInspect << endl;
    color(Colors.find("Reset")->second);


    cout << '\n' << '\n';
    color((select == 13 ? Colors.find("Green")->second : Colors.find("Reset")->second));
    centerOut("Exit");
    color(Colors.find("Reset")->second);
}

void settingsMenu(settings& config) {
    for (unsigned short select = 0;select < 13;) {
        for(char input = 0;input != 10;) {
            renderSettingsMenu(select, config);
            read(STDIN_FILENO, &input, 1);
            if (input == config.KMoveUp && select > 0) --select;
            if (input == config.KMoveDown && select < 13) ++select;
        }
        map<string, unsigned>::const_iterator currentPColor = Colors.find(config.KColorPlayer1);
        map<string, unsigned>::const_iterator currentEColor = Colors.find(config.KColorEnemy);
        char input = 0;
        switch (select) {
        case 0:
            read(STDIN_FILENO, &input, 1);
            config.KTokenPlayer1 = input;
            break;
        case 1:
            ++currentPColor;
            if (currentPColor == Colors.end()) currentPColor = Colors.begin();
            config.KColorPlayer1 = currentPColor->first;
            break;
        case 2:
            read(STDIN_FILENO, &input, 1);
            config.KTokenEnemy = input;
            break;
        case 3:
            ++currentEColor;
            if (currentEColor == Colors.end()) currentEColor = Colors.begin();
            config.KColorEnemy = currentEColor->first;
            break;
        case 4:
            read(STDIN_FILENO, &input, 1);
            config.KEmpty = input;
            break;
        case 5:
            if (config.KOutBox == 3) config.KOutBox = 0;
            else ++config.KOutBox;
            break;
        case 6:
            config.KSkipIntro = !config.KSkipIntro;
            break;
        case 7:
            config.KSeed = "";
            renderSettingsMenu(select, config);
            for (;;) {
                read(STDIN_FILENO, &input, 1);
                if (input == 10 || config.KSeed.size() == 9) break;
                config.KSeed += input;
                renderSettingsMenu(select, config);
            }
            break;
        case 8:
            read(STDIN_FILENO, &input, 1);
            config.KMoveUp = input;
            break;
        case 9:
            read(STDIN_FILENO, &input, 1);
            config.KMoveRight = input;
            break;
        case 10:
            read(STDIN_FILENO, &input, 1);
            config.KMoveDown = input;
            break;
        case 11:
            read(STDIN_FILENO, &input, 1);
            config.KMoveLeft = input;
            break;
        case 12:
            read(STDIN_FILENO, &input, 1);
            config.KInspect = input;
            break;
        }
    }
    color(Colors.find("Reset")->second);
    // If we left the loop, that means the user selected exit. In that case, we save the settings to the config file
    ofstream configFile("config.yaml");
    configFile << "# Apperance"                               << '\n'
               << "KColorEnemy   : " << config.KColorEnemy    << '\n'
               << "KColorPlayer1 : " << config.KColorPlayer1  << '\n'
               << "KEmpty        : " << config.KEmpty         << '\n'
               << "KTokenEnemy   : " << config.KTokenEnemy    << '\n'
               << "KTokenPlayer1 : " << config.KTokenPlayer1  << '\n'
               << "KOutBox       : " << config.KOutBox        << '\n'
               << "# Gameplay"                                << '\n'
               << "KSkipIntro    : " << config.KSkipIntro     << '\n'
               << "KSeed         : " << config.KSeed          << '\n'
               << "# Controls"                                << '\n'
               << "KMoveUp       : " << config.KMoveUp        << '\n'
               << "KMoveRight    : " << config.KMoveRight     << '\n'
               << "KMoveDown     : " << config.KMoveDown      << '\n'
               << "KMoveLeft     : " << config.KMoveLeft      << '\n'
               << "KInspect      : " << config.KInspect;
    configFile.close();
}
