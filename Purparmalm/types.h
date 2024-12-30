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

// logs placed in namespace to avoid boulettes (I know global vars are bad and accept the -1)
// dunno if this still applies since now there's only functions? since logs is still in the namespace?
namespace Logs {
    void addLog(const std::string& log);
    void setLog(const size_t& pos, const std::string& log);
    const std::vector<std::string>& getLogs();
}

struct playerInfo {
    std::string name;
    CPosition pos;
    bool seen = false;
    bool dead = false;
};


struct enemyInfo {
    CPosition pos;
    bool sees = false;
};

/**
 * @brief map containing each color and their terminal value equivalent
 */
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
    std::string KColorEnemy   = "Red";
    std::string KColorPlayer1 = "Cyan";
    char        KEmpty        = '_';
    char        KTokenEnemy   = 'O';
    char        KTokenPlayer1 = '@';
    unsigned    KOutBox       = 3;  // 0=none,1=ascii,2=single,3=double
    bool        KSkipIntro    = false;
};

// using arrays to save on ressources (I think lmao)
const std::array<char, 4> possibleMoves = {'z', 'q', 's', 'd'};
const std::array<std::string, 3> roomsUp = {"testRoomUp.txt", "anotherRoom.txt", "roomTest.txt"};
const std::array<std::string, 1> roomsRight = {"roomTest.txt"};
const std::array<std::string, 0> roomsDown = {};
const std::array<std::string, 2> roomsLeft = {"anotherRoom.txt", "roomTest.txt"};


#endif // TYPES_H
