#ifndef HUD_H
#define HUD_H

#include <assets.h>
#include <entity.h>
#include <SFML/Graphics.hpp>
#include <player_controller.h>

class hud
{
    public:
        std::string notice;
        bool show_notice;
        float notice_timer;
        void init(assets &resources);
        void display_notice(sf::RenderWindow &window, std::string notice, float frame_time);
        void draw_hud(sf::RenderWindow &window, float frame_time, int target_id, float speed, float torso_angle, mech &player_mech, mech &target_mech);

    private:
        assets resources;
        void draw_mech(float x_pos, mech &mech_to_draw, sf::RenderWindow &window);
};

#endif // HUD_H
