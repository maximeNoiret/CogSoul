/**
 * @author Noiret Maxime
 */

#include <iostream>
#include <unistd.h>
#include "mapManagement.h"
#include "terminalManagement.h"
#include "entityController.h"
#include "settingsManagement.h"

using namespace std;

// PLEASE TELL ME, IS THERE A WAY TO HAVE ACCESS TO config WITHOUT PUTTING IT EVERY FUCKING WHERE?????
// without just doing a global variable cuz I heard those suck lmao

int mainGame(settings& config)
{
    srand((config.KSeed.size() == 0 || !isdigit(config.KSeed[0]) ? time(NULL) : stoul(config.KSeed)));  // ToDo: add better seed system
    mapGrid gameMap (50, mapLine (80, config.KEmpty));

    set_input_mode();

    bool playerWon = false;

    playerInfo player = {inputName(), CPosition (gameMap.size() * 0.5, gameMap[0].size() * 0.5), false, false};
    vector<enemyInfo> enemies;
    loadAndPlace(gameMap, "rooms/testProceduralDoors.txt", 35, 20, config, enemies);

    gameMap[player.pos.first][player.pos.second] = config.KTokenPlayer1;  // set player in mat

    // intro sequence
    Logs::setLog(0, "LOGS_2078-04-29_23-12-09.2408751");
    Logs::setLog(1, "Initializing...");
    Logs::setLog(2, "Visual Sensors...");
    for (size_t i = 3; i < 8; ++i)
        Logs::setLog(i, "");
    if (!config.KSkipIntro) {
        introSequence(gameMap, player, config, enemies);
        cin.ignore();
    } else {
        Logs::setLog(2, "Visual Sensors... \033[32mOK\033[0m");
        Logs::setLog(3, "Motion Sensors... \033[32mOK\033[0m");
        Logs::setLog(4, "AI... \033[31mERROR\033[0m");
        Logs::setLog(5, "Attempting Troubleshoot... \033[31mERROR\033[0m");
        Logs::setLog(6, "\033[33mBig boulette detected!\033[0m");
        Logs::setLog(7, "Attempting Shutdown... \033[31mERROR\033[0m");
    }

    // main gameLoop
    pair<unsigned, unsigned> terminal_size;
    for (char input = 0; !player.dead && !playerWon;) {
        clearScreen();
        terminal_size = get_terminal_size();
        if (terminal_size.first < 24 || terminal_size.second < 80) {
            renderIncorrectSize();
            milSleep(100);
        } else {
            generateRender(gameMap, 10, player, config, enemies);
            read(STDIN_FILENO, &input, 1);
            if (input == 27) {
                pauseMenu(config);
            }
            moveToken(gameMap, input, player.pos, config, enemies);
            moveEnemies(gameMap, player, enemies, config);
            player.seen = isPlayerSeen(gameMap, enemies, player, config);
        }
    }

    if (player.dead) {
        clearScreen();
        cout << "A scientist caught you!" << endl << "GAME OVER" << endl << endl;
    }
    return 0;
}



int main() {
    settings config;
    initSettings(config);
    set_input_mode();
    // Lore logs
    for(unsigned short select = 0;select < 3;) {
        select = mainMenu(config);
        switch(select) {
        case 0:
            mainGame(config);
            break;
        case 1:
            helpMenu(config);
            break;
        case 2:
            settingsMenu(config);
            break;
        }
    }
    clearScreen();
    return 0;
}

