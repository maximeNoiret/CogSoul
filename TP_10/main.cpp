#include <iostream>
#include <vector>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
const char kTokenPlayer1 = 'X';
const char kTokenPlayer2 = 'O';
const char kEmpty        = '_';

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

typedef vector <char> CVLine; // un type représentant une ligne de la grille
typedef vector <CVLine> CMatrix; // un type représentant la grille //vector<vector<char>>
typedef pair   <unsigned, unsigned> CPosition; // un type représentant une coordonnée dans la grille






/* Use this variable to remember original terminal attributes. */

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

void showMatrix (const CMatrix & mat, const short & couleurPlato)
{
    clearScreen();
    couleur(KReset);
    for (size_t i (0); i < size(mat); ++i)
    {
        couleur(couleurPlato);
        cout << "|" ;
        couleur(kEmpty);
        for (size_t y (0); y < size(mat[0]); ++y)
        {
            if (mat[i][y] == kEmpty)
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
        couleur(kEmpty);


        }
        cout << endl;
    }
}
//CMatrix test (20, CVline(20, 'c'));

void initMat (CMatrix & Mat, unsigned nbLine, unsigned nbColumn, CPosition & posPlayer1, CPosition & posPlayer2)
{
    Mat.assign(nbLine, CVLine (nbColumn, kEmpty));
    posPlayer1  = {0 , 0} ;
    posPlayer2 = {nbLine-1, nbColumn-1} ;
    Mat [0][0] = kTokenPlayer1;
    Mat [nbLine-1][nbColumn-1] = kTokenPlayer2;
}

