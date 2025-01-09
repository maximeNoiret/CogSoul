#include "functions.h"

functions::functions() {}


void reset_input_mode (void)
{
    tcsetattr (STDIN_FILENO, TCSANOW, &saved_attributes);
}

void set_input_mode (void)
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

void showMatrix (const mapGrid & mat, const short & couleurPlato)
{
    clearScreen();
    couleur(KReset);
    for (size_t i (0); i < size(mat); ++i)
    {
        couleur(couleurPlato);
        cout << "|" ;
        couleur(KEmpty);
        for (size_t y (0); y < size(mat[0]); ++y)
        {
            if (mat[i][y] == KEmpty)
            {
                couleur(couleurPlato);
                cout << mat[i][y];
            }

            else if (mat[i][y] == kTokenPlayer1)
            {
                couleur(KJaune);
                cout << kTokenPlayer1;
                couleur(KReset);
            }
            else
            {
                couleur(KVert);
                cout << kTokenPlayer2;
                couleur(KReset);
            }
            couleur(couleurPlato);
            cout << "|" ;
            couleur(KEmpty);


        }
        cout << endl;
    }
}

size_t showCountMatrix(const mapGrid & mat, const short & couleurPlato, size_t & nombercase)
{
    clearScreen();
    couleur(KReset);
    for (size_t i (0); i < size(mat); ++i)
    {
        couleur(couleurPlato);
        cout << "|" ;
        couleur(KEmpty);
        for (size_t y (0); y < size(mat[0]); ++y)
        {
            if (mat[i][y] == KEmpty)
            {
                couleur(couleurPlato);
                cout << mat[i][y];
            }

            else if (mat[i][y] == kTokenPlayer1)
            {
                couleur(KJaune);
                cout << kTokenPlayer1;
                couleur(KReset);
                nombercase = nombercase + 1;
            }
            else
            {
                continue;
            }
            couleur(couleurPlato);
            cout << "|" ;
            couleur(KEmpty);


        }
        cout << endl;
    }
    return nombercase;
}




void initMat (mapGrid & Mat, unsigned nbLine, unsigned nbColumn, CPosition & posPlayer1, CPosition & posPlayer2)
{
    Mat.assign(nbLine, mapLine (nbColumn, KEmpty));
    posPlayer1  = {0 , 0} ;
    posPlayer2 = {nbLine-1, nbColumn-1} ;
    Mat [0][0] = kTokenPlayer1;
    Mat [nbLine-1][nbColumn-1] = kTokenPlayer2;
}

void moveToken (mapGrid & Mat, char move, CPosition  & pos)
{
    char joueur = Mat [pos.first][pos.second];
    Mat [pos.first][pos.second] = KEmpty;
    switch (move)
    {
    case 'a' :
        if ((pos.first > 0 )&& ( pos.second > 0))
        {
            pos.first -= 1;
            pos.second -= 1;
        }
        break;
    case 'e' :
        if ((pos.first > 0) && (pos.second < size(Mat[0])-1))
        {
            pos.first -= 1;
            pos.second += 1;
        }
        break;
    case 'z' :
        if (pos.first > 0)
            pos.first -= 1;
        break;
    case 'q' :
        if (pos.second > 0)
            pos.second -= 1;
        break;
    case 'd' :
        if (pos.second < size(Mat)-1)
            pos.second += 1;
        break;
    case 'w' :
        if ((pos.first < size(Mat)-1) && (pos.second > 0))
        {
            pos.first += 1;
            pos.second -= 1;
        }
        break;
    case 'x':
        if (pos.first < size(Mat)-1)
            pos.first += 1;
        break;
    case 'c':
        if ((pos.second < size(Mat)-1) && (pos.first < size(Mat[0])-1))
        {
            pos.first += 1;
            pos.second += 1;
        }
        break;
    }

    Mat [pos.first][pos.second] = joueur;
}

void moveTokenCouleur (mapGrid & Mat, char move, CPosition  & pos)
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
    case 'x':
        if (pos.first < Mat.size()-1 && Mat[pos.first + 1][pos.second] != '#')
            pos.first += 1;
        break;
    }

    Mat [pos.first][pos.second] = joueur;
}

void moveTokenChevalVertical (mapGrid & Mat, char move, CPosition  & pos)
{
    char joueur = Mat [pos.first][pos.second];
    Mat [pos.first][pos.second] = KEmpty;
    switch (move)
    {
    case 'a' :
        if ((pos.first > 1 ) && ( pos.second > 0))
        {
            pos.first -= 2;
            pos.second -= 1;
        }
        break;
    case 'e' :
        if ((pos.first > 1) && (pos.second < size(Mat[pos.first])-1))
        {
            pos.first -= 2;
            pos.second += 1;
        }
        break;
    case 'w' :
        if ((pos.first + 2 < size(Mat)) && (pos.second > 0))
        {
            pos.first += 2;
            pos.second -= 1;
        }
        break;
    case 'c':
        if ((pos.second  < size(Mat[pos.first])-1) && (pos.first + 2 < size(Mat)))
        {
            pos.first += 2;
            pos.second += 1;
        }
        break;
    }

    Mat [pos.first][pos.second] = joueur;
}

void moveTokenChevalHorizontal (mapGrid & Mat, char move, CPosition  & pos)
{
    char joueur = Mat [pos.first][pos.second];
    Mat [pos.first][pos.second] = KEmpty;
    switch (move)
    {
    case 'a' :
        if ((pos.first > 0 ) && ( pos.second > 1))
        {
            pos.first -= 1;
            pos.second -= 2;
        }
        break;
    case 'e' :
        if ((pos.first > 0) && (pos.second + 2 < size(Mat[pos.first])))
        {
            pos.first -= 1;
            pos.second += 2;
        }
        break;
    case 'w' :
        if ((pos.first + 1 < size(Mat)) && (pos.second > 1))
        {
            pos.first += 1;
            pos.second -= 2;
        }
        break;
    case 'c':
        if ((pos.second +2 < size(Mat[pos.first])) && (pos.first + 1 < size(Mat)))
        {
            pos.first += 1;
            pos.second += 2;
        }
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
    case 'x':
        if (pos.first < Mat.size()-1 && Mat[pos.first + 1][pos.second] != '#')
            return true;
        break;
    }
    return false;
}
