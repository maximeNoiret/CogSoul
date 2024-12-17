#include "mapManagement.h"
#include "terminalManagement.h"
#include <iostream>
#include <unistd.h>

using namespace std;


int main()
{
    mapGrid gameMap (50, mapLine (80, KEmpty));
    mapGrid room;
    loadAndPlace(gameMap, "../../rooms/roomTest.txt", 27, 9);
    loadAndPlace(gameMap, "../../rooms/weirdShapeTest.txt", 37, 9);
    loadAndPlace(gameMap, "../../rooms/idkLmao.txt", 33, 19);
    printGrid(gameMap);
    // ToDo: include player controller with termios
    set_input_mode();
    bool playerDead = false;
    bool playerWon = false;
    string playerName;
    // dumb af code :)
    char input = 0;
    short len = 0;
    for (;;) {
        string nameDisplay (5, '_');
        for (size_t i = 0; i < playerName.size(); ++i)
            nameDisplay[i] = playerName[i];
        clearScreen();
        cout << '\t';
        for (const char& letter : nameDisplay)
            cout << letter << ' ';
        cout << endl << "Enter your name:" << endl;
        if (len == 5) break;
        read(STDIN_FILENO, &input, 1);
        if (input == 10) break;
        if (input == 127) {
            playerName.erase(playerName.size()-1);
            --len;
        } else {
            playerName += input;
            ++len;
        }
    }
    // for (char input; !playerDead && !playerWon;) {

    // }
    return 0;
}
