#pragma once

#include <SFML/Graphics.hpp>

#include <iostream>

sf::VertexArray pointsToVertices(std::vector<sf::Vector2f> points, sf::Color color = sf::Color::Green);

void printVA(sf::VertexArray va);

void printPoints(std::vector<sf::Vector2f> points);

float dotProduct(sf::Vector2f point1, sf::Vector2f point2);

float norm(sf::Vector2f point);

sf::Vector2f normalize(sf::Vector2f point);

sf::Vector2f rotateVector90Left(sf::Vector2f point);

sf::Vector2f rotateVector90Right(sf::Vector2f point);

bool isPointLeftOfSegment(sf::Vector2f point, sf::Vector2f line1, sf::Vector2f line2);

bool isPointInsideConvexPolygon(sf::Vector2f point, std::vector<sf::Vector2f> polygon);

float radToDeg(float value);

float computeAngleBetweenVectors(sf::Vector2f point1, sf::Vector2f point2);