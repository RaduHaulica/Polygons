#include "Game.h"

Game::Game(GameParameters gameConfiguration)
{
    config = gameConfiguration;
}

void Game::initialize()
{
    if (window != nullptr)
    {
        delete window;
    }
	window = new sf::RenderWindow(sf::VideoMode(1000, 1000), "Polygons!");

    currentPoints.clear();
    polygons.clear();

    dt = 0.f;
    clock.restart();

    mousePosition = { 0.f, 0.f };
    lastMousePosition = { 0.f, 0.f };

    isLeftMouseButtonPressed = false;
    isQuitGameRequested = false;

    selectedPolygonIndex = -1;

    pointCaptureCooldownInterval = 0.05f;
    pointCaptureCooldownAccumulator = 0.f;

    fixedTimeUpdateInterval = 1.f / 60.f;
    fixedTimeUpdateAccumulator = 0.f;
}

void Game::draw()
{
    // draw stuff
    window->clear();

    // in progress polygon
    if (currentPoints.size() > 0)
    {
        window->draw(pointsToVertices(currentPoints));
    }

    // finished polygons
    for (int i = 0; i < polygons.size(); i++)
    {
        //std::cout << "Drawing polygon with " << polygons[i].size() << " vertices\n";
        sf::VertexArray tempVA = pointsToVertices(polygons[i]);
        tempVA.setPrimitiveType(sf::PrimitiveType::Points);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::F1))
        {
            std::cout << "Drawing polygon with " << tempVA.getVertexCount() << " vertices\n";
            printVA(tempVA);
        }
        window->draw(tempVA);

        //// convex hulls
        //tempVA.clear();
        //tempVA.setPrimitiveType(sf::PrimitiveType::LineStrip);
        //tempVA = pointsToVertices(hulls[i], sf::Color::Blue);
        //window->draw(tempVA);

        sf::Color color = (collisions[i] == true) ? sf::Color::Red : sf::Color::Green;
        sf::VertexArray hullVA = pointsToVertices(hulls[i], color);
        hullVA.append(hullVA[0]);
        hullVA.setPrimitiveType(sf::PrimitiveType::LineStrip);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::F2))
        {
            std::cout << "Drawing convex hull with " << hullVA.getVertexCount() << " vertices\n";
            printVA(hullVA);
        }
        window->draw(hullVA);
    }

    // differences
    for (int i = 0; i < differences.size(); i++)
    {
        sf::VertexArray diffVA = pointsToVertices(differences[i], sf::Color::Blue);
        diffVA.setPrimitiveType(sf::PrimitiveType::LineStrip);
        window->draw(diffVA);
    }

    window->display();
}

void Game::run()
{
    while (window->isOpen())
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed || isQuitGameRequested)
                window->close();
        }

        // get delta time, mouse coords
        dt = clock.restart().asSeconds();
        mousePosition = sf::Vector2f(sf::Mouse::getPosition(*window));
        differences.clear();

        // collect input
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            isQuitGameRequested = true;
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && sf::Keyboard::isKeyPressed(sf::Keyboard::P))
        {
            isLeftMouseButtonPressed = true;
        }
        else
        {
            // current polygon is completed => store
            if (isLeftMouseButtonPressed && currentPoints.size() > 3)
            {
                std::cout << "Polygon added (" << currentPoints.size() << " points)\n";
                polygons.push_back(currentPoints);
                printPoints(currentPoints);

                std::vector<sf::Vector2f> hull = computeConvexHull(currentPoints);
                hulls.push_back(hull);

                collisions.push_back(false);

                currentPoints.clear();
            }

            isLeftMouseButtonPressed = false;
            pointCaptureCooldownAccumulator = 0.f;
        }

        if (!isLeftMouseButtonPressed && sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            if (selectedPolygonIndex == -1)
            {
				for (int i = 0; i < hulls.size(); i++)
				{
					if (isPointInsideConvexPolygon(mousePosition, hulls[i]))
					{
						selectedPolygonIndex = i;
					}
				}
            }
        }
        else
        {
            selectedPolygonIndex = -1;
        }

        // update stuff

        // create new points
        if (isLeftMouseButtonPressed)
        {
            pointCaptureCooldownAccumulator += dt;
            if (pointCaptureCooldownAccumulator > pointCaptureCooldownInterval)
            {
                if (mousePosition == lastMousePosition)
                {
                    ;
                }
                else
                {
                    pointCaptureCooldownAccumulator -= pointCaptureCooldownInterval;
					currentPoints.push_back(mousePosition);
                }
            }
        }

        // move selected polygon
        if (selectedPolygonIndex != -1)
        {
            sf::Vector2f offset = mousePosition - lastMousePosition;
            for (int i = 0; i < polygons[selectedPolygonIndex].size(); i++)
            {
                polygons[selectedPolygonIndex][i] += offset;
            }

            for (int i = 0; i < hulls[selectedPolygonIndex].size(); i++)
            {
                hulls[selectedPolygonIndex][i] += offset;
            }
        }

        // check for collisions
        if (hulls.size() > 1)
        {
            for (int i = 0; i < collisions.size(); i++)
            {
                collisions[i] = false;
            }

			for (int i = 0; i < hulls.size() - 1; i++)
			{
				for (int j = i + 1; j < hulls.size(); j++)
				{
                    // create minkowski difference
                    std::vector<sf::Vector2f> difference;
                    for (int it1 = 0; it1 < hulls[i].size(); it1++)
                    {
                        for (int it2 = 0; it2 < hulls[j].size(); it2++)
                        {
                            difference.push_back(hulls[i][it1] - hulls[j][it2]);
                        }
                    }

                    difference = computeConvexHull(difference);
                    differences.push_back(difference);

                    if (isPointInsideConvexPolygon({ 0.f, 0.f }, difference))
                    {
                        std::cout << "Collision!\n";
                        collisions[i] = true;
                        collisions[j] = true;
                    }
				}
			}
        }

        lastMousePosition = mousePosition;

        draw();
    }
}

void Game::reset()
{
    initialize();
}

Game::~Game()
{
    delete window;
}