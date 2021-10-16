#include <calc_helper.h>
#include <SFML/Graphics.hpp>
#include <math.h>
#include <entity.h>

// Returns the distance between two vectors
float get_distance(sf::Vector2f v1, sf::Vector2f v2)
{
    float xdif = v2.x - v1.x;
    float ydif = v2.y - v1.y;
    float xdifsqrd = xdif * xdif;
    float ydifsqrd = ydif * ydif;
    return sqrt(xdifsqrd + ydifsqrd);
}

// Returns the midpoint between two vectors
sf::Vector2f get_midpoint(sf::Vector2f v1, sf::Vector2f v2)
{
    float xmid = (v1.x + v2.x) / 2;
    float ymid = (v1.y + v2.y) / 2;
    sf::Vector2f vmid(xmid, ymid);
    return vmid;
}

// Returns the angle between two vectors
float get_angle(sf::Vector2f v1, sf::Vector2f v2)
{
   return atan2(v2.y - v1.y, v2.x - v1.x) * (180 / 3.14);
}

// Sorts vectors based on their position along the x axis
std::vector<sf::Vector2f> x_sort(std::vector<sf::Vector2f> vectors, int total)
{
    sf::Vector2f temp_vector;
    int current_index, next_index;
    for(current_index = 0; current_index < total; current_index++)
    {
        for(next_index = current_index + 1; next_index < total; next_index++)
        {
            if(vectors[current_index].x > vectors[next_index].x)
            {
                temp_vector = vectors[current_index];
                vectors[current_index] = vectors[next_index];
                vectors[next_index] = temp_vector;
            }
        }
    }
    return vectors;
}
