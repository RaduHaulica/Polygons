#include "convex_hull.h"

ConvexHull::ConvexHull(std::vector<sf::Vector2f>& points):
	parentPoints{ points }
{
	if (points.size() < 3)
		throw "Points set not a valid polygon";


}

std::vector<sf::Vector2f> computeConvexHull(std::vector<sf::Vector2f> points)
{
    if (points.size() < 3)
    {
        return {};
    }

    // find lowest y point
    float lowestY = points[0].y;
    float lowestX = points[0].x;
    int index = 0;
    for (int i = 1; i < points.size(); i++)
    {
        // starting criterion lowest y, if multiple points take lowest x
        if (points[i].y < lowestY || (points[i].y == lowestY && points[i].x < lowestX))
        {
            lowestY = points[i].y;
            lowestX = points[i].x;
            index = i;
        }
    }
    std::swap<sf::Vector2f>(points[0], points[index]);
    // points[0] is the starting point now (P)

    // sort points by angle between (them and starting point P) to OX axis
    //printPointVectorAndAngles(points);

    // std::sort(points.begin() + 1 , points.end(), smallerAngleOX); // not good, no way to send in P offset
    for (int i = 1; i < points.size() - 1; i++)
    {
        for (int j = i + 1; j < points.size(); j++)
        {
            if (computeAngleBetweenVectors(points[j] - points[0], { 100.f, 0.f }) < computeAngleBetweenVectors(points[i] - points[0], { 100.f, 0.f }))
            {
                //std::swap<sf::Vector2f>(points[i], points[j]);
                sf::Vector2f temp = points[i];
                points[i] = points[j];
                points[j] = temp;
            }
        }
    }
    //printPointVectorAndAngles(points);

    // points are now sorted, starting algorithm
    int currentIndex = 1;
    while (currentIndex < points.size() - 1)
    {
        while (isPointLeftOfSegment(points[currentIndex + 1], points[currentIndex - 1], points[currentIndex]))
        {
            points.erase(points.begin() + currentIndex);
            currentIndex--;
        }
        currentIndex++;
    }

    return points;
}