/*
    Author(s) : FUSELIER Jules | SAE 1.01 | PACMAN GAME
    Collaborator(s) : BREST-LESTRADE Hugo
*/

#define FPS_LIMIT 60

#include <iostream>
#include <thread>

#include "mingl/mingl.h"

#include "mingl/shape/rectangle.h"
#include "mingl/shape/circle.h"
#include "mingl/shape/line.h"
#include "mingl/shape/triangle.h"
#include "mingl/transition/transition_engine.h"

using namespace std;
using namespace nsShape;
using namespace nsGraphics;

void dessiner(MinGL &window)
{
    // // Pour dessiner quelque chose avec minGL 2, vous pouvez soit instancier l'objet dans une variable et l'injecter dans la fenêtre...
    // nsShape::Rectangle rect1(nsGraphics::Vec2D(20, 20), nsGraphics::Vec2D(120, 120), nsGraphics::KBlue);
    // window << (rect1 *0.5 + nsGraphics::Vec2D(120, 120));

    // // ...ou l'injecter directement dans la fenêtre!
    // window << nsShape::Rectangle(nsGraphics::Vec2D(30, 30), nsGraphics::Vec2D(160, 160), nsGraphics::KPurple);

    // // (Vous voyez par ailleurs que l'ordre d'affichage est important, le rectangle violet masque maintenant une partie du rectangle bleu.)
    // // Vous pouvez combiner les différentes formes disponibles pour faire des choses plus complexes.

    // // Voilà un bouton de fermeture.
    // window << nsShape::Circle(nsGraphics::Vec2D(100, 320), 50, nsGraphics::KRed);
    // window << nsShape::Line(nsGraphics::Vec2D(70, 290), nsGraphics::Vec2D(130, 300), nsGraphics::KWhite, 3.f);
    // window << nsShape::Line(nsGraphics::Vec2D(130, 290), nsGraphics::Vec2D(70, 300), nsGraphics::KWhite, 3.f);

    // // Et voilà la triforce.
    // window << nsShape::Triangle(nsGraphics::Vec2D(200, 620), nsGraphics::Vec2D(400, 620), nsGraphics::Vec2D(300, 420), nsGraphics::KYellow);
    // window << nsShape::Triangle(nsGraphics::Vec2D(400, 620), nsGraphics::Vec2D(600, 620), nsGraphics::Vec2D(500, 420), nsGraphics::KYellow);
    // window << nsShape::Triangle(nsGraphics::Vec2D(300, 420), nsGraphics::Vec2D(500, 420), nsGraphics::Vec2D(400, 220), nsGraphics::KYellow);


    MyMap =




    Circle corps(Vec2D(320,360),10,KYellow);
    //Triangle bouche(Vec2D(300,300),Vec2D(400,200),Vec2D(400,400),KBlack);
    Circle oeil (Vec2D(325,358),2, KBlack);
    //Triangle bouche_fermee(Vec2D(300,300),Vec2D(400,280),Vec2D(320,320),KBlack);

    // BORDERS OF THE WINDOW
    Line barrier1(Vec2D(0,0),Vec2D(0,640),KBlue,10);
    Line barrier2(Vec2D(0,640),Vec2D(640,640),KBlue,10);
    Line barrier3(Vec2D(640,640),Vec2D(640,0),KBlue,1.5);
    Line barrier4(Vec2D(0,0),Vec2D(640,0),KBlue,1.5);

    //BOX OF FANTOMS
    Line boxTopBarrierOfPhantoms(Vec2D(275,275),Vec2D(365,275),KSilver,3);
    Line boxRightBarrierOfPhantoms(Vec2D(365,275),Vec2D(365,340),KSilver,3);
    Line boxDownBarrierOfPhantoms(Vec2D(275,340),Vec2D(365,340),KSilver,3);
    Line boxLeftBarrierOfPhantoms(Vec2D(275,340),Vec2D(275,275),KSilver,3);

    // CORRIDORS

    Line firstWall(Vec2D(275,380), Vec2D(365,380),KBlue, 5);

    for (unsigned i(0); i < 10; ++i){
        window.clearScreen();
        window << barrier1;
        window << barrier2;
        window << barrier3;
        window << barrier4;

        window << boxTopBarrierOfPhantoms;
        window << boxRightBarrierOfPhantoms;
        window << boxDownBarrierOfPhantoms;
        window << boxLeftBarrierOfPhantoms;

        window << firstWall;

        i = 0; // bien mon toutou
        if(i%2 ==0){
            window << corps + Vec2D(10*i,0);
            //window << bouche_fermee + Vec2D(10*i,0);
            window << oeil + Vec2D(10*i,0);

        }
        else{
            window << corps + Vec2D(10*i,0);
            //window << bouche + Vec2D(10*i,0);
            window << oeil + Vec2D(10*i,0);
        }
        window.finishFrame();

        this_thread::sleep_for(500ms);


    }

    // N'hésitez pas a lire la doc pour plus de détails.
}

int main()
{
    // Initialise le système
    MinGL window("Casalite", nsGraphics::Vec2D(640, 640), nsGraphics::Vec2D(128, 128), nsGraphics::KBlack);
    window.initGlut();
    window.initGraphic();



    // nsTransition::TransitionEngine transitionEngine;

    // // On démarre une premiere transition simple, qui change le rayon du cercle a 48 pixels pendant 10 secondes
    // transitionEngine.startContract(nsTransition::TransitionContract(corps, corps.TRANSITION_RADIUS, chrono::seconds(10), {48}));
    // transitionEngine.startContract(nsTransition::TransitionContract(bouche, bouche.TRANSITION_RADIUS, chrono::seconds(10), {400,400}));
    // transitionEngine.startContract(nsTransition::TransitionContract(oeil, oeil.TRANSITION_RADIUS, chrono::seconds(10), {48}));

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
