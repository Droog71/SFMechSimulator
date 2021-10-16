#ifndef ENTITY_H
#define ENTITY_H

#include <mech.h>
#include <assets.h>
#include <calc_helper.h>
#include <SFML/Graphics.hpp>

class entity
{
    public:
        float draw_x;
        float draw_y;
        float move_x;
        float move_y;
        float distance;
        float old_pos;
        float think_timer;
        bool visible;
        bool firing;
        bool dying;
        bool dead;
        bool init;
        int id;
        int targeted_component;
        sf::Sprite sprite;
        sf::Sprite icon;
        sf::Vector2f position;
        std::string type;
        std::string sub_type;
        std::string components [7];
        entity();
        mech entity_mech;
        void fire_weapons(assets &resources);
        void update(sf::Vector2f camera_pos, bool maze);

    private:
        bool wall_blocking(sf::Vector2f camera_pos, bool maze);
        void avoid_walls(bool maze);
};

#endif // ENTITY_H
