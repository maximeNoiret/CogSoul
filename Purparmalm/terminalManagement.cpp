#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include "types.h"

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
