#ifndef TYPES_H
#define TYPES_H

#include <vector>
#include <string>

/**
 * @brief a vector of characters, representing a line of the map.
 */
typedef std::vector<char> mapLine;

/**
 * @brief a vector of mapLine, representing the game board/map
 */
typedef std::vector<mapLine> mapGrid;

typedef std::pair<unsigned, unsigned> CPosition;

struct playerInfo {
    std::string name;
    CPosition pos;
    unsigned steps;
};

struct enemyInfo {
    CPosition pos;
};

const unsigned KReset   = 0;
const unsigned KBlack   = 30;
const unsigned KRed     = 31;
const unsigned KGreen   = 32;
const unsigned KYellow  = 33;
const unsigned KBlue    = 34;
const unsigned KMagenta = 35;
const unsigned KCyan    = 36;

const char     KEmpty        = '_';
const char     KTokenPlayer1 = '@';
const unsigned KColorPlayer1 = KBlue;
const char     KTokenEnemy   = 'O';




#endif // TYPES_H
