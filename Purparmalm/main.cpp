#include <iostream>
#include <unistd.h>
#include "mapManagement.h"
#include "terminalManagement.h"
#include "playerController.h"

using namespace std;


int main()
{
    mapGrid gameMap (50, mapLine (80, KEmpty));
    loadAndPlace(gameMap, "../../rooms/roomTest.txt", 27, 9);
    loadAndPlace(gameMap, "../../rooms/weirdShapeTest.txt", 37, 9);
    loadAndPlace(gameMap, "../../rooms/idkLmao.txt", 33, 19);

    set_input_mode();

    bool playerDead = false;
    bool playerWon = false;

    playerInfo player = {"inputName()", CPosition (11, 29), 0};
    vector<enemyInfo> enemies (3);
    enemies[0] = {CPosition (12, 30)};
    enemies[1] = {CPosition (14, 31)};
    enemies[2] = {CPosition (17, 32)};

    // main gameLoop
    gameMap[player.pos.first][player.pos.second] = KTokenPlayer1;
    for (const enemyInfo& enemy : enemies)
        gameMap[enemy.pos.first][enemy.pos.second] = KTokenEnemy;
    for (char input; !playerDead && !playerWon;) {
        clearScreen();
        generateRender(gameMap, 10, player);
        read(STDIN_FILENO, &input, 1);
        moveToken(gameMap, input, player);
    }
    return 0;
}
