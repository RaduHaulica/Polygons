#pragma once

#include <SFML/Graphics.hpp>

#include "Utility.h"

class ConvexHull
{
public:
	std::vector<sf::Vector2f>& parentPoints;

	ConvexHull(std::vector<sf::Vector2f>& points);
};

std::vector<sf::Vector2f> computeConvexHull(std::vector<sf::Vector2f> points);