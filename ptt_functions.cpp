#include <iostream>
#include <vector>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include "ptt_functions.h"
#include "types.h"


using namespace std;
struct termios saved_attributes_ptt;

void reset_input_mode_ptt ()
{
    tcsetattr (STDIN_FILENO, TCSANOW, &saved_attributes_ptt);
}

void set_input_mode_ptt (void)
{
    struct termios tattr;
    char *name;

    /* Make sure stdin is a terminal. */
    if (!isatty (STDIN_FILENO))
    {
        fprintf (stderr, "Not a terminal.\n");
        exit (EXIT_FAILURE);
    }

    /* Save the terminal attributes so we can restore them later. */
    tcgetattr (STDIN_FILENO, &saved_attributes_ptt);
    atexit (reset_input_mode_ptt);

    /* Set the funny terminal modes. */
    tcgetattr (STDIN_FILENO, &tattr);
    tattr.c_lflag &= ~(ICANON|ECHO); /* Clear ICANON and ECHO. */
    tattr.c_cc[VMIN] = 1;
    tattr.c_cc[VTIME] = 0;
    tcsetattr (STDIN_FILENO, TCSAFLUSH, &tattr);
}

void clearScreen_ptt () {
    cout << "\033[H\033[2J";
}

void couleur_ptt (const unsigned & coul) {
    cout << "\033[" << coul <<"m";
}
void background_ptt (const unsigned & back)
{
    cout << "\033[7;" << back <<"m";
}


void loadMapFromFile_ptt(mapGrid& roomGrid, const string& fileName) {
    ifstream mapFile (fileName);
    if (!mapFile.good()) {
        cerr << "Couldn't access map file! (" << fileName << ")" << endl;
        exit(2);
    }
    size_t height;
    mapFile >> height;
    size_t width;
    mapFile >> width;
    mapFile.get();  // gets rid of newline
    roomGrid.assign(height, mapLine (width, KEmpty));
    string input;
    for (mapGrid::iterator iter = roomGrid.begin(); iter != roomGrid.end() && getline(mapFile, input); ++iter) {
        size_t tmpIndex = 0;
        for (mapLine::iterator subIter = iter->begin(); subIter != iter->end() && tmpIndex < input.size(); ++subIter) {
            if (input[tmpIndex] == '\n') continue;
            *subIter = (input[tmpIndex] == ' ' ? KEmpty : input[tmpIndex]);
            ++tmpIndex;
        }
    }
}

size_t showCountMatrix(const mapGrid & mat, const short & couleurPlato, size_t & nombercase)
{
    clearScreen_ptt();
    couleur_ptt(KReset);
    for (size_t i (0); i < size(mat); ++i)
    {
        for (size_t y (0); y < size(mat[0]); ++y)
        {
            if (mat[i][y] == KEmpty)
            {
                couleur_ptt(couleurPlato);
                cout << ' ';
            }

            else if (mat[i][y] == kTokenPlayer1)
            {
                couleur_ptt(KJaune);
                cout << kTokenPlayer1;
            }
            else if (mat[i][y] == '#')
            {
                couleur_ptt(couleurPlato);
                cout << '#';
            }
            else
            {
                couleur_ptt(31);
                cout << 'X';
            }
        }
        cout << endl;
    }
    return nombercase;
}

void printVect(const vector<char>& vect) {
    for (const char & elem : vect) {
        //color((elem == KTokenPlayer1 ? KBlue : (elem == KTokenEnemy ? KRed : KReset)));
        cout << elem;
    }
    cout << endl;
}

void printGrid(const mapGrid& gameMap) {
    for (const mapLine& lin : gameMap)
        printVect(lin);
}

void moveToken_ptt (mapGrid & Mat, char move, CPosition  & pos)
{
    char joueur = Mat [pos.first][pos.second];
    Mat [pos.first][pos.second] = 'X';
    switch (move)
    {
    case 'z' :
        if (pos.first > 0 && Mat[pos.first - 1][pos.second] != '#')
            pos.first -= 1;
        break;
    case 'q' :
        if (pos.second > 0 && Mat[pos.first][pos.second - 1] != '#')
            pos.second -= 1;
        break;
    case 'd' :
        if (pos.second < Mat[pos.first].size()-1 && Mat[pos.first][pos.second + 1] != '#')
            pos.second += 1;
        break;
    case 's':
        if (pos.first < Mat.size()-1 && Mat[pos.first + 1][pos.second] != '#')
            pos.first += 1;
        break;
    }

    Mat [pos.first][pos.second] = joueur;
}

bool isgoodPlaced(mapGrid & Mat, char & move, CPosition  & pos)
{
    switch (move)
    {
    case 'z' :
        if (pos.first > 0 && Mat[pos.first - 1][pos.second] != '#')
            return true;
        break;
    case 'q' :
        if (pos.second > 0 && Mat[pos.first][pos.second - 1] != '#')
            return true;
        break;
    case 'd' :
        if (pos.second < Mat[pos.first].size()-1 && Mat[pos.first][pos.second + 1] != '#')
            return true;
        break;
    case 's':
        if (pos.first < Mat.size()-1 && Mat[pos.first + 1][pos.second] != '#')
            return true;
        break;
    }
    return false;
}

size_t countCasesVides(mapGrid & mat, size_t emptynNbr)
{
    emptynNbr = 0;
    for (size_t i (0); i < size(mat); ++i)
    {
        for (size_t y (0); y < size(mat[0]); ++y)
        {
            if (mat[i][y] == KEmpty)
            {
                emptynNbr += 1;
            }
            else if (mat[i][y] == kTokenPlayer1)
            {
                continue;
            }

        }
        cout << endl;
    }
    return emptynNbr;
}
