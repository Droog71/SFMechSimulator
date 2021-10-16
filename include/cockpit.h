#ifndef COCKPIT_H
#define COCKPIT_H

#include <assets.h>
#include <SFML/Graphics.hpp>
#include <player_controller.h>

void draw_cockpit(sf::RenderWindow &window, assets &resources, player_controller &pc, bool took_damage);

#endif // COCKPIT_H
