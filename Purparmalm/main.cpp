#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

typedef vector<char> mapLine;
typedef vector<mapLine> mapGrid;

template<typename T>
void printVect(const T& vect) {
    for (const T& elem : vect)
        cout << elem << '\t';
    cout << endl;
}

void printGrid(const mapGrid& gameMap) {
    for (const mapLine lin : gameMap)
        printVect(lin);
}

void loadMapFromFile(mapGrid& gameMap, const string& fileName) {
    ifstream mapFile (fileName);
    string input;
    for (size_t i = 0; getline(fileName, input); ++i) {
        gameMap[i].resize(0);
        for (const char& car : input) {
            gameMap[i].push_back(car);
        }
    }
    printGrid(gameMap);
}

int main()
{
    mapGrid gameMap (31, mapLine (28, ' '));
    loadMapFromFile(gameMap, "../pacmanMap.txt");
    return 0;
}
