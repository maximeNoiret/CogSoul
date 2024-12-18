#include <iostream>
#include <unistd.h>
#include "mapManagement.h"
#include "terminalManagement.h"
#include "entityController.h"

using namespace std;


int main()
{
    srand(time(NULL));
    mapGrid gameMap (50, mapLine (80, KEmpty));
    loadAndPlace(gameMap, "../../rooms/roomTest.txt", 27, 9);
    loadAndPlace(gameMap, "../../rooms/weirdShapeTest.txt", 37, 9);
    loadAndPlace(gameMap, "../../rooms/idkLmao.txt", 33, 19);

    set_input_mode();

    bool playerWon = false;

    playerInfo player = {inputName(), CPosition (11, 29), false, false, 0};
    vector<enemyInfo> enemies (3);
    enemies[0] = {CPosition (14, 30), false};
    enemies[1] = {CPosition (14, 31), false};
    enemies[2] = {CPosition (17, 32), false};

    gameMap[player.pos.first][player.pos.second] = KTokenPlayer1;  // set player in mat
    for (const enemyInfo& enemy : enemies)
        gameMap[enemy.pos.first][enemy.pos.second] = KTokenEnemy;  // set each enemy in mat
    // main gameLoop
    for (char input; !player.dead && !playerWon;) {
        clearScreen();
        generateRender(gameMap, 10, player);
        read(STDIN_FILENO, &input, 1);
        moveToken(gameMap, input, player.pos);
        moveEnemies(gameMap, player, enemies);
        player.seen = isPlayerSeen(gameMap, enemies, player);


    }
    if (player.dead) {
        clearScreen();
        cout << "A scientist found you!" << endl << "GAME OVER" << endl << endl;
    }
    return 0;
}
