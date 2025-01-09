#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#endif // FUNCTIONS_H
/**
 * @brief reset_input_mode
 */
void reset_input_mode (void);

/**
 * @brief set_input_mode
 */
void set_input_mode (void);
/**
 * @brief clearScreen
 */
void clearScreen ();

/**
 * @brief couleur
 * @param[in] coul : Unix terminal code for the color to change to
 */
void couleur (const unsigned & coul);

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
mapGrid loadMapFromFile(const std::string& fileName, const settings& config);

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
void printVect(const vector<char>& vect);

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
void moveToken (mapGrid & Mat, char move, CPosition  & pos);

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
















