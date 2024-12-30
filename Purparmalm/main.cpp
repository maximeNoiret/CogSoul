#include <iostream>
#include <unistd.h>
#include "mapManagement.h"
#include "terminalManagement.h"
#include "entityController.h"
#include "settingsManagement.h"

using namespace std;


int mainGame(const settings& config)
{
    srand(time(NULL));
    mapGrid gameMap (50, mapLine (80, config.KEmpty));
    loadAndPlace(gameMap, "rooms/testProceduralDoors.txt", 35, 20, config);

    set_input_mode();

    bool playerWon = false;

    playerInfo player = {inputName(), CPosition (25, 40), false, false};
    vector<enemyInfo> enemies (3);
    // enemies[0] = {CPosition (14, 30), false};
    // enemies[1] = {CPosition (14, 31), false};
    // enemies[2] = {CPosition (17, 32), false};

    gameMap[player.pos.first][player.pos.second] = config.KTokenPlayer1;  // set player in mat
    for (const enemyInfo& enemy : enemies)
        gameMap[enemy.pos.first][enemy.pos.second] = config.KTokenEnemy;  // set each enemy in mat
    // main gameLoop
    for (char input = 0; !player.dead && !playerWon && input != 27;) {
        clearScreen();
        generateRender(gameMap, 10, player, config);
        read(STDIN_FILENO, &input, 1);
        moveToken(gameMap, input, player.pos, config);
        moveEnemies(gameMap, player, enemies, config);
        player.seen = isPlayerSeen(gameMap, enemies, player, config);
    }
    if (player.dead) {
        clearScreen();
        cout << "A scientist found you!" << endl << "GAME OVER" << endl << endl;
    }
    return 0;
}



int main() {
    settings config;
    initSettings(config);
    set_input_mode();
    // Lore logs
    for(unsigned short select = 0;select < 2;) {
        select = mainMenu();
        switch(select) {
        case 0:
            mainGame(config);
            break;
        case 1:
            settingsMenu(config);
            break;
        }
    }
    clearScreen();
    return 0;
}

