#ifndef FUNCTIONS_H
#define FUNCTIONS_H

class functions
{
public:
    functions();
};

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
void loadMapFromFile(mapGrid& roomGrid, const string& fileName);


/**
 * @brief showMatrix
 * @param[in] mat : mapGrid object who represent the map with colors
 * @param[in] couleurPlato : the color the map takes
 */
void showMatrix (const mapGrid & mat, const short & couleurPlato);

/**
 * @brief showCountMatrix
 * @param[in] mat : mapGrid object who represent the map with colors
 * @param[in] couleurPlato : the color the map takes
 * @param[in] nombercase : number of cases of the map
 * @return
 */
size_t showCountMatrix(const mapGrid & mat, const short & couleurPlato, size_t & nombercase);


/**
 * @brief initMat
 * @param[in] Mat : mapGrid object who represent the map
 * @param[in] nbLine : unsigned object who represent the length of the map
 * @param[in] nbColumn : unsigned object who represent the width of the map
 * @param[in] posPlayer1 : CPosition object who represent the coordinates of the first Player
 * @param[in] posPlayer2 : CPosition object who represent the coordinates of the second Player
 */
void initMat (mapGrid & Mat, unsigned nbLine, unsigned nbColumn, CPosition & posPlayer1, CPosition & posPlayer2);

/**
 * @brief moveToken
 * @param[in] Mat : mapGrid object who represent the map
 * @param[in] move : char object who represent the deplacement keys
 * @param[in] pos : CPosition object who represent the coordinates of the player
 */
void moveToken (mapGrid & Mat, char move, CPosition  & pos);

/**
 * @brief moveTokenCouleur
 * @param[in] Mat : mapGrid object who represent the map
 * @param[in] move : char object who represent the deplacement keys
 * @param[in] pos : CPosition object who represent the coordinates of the player
 */
void moveTokenCouleur (mapGrid & Mat, char move, CPosition  & pos);

/**
 * @brief moveTokenChevalVertical
 * @param[in] Mat : mapGrid object who represent the map
 * @param[in] move : char object who represent the deplacement keys
 * @param[in] pos : CPosition object who represent the coordinates of the player
 */
void moveTokenChevalVertical (mapGrid & Mat, char move, CPosition  & pos);



/**
 * @brief moveTokenChevalHorizontal
 * @param[in] Mat : mapGrid object who represent the map
 * @param[in] move : char object who represent the deplacement keys
 * @param[in] pos : CPosition object who represent the coordinates of the player
 */
void moveTokenChevalHorizontal (mapGrid & Mat, char move, CPosition  & pos);


/**
 * @brief isgoodPlaced
 * @param[in] Mat : mapGrid object who represent the map
 * @param[in] move : char object who represent the deplacement keys
 * @param[in] pos : CPosition object who represent the coordinates of the player
 * @return
 */
bool isgoodPlaced(mapGrid & Mat, char & move, CPosition  & pos);













