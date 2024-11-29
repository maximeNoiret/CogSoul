#define FPS_LIMIT 60

#include <iostream>
#include <thread>

#include "mingl/mingl.h"

#include "mingl/shape/rectangle.h"
#include "mingl/shape/circle.h"
#include "mingl/shape/line.h"
#include "mingl/shape/triangle.h"

using namespace std;

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

void dessiner(MinGL &window/*, nsShape::Circle& body, nsShape::Triangle& mouth*/)
{
    nsShape::Triangle triangle0(nsGraphics::Vec2D(100, 100), nsGraphics::Vec2D(150, 100), nsGraphics::Vec2D(125, 50), nsGraphics::KCyan);
    nsShape::Triangle triangle1 = triangle0 + nsGraphics::Vec2D(60, 0);

    window << triangle0 << triangle1;

    nsShape::Circle cercle0(nsGraphics::Vec2D(100, 200), 50, nsGraphics::KRed);
    nsShape::Circle cercle2 = cercle0 + nsGraphics::Vec2D(110, 0);
    nsShape::Circle cercle3 = cercle2 + nsGraphics::Vec2D(110, 0);

    window << cercle0 << cercle2 << cercle3;

    pair<unsigned, unsigned> pos = {100, 400};
    int mouthOpenness = 50;
    nsShape::Circle body(nsGraphics::Vec2D(pos.first, pos.second), 25, nsGraphics::KYellow);  // pacman body
    nsShape::Triangle mouth(
        body.getPosition(),
        body.getPosition() + nsGraphics::Vec2D(body.getRadius(), mouthOpenness),
        body.getPosition() + nsGraphics::Vec2D(body.getRadius(), 0) - nsGraphics::Vec2D(0, mouthOpenness),
        nsGraphics::KSilver);
    nsShape::Circle eye(nsGraphics::Vec2D(pos.first - (body.getRadius() / 2), pos.second - (body.getRadius() / 2)), (body.getRadius() / 5), nsGraphics::KBlack);
    bool closing = true;
    while(true) {
        this_thread::sleep_for(20ms);
        window.clearScreen();
        pos.first += 1;

        // update pacman position
        body.setPosition(nsGraphics::Vec2D(pos.first, pos.second));
        mouth.setFirstPosition(body.getPosition());
        mouth.setSecondPosition(body.getPosition() + nsGraphics::Vec2D(body.getRadius(), mouthOpenness));
        mouth.setThirdPosition(body.getPosition() + nsGraphics::Vec2D(body.getRadius(), 0) - nsGraphics::Vec2D(0, mouthOpenness));
        eye.setPosition(nsGraphics::Vec2D(pos.first - (body.getRadius() / 2), pos.second - (body.getRadius() / 2)));

        // update mouth openness
        if (closing) {
            if (mouthOpenness <= 0)
                closing = false;
            else
                mouthOpenness -= 5;
        } else {
            if (unsigned(mouthOpenness) >= body.getRadius())
                closing = true;
            else
                mouthOpenness += 5;
        }

        window << body << mouth << eye;
        window.finishFrame();
    }


    window << body << mouth;
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
