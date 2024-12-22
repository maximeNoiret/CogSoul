#ifndef TYPES_H
#define TYPES_H

#include <array>
#include <vector>
#include <string>
#include <map>

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
    bool seen = false;
    bool dead = false;
    unsigned steps = 0;
};

struct enemyInfo {
    CPosition pos;
    bool sees = false;
};

// const unsigned KReset   = 0;
// const unsigned KBlack   = 30;
// const unsigned KRed     = 31;
// const unsigned KGreen   = 32;
// const unsigned KYellow  = 33;
// const unsigned KBlue    = 34;
// const unsigned KMagenta = 35;
// const unsigned KCyan    = 36;

const std::map<std::string, unsigned> Colors = {
    {"Reset", 0},
    {"Black", 30},
    {"Red", 31},
    {"Green", 32},
    {"Yellow", 33},
    {"Blue", 34},
    {"Magenta", 35},
    {"Cyan", 36}
};

struct settings {
    char        KEmpty        = '_';
    char        KTokenPlayer1 = '@';
    std::string KColorPlayer1 = "Cyan";
    char        KTokenEnemy   = 'O';
    std::string KColorEnemy   = "Red";
};

// using arrays to save on ressources (I think lmao)
const std::array<char, 4> possibleMoves = {'z', 'q', 's', 'd'};
const std::array<std::string, 3> roomsUp = {"testRoomUp.txt", "anotherRoom.txt", "roomTest.txt"};
const std::array<std::string, 1> roomsRight = {"roomTest.txt"};
const std::array<std::string, 0> roomsDown = {};
const std::array<std::string, 2> roomsLeft = {"anotherRoom.txt", "roomTest.txt"};


#endif // TYPES_H
