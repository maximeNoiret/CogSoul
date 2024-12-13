#include "mapManagement.h"

using namespace std;


int main()
{
    mapGrid gameMap (31, mapLine (28, ' '));
    loadMapFromFile(gameMap, "../../../pacmanMap.txt");
    return 0;
}
