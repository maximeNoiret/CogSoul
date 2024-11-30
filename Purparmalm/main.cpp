#define FPS_LIMIT 60

#include <iostream>
#include <fstream>
#include <thread>

#include "mingl/mingl.h"

#include "mingl/shape/rectangle.h"
#include "mingl/shape/circle.h"
#include "mingl/shape/line.h"
#include "mingl/shape/triangle.h"

using namespace std;
using namespace nsShape;
using namespace nsGraphics;

typedef vector<unsigned> boardLine;
typedef vector<boardLine> Matrix;

struct pacman {
    nsShape::Circle body;
    nsShape::Triangle mouth;
    int mouthOpenness;
};

void setupPacman (pacman& pac) {
    pac.body = nsShape::Circle(nsGraphics::Vec2D(100, 400), 50, nsGraphics::KYellow);  // pacman body
    pac.mouth = nsShape::Triangle(
        pac.body.getPosition(),
        pac.body.getPosition() + nsGraphics::Vec2D(pac.body.getRadius(), pac.mouthOpenness),
        pac.body.getPosition() + nsGraphics::Vec2D(pac.body.getRadius(), 0) - nsGraphics::Vec2D(0, pac.mouthOpenness),
        nsGraphics::KSilver);
}

Line drawTop(const unsigned& tileSize, const unsigned& x, const unsigned& y) {
    return Line (Vec2D(x*tileSize, y*tileSize), Vec2D(x*tileSize+tileSize, y*tileSize), KBlue, 20);
}
Line drawRight(const unsigned& tileSize, const unsigned& x, const unsigned& y) {
    return Line (Vec2D(x*tileSize+tileSize, y*tileSize), Vec2D(x*tileSize+tileSize, y*tileSize+tileSize), KBlue, 20);
}
Line drawBottom(const unsigned& tileSize, const unsigned& x, const unsigned& y) {
    return Line (Vec2D(x*tileSize, y*tileSize+tileSize), Vec2D(x*tileSize+tileSize, y*tileSize+tileSize), KBlue, 20);
}
Line drawLeft(const unsigned& tileSize, const unsigned& x, const unsigned& y) {
    return Line (Vec2D(x*tileSize, y*tileSize), Vec2D(x*tileSize, y*tileSize+tileSize), KBlue, 20);
}


void generateMap(Matrix& gameBoard) {
    ifstream mapFile("map.txt");
    // WARNING: this assumes that the input file is formatted PERFECTLY. If it's not, boulette.
    for (boardLine& line : gameBoard) {
        for (unsigned& elem : line) {
            mapFile >> elem;
        }
    }
    mapFile.close();
}

void dessiner(MinGL &window)
{
    const unsigned tileSize = 64;  // must be diviser of 640
    if (window.getWindowSize().getX() % tileSize != 0) {
        cerr << "incorrect tileSize.";
        exit (1);
    }
    unsigned tileCount = window.getWindowSize().getX() / tileSize;

    Matrix gameBoard (tileCount, boardLine (tileCount));
    generateMap(gameBoard);
    vector<Line> lineMap;
    for (size_t y = 0; y < gameBoard.size(); ++y) {
        for (size_t x = 0; x < gameBoard[y].size(); ++x) {
            switch (gameBoard[y][x]) {
/*none*/        case 0: break;
/*top*/         case 1: lineMap.push_back(drawTop(tileSize, x, y)); break;
/*right*/       case 2: lineMap.push_back(drawRight(tileSize, x, y)); break;
/*bottom*/      case 3: lineMap.push_back(drawBottom(tileSize, x, y)); break;
/*left*/        case 4: lineMap.push_back(drawLeft(tileSize, x, y)); break;
/*top-left*/    case 5: lineMap.push_back(drawTop(tileSize, x, y)); lineMap.push_back(drawLeft(tileSize, x, y)); break;
/*top-right*/   case 6: lineMap.push_back(drawTop(tileSize, x, y)); lineMap.push_back(drawRight(tileSize, x, y)); break;
/*bottom-right*/case 7: lineMap.push_back(drawRight(tileSize, x, y)); lineMap.push_back(drawBottom(tileSize, x, y)); break;
/*bottom-left*/ case 8: lineMap.push_back(drawBottom(tileSize, x, y)); lineMap.push_back(drawLeft(tileSize, x, y)); break;
/*top-bottom*/  case 9: lineMap.push_back(drawTop(tileSize, x, y)); lineMap.push_back(drawBottom(tileSize, x, y)); break;
/*right-left*/  case 10: lineMap.push_back(drawRight(tileSize, x, y)); lineMap.push_back(drawLeft(tileSize, x, y)); break;
/*encase top*/  case 11: lineMap.push_back(drawTop(tileSize, x, y)); lineMap.push_back(drawRight(tileSize, x, y)); lineMap.push_back(drawLeft(tileSize, x, y)); break;
/*encase right*/case 12: lineMap.push_back(drawTop(tileSize, x, y)); lineMap.push_back(drawRight(tileSize, x, y)); lineMap.push_back(drawBottom(tileSize, x, y)); break;
/*encaseBottom*/case 13: lineMap.push_back(drawRight(tileSize, x, y)); lineMap.push_back(drawBottom(tileSize, x, y)); lineMap.push_back(drawLeft(tileSize, x, y)); break;
/*encase left*/ case 14: lineMap.push_back(drawTop(tileSize, x, y)); lineMap.push_back(drawBottom(tileSize, x, y)); lineMap.push_back(drawLeft(tileSize, x, y)); break;
/*square*/      case 15: lineMap.push_back(drawTop(tileSize, x, y)); lineMap.push_back(drawRight(tileSize, x, y)); lineMap.push_back(drawBottom(tileSize, x, y)); lineMap.push_back(drawLeft(tileSize, x, y)); break;
                default: cout << "Something probably went wrong with map input. Ignoring...";
            }
        }
    }

    window.clearScreen();
    for (const Line& line : lineMap)
        window << line;
    window.finishFrame();

    // while(true) {
    //     // game mainloop
    // }

}

int main()
{
    // Initialise le système
    MinGL window("Pacman lol", nsGraphics::Vec2D(640, 640), nsGraphics::Vec2D(128, 128), nsGraphics::KSilver);
    window.initGlut();
    window.initGraphic();



    // Variable qui tient le temps de frame
    chrono::microseconds frameTime = chrono::microseconds::zero();

    // On fait tourner la boucle tant que la fenêtre est ouverte
    while (window.isOpen())
    {
        // Récupère l'heure actuelle
        chrono::time_point<chrono::steady_clock> start = chrono::steady_clock::now();

        // On efface la fenêtre
        window.clearScreen();

        // On dessine les formes géométriques
        dessiner(window);

        // On finit la frame en cours
        window.finishFrame();

        // On vide la queue d'évènements
        window.getEventManager().clearEvents();

        // On attend un peu pour limiter le framerate et soulager le CPU
        this_thread::sleep_for(chrono::milliseconds(1000 / FPS_LIMIT) - chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start));

        // On récupère le temps de frame
        frameTime = chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start);
    }

    return 0;
}
