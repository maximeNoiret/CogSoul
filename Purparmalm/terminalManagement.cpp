#include <iostream>
#include "types.h"

using namespace std;

void printVect(const vector<char>& vect) {
    for (const char & elem : vect)
        cout << elem;
    cout << endl;
}

void printGrid(const mapGrid& gameMap) {
    for (const mapLine& lin : gameMap)
        printVect(lin);
}
