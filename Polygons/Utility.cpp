#include "Utility.h"

sf::VertexArray pointsToVertices(std::vector<sf::Vector2f> points, sf::Color color)
{
    sf::VertexArray dots;
    for (int i = 0; i < points.size(); i++)
    {
        dots.append(sf::Vertex(points[i], color));
    }
    return dots;
}

void printVA(sf::VertexArray va)
{
    for (int i = 0; i < va.getVertexCount(); i++)
    {
        std::cout << "Vertex position: (" << va[i].position.x << ", " << va[i].position.y << ")\n";
    }
}

void printPoints(std::vector<sf::Vector2f> points)
{
    std::cout << "Printing points (size " << points.size() << ")\n";
    for (int i = 0; i < points.size(); i++)
    {
        std::cout << "(" << points[i].x << ", " << points[i].y << ") ";
    }
    std::cout << "\n";
}

float dotProduct(sf::Vector2f point1, sf::Vector2f point2)
{
    return point1.x * point2.x + point1.y * point2.y;
}

float norm(sf::Vector2f point)
{
    return sqrt(point.x * point.x + point.y * point.y);
}

sf::Vector2f normalize(sf::Vector2f point)
{
    return point / norm(point);
}

sf::Vector2f rotateVector90Left(sf::Vector2f point)
{
    // return {-point.y, point.x}; // Y axis is inverted so orthogonal rotation is inverted too
    return { point.y, -point.x };
}

sf::Vector2f rotateVector90Right(sf::Vector2f point)
{
    // return { point.y, -point.x }; // Y axis is inverted so orthogonal rotation is inverted too
    return { -point.y, point.x };
}

bool isPointLeftOfSegment(sf::Vector2f point, sf::Vector2f line1, sf::Vector2f line2)
{
    sf::Vector2f rotatedVector = rotateVector90Left(line2 - line1);
    point = point - line1;
    return dotProduct(point, rotatedVector) > 0;
}

bool isPointInsideConvexPolygon(sf::Vector2f point, std::vector<sf::Vector2f> polygon)
{
    if (polygon.size() < 3)
    {
        return false;
    }

    bool firstSegmentSide = isPointLeftOfSegment(point, polygon[0], polygon[1]);
    for (int i = 2; i < polygon.size(); i++)
    {
        if (firstSegmentSide != isPointLeftOfSegment(point, polygon[i - 1], polygon[i]))
        {
            return false;
        }
    }
    if (firstSegmentSide != isPointLeftOfSegment(point, polygon[polygon.size() - 1], polygon[0])) // last side is not in polygon vector
    {
        return false;
    }

    return true;
}

float radToDeg(float value)
{
    // pi = 180 deg
    float pi = 3.14159f;
    return value / pi * 180;
}

float computeAngleBetweenVectors(sf::Vector2f point1, sf::Vector2f point2)
{
    // P1 dot P2 = norm(P1)*norm(P2)*cos angle
    return radToDeg(std::acos(dotProduct(point1, point2) / (norm(point1) * norm(point2))));
}