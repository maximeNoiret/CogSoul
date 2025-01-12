/**
 * @author Brest-Lestrade Hugo
 */

// ToDo: fix all the documentation

#ifndef PTT_FUNCTIONS_H
#define PTT_FUNCTIONS_H

#include "types.h"
#include <termios.h>
#include <vector>


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

typedef vector <char> mapLine;
typedef vector <mapLine> mapGrid;
typedef pair   <unsigned, unsigned> CPosition;


/**
 * @brief reset_input_mode
 */
void reset_input_mode_ptt ();

/**
 * @brief set_input_mode
 */
void set_input_mode_ptt (void);
/**
 * @brief clearScreen
 */
void clearScreen_ptt ();

/**
 * @brief couleur
 * @param[in] coul : Unix terminal code for the color to change to
 */
void couleur_ptt (const unsigned & coul);

/**
 * @brief background
 * @param back[in] : back est une valeur utilisée pour mettre un code de couleur pour l'arrière-plan
 */
void background (const unsigned & back);

/**
 * @brief Places a map from a text file into a mapGrid object
 * @param[in] fileName : the path of the file that contains the map
 * @param[in] config : settings of the game
 * @return a mapGrid object containing the map
 */
void loadMapFromFile_ptt(mapGrid& mat, const std::string& fileName);

/**
 * @brief showCountMatrix
 * @param[in] mat : mapGrid object who represent the map with colors
 * @param[in] couleurPlato : the color the map takes
 * @param[in] nombercase : number of cases of the map
 * @return
 */
size_t showCountMatrix(const mapGrid & mat, const short & couleurPlato, size_t & nombercase);

/**
 * @brief printVect
 * @param[in] vect : represent a vector's elements
 */
void printVect(const std::vector<char>& vect);

/**
 * @brief printGrid
 * @param[in] gameMap : mapGrid object who represent the map
 */
void printGrid(const mapGrid& gameMap);


/**
 * @brief moveToken
 * @param[in] Mat : mapGrid object who represent the map with colors
 * @param[in] move : char object who represent the deplacement keys
 * @param[in_out] pos : CPosition object who represent the coordinates of the player
 */
void moveToken_ptt (mapGrid & Mat, char move, CPosition  & pos);

/**
 * @brief isgoodPlaced
 * @param[in] Mat : mapGrid object who represent the map
 * @param[in] move : char object who represent the deplacement keys
 * @param[in] pos : CPosition object who represent the coordinates of the player
 * @return
 */
bool isgoodPlaced(mapGrid & Mat, char & move, CPosition  & pos);



/**
 * @brief countCasesVides
 * @param[in] mat : mapGrid object who represent the map with colors
 * @param[in_out] emptynNbr : integrer element who represent cases no colored yet in the map
 * @return
 */
size_t countCasesVides(mapGrid & mat, size_t nbrVides);






#endif // FUNCTIONS_H
















