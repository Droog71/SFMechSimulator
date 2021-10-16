#ifndef CALC_HELPER_H
#define CALC_HELPER_H

#include <SFML/Graphics.hpp>

float get_angle(sf::Vector2f v1, sf::Vector2f v2);
float get_distance(sf::Vector2f v1, sf::Vector2f v2);
sf::Vector2f get_midpoint(sf::Vector2f v1, sf::Vector2f v2);
std::vector<sf::Vector2f> x_sort(std::vector<sf::Vector2f> vectors, int total);

#endif // CALC_HELPER_H
