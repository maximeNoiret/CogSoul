#include <iostream>
#include <vector>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>

const char kTokenPlayer1 = 'O';
const char KEmpty        = ' ';

using namespace std;
//COULEURS texte
const unsigned KReset   (0);
const unsigned KNoir    (30);
const unsigned KRouge   (31);
const unsigned KVert    (32);
const unsigned KJaune   (33);
const unsigned KBleu    (34);
const unsigned KMAgenta (35);
const unsigned KCyan    (36);
//couleur background
const unsigned BackKReset   (0);
const unsigned BackKNoir    (40);
const unsigned BackKRouge   (41);
const unsigned BackKVert    (42);
const unsigned BackKJaune   (43);
const unsigned BackKBleu    (44);
const unsigned BackKMAgenta (45);
const unsigned BackKCyan    (46);

typedef vector <char> mapLine; // un type représentant une ligne de la grille
typedef vector <mapLine> mapGrid; // un type représentant la grille //vector<vector<char>>
typedef pair   <unsigned, unsigned> CPosition; // un type représentant une coordonnée dans la grille

struct termios saved_attributes;

void
reset_input_mode (void)
{
    tcsetattr (STDIN_FILENO, TCSANOW, &saved_attributes);
}

void
set_input_mode (void)
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
    tcgetattr (STDIN_FILENO, &saved_attributes);
    atexit (reset_input_mode);

    /* Set the funny terminal modes. */
    tcgetattr (STDIN_FILENO, &tattr);
    tattr.c_lflag &= ~(ICANON|ECHO); /* Clear ICANON and ECHO. */
    tattr.c_cc[VMIN] = 1;
    tattr.c_cc[VTIME] = 0;
    tcsetattr (STDIN_FILENO, TCSAFLUSH, &tattr);
}



void clearScreen () {
    cout << "\033[H\033[2J";
}

void couleur (const unsigned & coul) {
    cout << "\033[" << coul <<"m";
}
void background (const unsigned & back)
{
    cout << "\033[7;" << back <<"m";
}


void loadMapFromFile(mapGrid& roomGrid, const string& fileName) {
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

// void showMatrix (const mapGrid & mat, const short & couleurPlato)
// {
//     clearScreen();
//     for (size_t i (0); i < size(mat); ++i)
//     {

//         for (size_t y (0); y < size(mat[0]); ++y)
//         {
//             if (mat[i][y] == KEmpty)
//             {

//                 cout << mat[i][y];
//             }

//             else if (mat[i][y] == kTokenPlayer1)
//             {

//                 cout << kTokenPlayer1;

//             }
//             else
//             {

//                 cout << kTokenPlayer1;

//             }


//         }
//         cout << endl;
//     }
// }
size_t showCountMatrix(const mapGrid & mat, const short & couleurPlato, size_t & nombercase)
{
    clearScreen();
    couleur(KReset);
    for (size_t i (0); i < size(mat); ++i)
    {
        for (size_t y (0); y < size(mat[0]); ++y)
        {
            if (mat[i][y] == KEmpty)
            {
                couleur(couleurPlato);
                cout << ' ';
            }

            else if (mat[i][y] == kTokenPlayer1)
            {
                couleur(KJaune);
                cout << kTokenPlayer1;
            }
            else if (mat[i][y] == '#')
            {
                couleur(couleurPlato);
                cout << '#';
            }
            else
            {
                couleur(31);
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

void moveToken (mapGrid & Mat, char move, CPosition  & pos)
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

size_t countCasesVides(mapGrid & mat, size_t nbrVides)
{
    nbrVides = 0;
    for (size_t i (0); i < size(mat); ++i)
    {
        for (size_t y (0); y < size(mat[0]); ++y)
        {
            if (mat[i][y] == KEmpty)
            {
                nbrVides += 1;
            }
            else if (mat[i][y] == kTokenPlayer1)
            {
                continue;
            }

        }
        cout << endl;
    }
    return nbrVides;
}

using namespace std;

int main()
{
    size_t nbrVides;
    char Move;
    mapGrid Mat;
    CPosition posPlayer = {3, 4};
    size_t nombercase (0);
    size_t nombreTours (0);
    short Couleur (36);
    size_t numeroMap (1);
    string cheminMap ("../../map" + to_string(numeroMap) + ".txt") ;
    char resultat;
    unsigned toursMax (200);



    for(size_t y (numeroMap) ; y < 10 ; ++y)
    {
        cheminMap = ("../../map" + to_string(y) + ".txt") ;
        clearScreen();
        loadMapFromFile(Mat, cheminMap);
        Mat[posPlayer.first][posPlayer.second] = kTokenPlayer1;
        showCountMatrix(Mat, Couleur, nombercase);
        for(size_t i (nombreTours); i < toursMax; ++i)
        {
            nombercase = 0;
            read (STDIN_FILENO, &Move, 1);
            while(isgoodPlaced(Mat, Move, posPlayer))
            {
                moveToken(Mat, Move,posPlayer);
            }
            nombercase = showCountMatrix(Mat, Couleur, nombercase);
            nbrVides = countCasesVides(Mat, nbrVides);

            cout << endl << endl << "tours restants : " << toursMax-i << endl;
            cout << endl << "cases vides : " << nbrVides << endl;
            cout << endl << "level :" << y << endl;
            cout << nombercase << endl;
            if (nbrVides == 0)
                i = toursMax-1;
        }

    }

    cout  << endl << "BRAVO, VOUS AVEZ GAGNÉ" << endl;
    cout << endl << endl <<"APPUYEZ SUR ENTRÉE POUR SORTIR DU JEU" << endl;
    cin >> resultat;



    return 0;
}


















