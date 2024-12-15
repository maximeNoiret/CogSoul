#include "mapManagement.h"
#include "terminalManagement.h"

using namespace std;


int main()
{
    mapGrid gameMap (50, mapLine (80, ' '));
    mapGrid room;
    loadMapFromFile(room, "../../rooms/pacMap.txt");
    placeRoom(gameMap, room, 0, 0);
    loadMapFromFile(room, "../../rooms/roomTest.txt");
    placeRoom(gameMap, room, 27, 9);
    loadMapFromFile(room, "../../rooms/weirdShapeTest.txt");
    placeRoom(gameMap, room, 37, 9);
    loadMapFromFile(room, "../../rooms/idkLmao.txt");
    placeRoom(gameMap, room, 33, 19);
    printGrid(gameMap);
    return 0;
}
