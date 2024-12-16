#include "mapManagement.h"
#include "terminalManagement.h"

using namespace std;


int main()
{
    mapGrid gameMap (50, mapLine (80, ' '));
    mapGrid room;
    loadAndPlace(gameMap, "../../rooms/pacMap.txt", 0, 0);
    loadAndPlace(gameMap, "../../rooms/roomTest.txt", 27, 9);
    loadAndPlace(gameMap, "../../rooms/weirdShapeTest.txt", 37, 9);
    loadAndPlace(gameMap, "../../rooms/idkLmao.txt", 33, 19);
    printGrid(gameMap);
    return 0;
}
