#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <iomanip>
#include "types.h"
#include "mapManagement.h"

using namespace std;
struct termios saved_attributes;

void reset_input_mode() {
    tcsetattr (STDIN_FILENO, TCSANOW, &saved_attributes);
}

void set_input_mode() {
    struct termios tattr;

    /* Make sure stdin is a terminal. */
    if (!isatty (STDIN_FILENO))
    {
        cerr << "Not a terminal.\n";
        exit (EXIT_FAILURE);
    }

    /* Save the terminal attributes so we can restore them later. */
    tcgetattr (STDIN_FILENO, &saved_attributes);
    atexit (reset_input_mode);

    /* Set the funny terminal modes. */
    tcgetattr (STDIN_FILENO, &tattr);
    tattr.c_lflag &= ~(ICANON|ECHO); /* Clear ICANON and ECHO. */
    tattr.c_cc[VMIN] = 1;
    tattr.c_cc[VTIME] = 0;
    tcsetattr (STDIN_FILENO, TCSAFLUSH, &tattr);
}


void clearScreen() {
    cout << "\033[H\033[2J";
}


void color (const unsigned & col) {
    cout << "\033[" << col <<"m";
}


// NOTE: this function assumes a terminal width of 80 columns, the default pretty much everywhere (even windows)
void centerOut(const string& out) {
    cout << string(80*0.5 - out.size()*0.5, ' ') << out << endl;
}


void renderMainMenu(const short& select) {
    clearScreen();
    cout << string(4, '\n');
    centerOut("GAME NAME");
    cout << string(3, '\n');
    color((select == 0 ? Colors.find("Green")->second : Colors.find("Reset")->second));
    centerOut("Play");
    cout << '\n';
    color((select == 1 ? Colors.find("Green")->second : Colors.find("Reset")->second));
    centerOut("Settings");
    cout << '\n';
    color((select == 2 ? Colors.find("Green")->second : Colors.find("Reset")->second));
    centerOut("Exit");
    color(Colors.find("Reset")->second);
}


unsigned short mainMenu() {
    unsigned short select = 0;
    for(char input = 0;input != 10;) {
        renderMainMenu(select);
        read(STDIN_FILENO, &input, 1);
        switch (input) {
        case 'z':
            if (select > 0) --select;
            break;
        case 's':
            if (select < 2) ++select;
            break;
        }
    }
    return select;
}


string inputName() {
    string playerName;
    for (char input = 0;;) {
        string nameDisplay (5, '_');
        for (size_t i = 0; i < playerName.size(); ++i)
            nameDisplay[i] = playerName[i];
        clearScreen();
        cout << '\t';
        for (const char& letter : nameDisplay)
            cout << letter << ' ';
        cout << endl << "Enter your name:" << endl;
        if (playerName.size() == 5) break;
        read(STDIN_FILENO, &input, 1);
        if (input == 10) break;
        if (input == 127) {
            playerName.erase(playerName.size()-1);
        } else {
            playerName += input;
        }
    }
    return playerName;
}


void generateRender(const mapGrid& gameMap, const unsigned& renderDist, const playerInfo player, const settings& config) {
    mapGrid universe (gameMap.size()+ 2 * renderDist, mapLine (gameMap[0].size()+ 2 * renderDist, ' '));
    placeRoom(universe, gameMap, renderDist, renderDist, true);
    // simple waste of ressources (16 bytes of memory(?)) to make my life easier
    CPosition upperLeft = {player.pos.first + renderDist * 0.5, player.pos.second};
    CPosition bottomRight = {player.pos.first + 2 * renderDist - renderDist * 0.5 + 1, player.pos.second + 2 * renderDist + 1};

    // print rendered map
    // test if weird box characters work in any systems (test it in a fresh linux distro)
    // └─ nvm, just fixed it by adding it as an option and adding an ascii version
    if (config.KOutBox > 0) {
        cout << '\t' << (config.KOutBox == 1 ? "+" :
                             config.KOutBox == 2 ? "\u250C" : "\u2554");
        for(unsigned i = 0; i < renderDist*2+1; ++i)
            cout << (config.KOutBox == 1 ? "-" :
                         config.KOutBox == 2 ? "\u2500" : "\u2550");
        cout << (config.KOutBox == 1 ? "+" :
                     config.KOutBox == 2 ? "\u2510" : "\u2557");
    }
    cout << endl;
    const vector<string> logs = Logs::getLogs();
    unsigned logIndex = 0;  // unsigned is fine since log size is fixed
    for (mapGrid::const_iterator iter = universe.begin() + upperLeft.first;
         iter < universe.begin() + bottomRight.first;
         ++iter) {
        cout << '\t';
        if (config.KOutBox > 0)
            cout << (config.KOutBox == 1 ? "|" :
                             config.KOutBox == 2 ? "\u2502" : "\u2551");
        for (mapLine::const_iterator subIter = iter->begin() + upperLeft.second;
             subIter < iter->begin() + bottomRight.second;
             ++subIter) {
            // nested ternary operators my beloved :)
            color(*subIter == config.KTokenPlayer1 ? Colors.find(config.KColorPlayer1)->second :
                  *subIter == config.KTokenEnemy ? Colors.find(config.KColorEnemy)->second : Colors.find("Reset")->second);
            cout << (*subIter == '1' || *subIter == '3' ? '-' :
                     *subIter == '2' || *subIter == '4' ? '|' : *subIter);
        }
        if (config.KOutBox > 0)
            cout << (config.KOutBox == 1 ? "|" :
                     config.KOutBox == 2 ? "\u2502" : "\u2551");
        if (logIndex < logs.size()) {
            cout << string(8, ' ') << logs[logIndex];
            ++logIndex;
        }
        cout << endl;
    }
    if (config.KOutBox > 0) {
        cout << '\t' << (config.KOutBox == 1 ? "+" :
                         config.KOutBox == 2 ? "\u2514" : "\u255A");
        for(unsigned i = 0; i < renderDist*2+1; ++i)
            cout << (config.KOutBox == 1 ? "-" :
                     config.KOutBox == 2 ? "\u2500" : "\u2550");
        cout << (config.KOutBox == 1 ? "+" :
                 config.KOutBox == 2 ? "\u2518" : "\u255D");
    }
    cout << '\n';
    // print info
    cout << '\n' << '\n';
    cout << "X: " << setw(4) << player.pos.second
         << "\tY: " << setw(4) << player.pos.first
         << "\tCaught: " << setw(4) << (player.seen ? "Yes" : "No");
}
