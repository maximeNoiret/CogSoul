#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "ptt_functions.h"
#include "ptt_main.h"


using namespace std;

int main_ptt()
{
    size_t emptynNbr;
    char Move;
    mapGrid Mat;
    CPosition posPlayer = {3, 4};
    size_t nombercase (0);
    size_t nomberTours (0);
    short Couleur (36);
    size_t nbrMap (1);
    string wayMap ("../../map" + to_string(nbrMap)) ;
    char resultat;
    unsigned maxTurn (200);



    for(size_t y (nbrMap) ; y < 10 ; ++y)
    {
        wayMap = ("ptt_maps/map" + to_string(y)) ;
        clearScreen_ptt();
        loadMapFromFile_ptt(Mat, wayMap);
        posPlayer.first = 5;
        posPlayer.second = 4;
        Mat[posPlayer.first][posPlayer.second] = kTokenPlayer1;
        showCountMatrix(Mat, Couleur, nombercase);
        for(size_t i (nomberTours); i < maxTurn; ++i)
        {
            nombercase = 0;
            read (STDIN_FILENO, &Move, 1);
            while(isgoodPlaced(Mat, Move, posPlayer))
            {
                moveToken_ptt(Mat, Move,posPlayer);
            }
            nombercase = showCountMatrix(Mat, Couleur, nombercase);
            emptynNbr = countCasesVides(Mat, emptynNbr);

            cout << endl << endl << "Remaining Turns : " << maxTurn-i << endl;
            cout << endl << "empty cases left : : " << emptynNbr << endl;
            cout << endl << "level :" << y << endl;
            cout << nombercase << endl;
            if (emptynNbr == 0)
                i = maxTurn-1;
        }

    }

    cout  << endl << "GG YOU WON" << endl;
    cin >> resultat;



    return 0;
}


