//Chaque joueur joue à tour de rôle, et ne peut faire qu’un unique déplacement, et d’une seule case. Les touches valides de déplacement sont ‘A’ (haut gauche), ‘Z’ (haut), ‘E’ (haut droit), ‘Q’, ‘D’, ‘W’, ‘X, et ‘C’ (mais elles peuvent être changées).
void moveToken (CMatrix & Mat, char move, CPosition  & pos)
{
    char joueur = Mat [pos.first][pos.second];
    Mat [pos.first][pos.second] = kEmpty;
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


void moveTokenChevalVertical (CMatrix & Mat, char move, CPosition  & pos)
{
    char joueur = Mat [pos.first][pos.second];
    Mat [pos.first][pos.second] = kEmpty;
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

void moveTokenChevalHorizontal (CMatrix & Mat, char move, CPosition  & pos)
{
    char joueur = Mat [pos.first][pos.second];
    Mat [pos.first][pos.second] = kEmpty;
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

void moveTokenChevalHV(CMatrix & Mat, char move)
{
    char moveHorV;
    if (move == 'l')
    {
        cout << "Voulez vous jouer en horizontal ou vertical ? Les touches seront a,e,w, et c pour se déplacer !" << endl;
        cin >> moveHorV;
    }


}

int ppal ()
{
    // probs:
    //      -sortie de plateau [OK]
    //      -plusieurs move en même temps [OK]
    CMatrix Mat;
    unsigned ligne;
    unsigned colonne;
    unsigned toursMax (0);
    char Move;
    char MoveHorV;
    short Couleur;
    char TypeDeJeu;
    size_t nombreTours (0);
    CPosition posPlayer1;
    CPosition posPlayer2;
    cout << "combien de lignes ? " << endl << "->  ";
    cin >> ligne;
    cout << "combien de colonnes ? " << endl << "->  ";
    cin >> colonne;
    cout << "combien de tours max ? " << endl << "->  ";
    cin >> toursMax;
    cout << "Quelle couleur pour le plateau ? " << endl
    << "| Noir : 30 " << endl
    <<  "| Rouge : 31" << endl
    << "| Vert : 32 "<< endl
    <<"| Jaune : 33 "<< endl
    <<"| Bleu : 34 "<< endl
    <<"| Magenta : 35 "
    << endl <<"| Cyan : 36 "
    << endl << endl << "->  ";
    cin >> Couleur;
    cout << "Input des règles ici" << endl
         << "Quel mode de jeu voulez vous ?" << endl
         << " Cavalier : entrez 'l' " << endl
         << " Jeu normal : entrez 'a'" << endl << endl
         << "->  ";
    cin >>TypeDeJeu;
    initMat(Mat,ligne,colonne,posPlayer1,posPlayer2);
    showMatrix(Mat, Couleur);
    set_input_mode ();
    if (TypeDeJeu == 'a')

        while (nombreTours < toursMax && posPlayer1 != posPlayer2)
        {

            if (nombreTours%2 == 0)
            {
                couleur(KJaune);
                cout << "Tour du joueur 1" << endl;
                couleur(KReset);
                read (STDIN_FILENO, &Move, 1);
                moveToken(Mat, Move,posPlayer1);

            }
            else
            {
                couleur(KVert);
                cout << "Tour du joueur 2" <<endl;
                couleur(KReset);
                read (STDIN_FILENO, &Move, 1);
                moveToken(Mat, Move,posPlayer2);
            }

            showMatrix(Mat, Couleur);
            cout << endl << endl << "tours restants : " << toursMax-(nombreTours+1) << endl;
            nombreTours += 1;
        }
    else if (TypeDeJeu == 'l')

        while (nombreTours < toursMax && posPlayer1 != posPlayer2)
        {

            if (nombreTours%2 == 0)
            {
                couleur(KJaune);
                cout << "Tour du joueur 1" << endl <<endl << "Voulez-vous jouer en horizontal ou vertical ?" << endl << "Pour vertical : Entrez 'v' " << endl << "Pour horizontal : Entrez 'h' " << endl ;
                couleur(KReset);
                read (STDIN_FILENO, &MoveHorV, 1);
                showMatrix(Mat, Couleur);
                couleur(Couleur);
                cout << endl << endl <<  "tours restants : " << toursMax-(nombreTours+1) << endl;
                couleur(KReset);
                couleur(KJaune);
                cout << "Tour du joueur 1" << endl << endl;
                couleur(KReset);
                read (STDIN_FILENO, &Move, 1);
                if (MoveHorV == 'v')
                    moveTokenChevalVertical(Mat, Move, posPlayer1);
                else
                    moveTokenChevalHorizontal(Mat, Move, posPlayer1);
                couleur(KReset);
            }
            else
            {
                couleur(KVert);
                cout << "Tour du joueur 2" << endl <<endl << "Voulez-vous jouer en horizontal ou vertical ?" << endl << "Pour vertical : Entrez 'v' " << endl << "Pour horizontal : Entrez 'h' " << endl ;
                couleur(KReset);
                read (STDIN_FILENO, &MoveHorV, 1);
                showMatrix(Mat, Couleur);
                couleur(Couleur);
                cout << endl << endl << "tours restants : " << toursMax-(nombreTours+1) << endl;
                couleur(KReset);
                couleur(KVert);
                cout << "Tour du joueur 2" << endl << endl;
                couleur(KReset);
                read (STDIN_FILENO, &Move, 1);
                if (MoveHorV == 'v')
                    moveTokenChevalVertical(Mat, Move, posPlayer2);
                else
                    moveTokenChevalHorizontal(Mat, Move, posPlayer2);
                couleur(KReset);
            }

            showMatrix(Mat, Couleur);
            couleur(Couleur);
            cout << endl << endl << "tours restants : " << toursMax-(nombreTours+1) << endl;
            couleur(KReset);
            nombreTours += 1;
        }

    if ( nombreTours == toursMax)
    {
        couleur(Couleur);
        cout << endl << endl << "egalité, plus de tours disponibles" <<endl <<endl;
        couleur(KReset);
    }
    else if ( nombreTours%2 == 0)
    {
        couleur(KVert);
        cout << endl << endl << "Le joueur 2 a gagné" <<endl <<endl;
        couleur(KReset);
    }
    else
    {
        couleur(KJaune);
        cout << endl << endl<< "Le joueur 1 a gagné" <<endl <<endl;
        couleur(KReset);
    }

    return 0;

}



int main()
{
    return ppal();
    // CMatrix Mat;
    // CPosition posPlayer1;
    // CPosition posPlayer2;
    // initMat(Mat, 10, 10, posPlayer1, posPlayer2);
    //CODEU
    // cout << "Hello World!" << endl;
    // clearScreen();
    // background(BackKRouge);
    // cout << "TETETTEFDSEFICSNFCS" << endl;
    //initMat();
    // return 0;
}




