#include <SFML/Graphics.hpp>

#include <iostream>

#include "Config.h"
#include "Game.h"
#include "convex_hull.h"

//1. Creat poligon convex. (convex hull)
//2. Determinare punct in poligon
//3. Apucat si mutat poligonul
//4. Detectie de coliziune cu GJK : Mai intai o varianta simplifcata si apoi the real deal!
//
//Varianta simplificata este fara simplexuri, direct originea este in diferenta Minkowsky ?

int main()
{
    GameParameters gameConfiguration;

    Game game(gameConfiguration);
    game.initialize();
    game.run();

    return 0;
}