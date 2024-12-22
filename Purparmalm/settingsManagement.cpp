#include "settingsManagement.h"
#include "types.h"
#include "terminalManagement.h"
#include <iostream>
#include <iomanip>
#include <unistd.h>

using namespace std;

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


    cout << '\n' << '\n';
    color((select == 4 ? Colors.find("Green")->second : Colors.find("Reset")->second));
    centerOut("Exit");
}

unsigned short settingsMenu(settings& config) {
    unsigned short select = 0;

    for (;select < 4;) {
        for(char input = 0;input != 10;) {
            renderSettingsMenu(select, config);
            read(STDIN_FILENO, &input, 1);
            switch (input) {
            case 'z':
                if (select > 0) --select;
                break;
            case 's':
                if (select < 4) ++select;
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
        }
    }
    color(Colors.find("Reset")->second);
    return select;
}
