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

void initSettings(settings& config) {
    ifstream configFile;
    configFile.open("config.yaml");
    if (!configFile.good()) {
        ofstream newConfigFile("config.yaml");
        newConfigFile << "KColorEnemy   : " << config.KColorEnemy << '\n'
                      << "KColorPlayer1 : " << config.KColorPlayer1 << '\n'
                      << "KEmpty        : " << config.KEmpty << '\n'
                      << "KTokenEnemy   : " << config.KTokenEnemy << '\n'
                      << "KTokenPlayer1 : " << config.KTokenPlayer1 << '\n'
                      << "KOutBox       : " << config.KOutBox;
        newConfigFile.close();
        configFile.close();
        configFile.open("config.yaml");
    }
    map<string, string> configValues;
    for(string input;getline(configFile, input);) {
        if (input[0] == '#') continue;  // ignore comments
        trim(input);
        size_t semiColon = input.find(":");
        configValues[input.substr(0, semiColon)] = input.substr(semiColon+1);
    }
    configFile.close();
    // this is ridiculous...
    config.KColorEnemy = configValues.find("KColorEnemy")->second;
    config.KColorPlayer1 = configValues.find("KColorPlayer1")->second;
    config.KEmpty = configValues.find("KEmpty")->second[0];
    config.KTokenEnemy = configValues.find("KTokenEnemy")->second[0];
    config.KTokenPlayer1 = configValues.find("KTokenPlayer1")->second[0];
    cout << configValues.find("KOutBox")->second << endl;
    config.KOutBox = stoul(configValues.find("KOutBox")->second);
}

// uh... wtf is this? Monster Energy makes me black out and write code like this????
void renderSettingsMenu(const unsigned short& select, const settings& config){
    clearScreen();
    centerOut("Settings");
    cout << left << setw(30) << "Player Character : ";
    color((select == 0 ? Colors.find("Green")->second : Colors.find("Reset")->second));
    cout << config.KTokenPlayer1 << "   ";
    cout << '\n';
    color(Colors.find("Reset")->second);
    cout << left << setw(30) << "Player Color : ";
    color((select == 1 ? Colors.find("Green")->second : Colors.find("Reset")->second));
    cout << config.KColorPlayer1 << endl;
    color(Colors.find("Reset")->second);
    cout << left << setw(30) << "Enemy Character : ";
    color((select == 2 ? Colors.find("Green")->second : Colors.find("Reset")->second));
    cout << config.KTokenEnemy << "   ";
    cout << '\n';
    color(Colors.find("Reset")->second);
    cout << left << setw(30) << "Enemy Color : ";
    color((select == 3 ? Colors.find("Green")->second : Colors.find("Reset")->second));
    cout << config.KColorEnemy << endl;
    color(Colors.find("Reset")->second);
    cout << left << setw(30) << "Outline Style : ";
    color((select == 4 ? Colors.find("Green")->second : Colors.find("Reset")->second));
    cout << (config.KOutBox == 0 ? "None" :
             config.KOutBox == 1 ? "Ascii" :
             config.KOutBox == 2 ? "Single" : "Double") << endl;
    color(Colors.find("Reset")->second);


    cout << '\n' << '\n';
    color((select == 5 ? Colors.find("Green")->second : Colors.find("Reset")->second));
    centerOut("Exit");
    color(Colors.find("Reset")->second);
}

void settingsMenu(settings& config) {
    for (unsigned short select = 0;select < 5;) {
        for(char input = 0;input != 10;) {
            renderSettingsMenu(select, config);
            read(STDIN_FILENO, &input, 1);
            switch (input) {
            case 'z':
                if (select > 0) --select;
                break;
            case 's':
                if (select < 5) ++select;
                break;
            }
        }
        map<string, unsigned>::const_iterator currentPColor = Colors.find(config.KColorPlayer1);
        map<string, unsigned>::const_iterator currentEColor = Colors.find(config.KColorEnemy);
        char input;
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
            if (config.KOutBox == 3) config.KOutBox = 0;
            else ++config.KOutBox;
            break;
        }
    }
    color(Colors.find("Reset")->second);
    // If we left the loop, that means the user selected exit. In that case, we save the settings to the config file
    ofstream configFile("config.yaml");
    configFile << "KColorEnemy   : " << config.KColorEnemy << '\n'
               << "KColorPlayer1 : " << config.KColorPlayer1 << '\n'
               << "KEmpty        : " << config.KEmpty << '\n'
               << "KTokenEnemy   : " << config.KTokenEnemy << '\n'
               << "KTokenPlayer1 : " << config.KTokenPlayer1 << '\n'
               << "KOutBox       : " << config.KOutBox;
    configFile.close();
}
