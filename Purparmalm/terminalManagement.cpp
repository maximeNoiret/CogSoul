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


void printVect(const vector<char>& vect) {
    for (const char & elem : vect) {
        color((elem == KTokenPlayer1 ? KBlue : (elem == KTokenEnemy ? KRed : KReset)));
        cout << elem;
    }
    cout << endl;
}

void printGrid(const mapGrid& gameMap) {
    for (const mapLine& lin : gameMap)
        printVect(lin);
}

void generateRender(const mapGrid& gameMap, const unsigned& renderDist, const playerInfo player) {
    mapGrid universe (gameMap.size()+ 2 * renderDist, mapLine (gameMap[0].size()+ 2 * renderDist, ' '));
    placeRoom(universe, gameMap, renderDist, renderDist);
    CPosition upperLeft = {player.pos.first + renderDist * 0.5, player.pos.second};
    CPosition bottomRight = {player.pos.first + 2 * renderDist - renderDist * 0.5 + 1, player.pos.second + 2 * renderDist + 1};
    // print rendered map
    for (mapGrid::const_iterator iter = universe.begin() + upperLeft.first;
         iter < universe.begin() + bottomRight.first;
         ++iter) {
        for (mapLine::const_iterator subIter = iter->begin() + upperLeft.second;
             subIter < iter->begin() + bottomRight.second;
             ++subIter) {
            cout << *subIter;
        }
        cout << endl;
    }

    // print info
    cout << endl << endl;
    cout << "X: " << setw(4) << player.pos.first
         << "\tY: " << setw(4) << player.pos.second
         << "\tCaught: " << setw(4) << (player.seen ? "Yes" : "No")
         << "\tSteps: " << setw(4) << player.steps
         << endl;
}
