#include "mapManagement.h"
#include "terminalManagement.h"

using namespace std;


int main()
{
    mapGrid gameMap (31, mapLine (30, ' '));
    mapGrid pacMap;
    loadMapFromFile(pacMap, "../../../pacmanMap.txt");
    placeRoom(gameMap, pacMap, 1, 0);
    printGrid(gameMap);
    return 0;
}
