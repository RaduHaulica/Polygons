#pragma once

#include "Config.h"
#include "Utility.h"
#include "convex_hull.h"

class Game
{
public:
    // containers
    sf::RenderWindow* window;
    std::vector<sf::Vector2f> currentPoints;
    std::vector<std::vector<sf::Vector2f>> polygons;
    std::vector<std::vector<sf::Vector2f>> hulls;
    std::vector<std::vector<sf::Vector2f>> differences;
    std::vector<bool> collisions;

    GameParameters config;
    float dt{ 0.f };
    sf::Clock clock;
    sf::Vector2f lastMousePosition;
    sf::Vector2f mousePosition;

    // text
    sf::Font defaultFont;
    sf::Text mainTextBlob;

    // misc game flags
    bool isLeftMouseButtonPressed{ false };
    bool isQuitGameRequested{ false };

    int selectedPolygonIndex{ -1 };


    // update related
    float pointCaptureCooldownInterval{ 0.05f };
    float pointCaptureCooldownAccumulator{ 0.f };

    float fixedTimeUpdateInterval = 1.f / 60.f;
    float fixedTimeUpdateAccumulator{ 0.f };

    Game(GameParameters gameConfiguration);
    ~Game();

    void initialize();

	void update(float dt);

    void draw();

    void run();

    void reset();
};