#ifndef PLAYER_CONTROLLER_H
#define PLAYER_CONTROLLER_H

#include <assets.h>
#include <entity.h>
#include <settings.h>
#include <calc_helper.h>
#include <file_handler.h>
#include <key_bindings.h>
#include <SFML/Graphics.hpp>

class player_controller
{
    public:
        player_controller();
        key_bindings kb;
        mech player_mech;
        sf::Vector2f player_pos;
        sf::Vector2f look_pos;
        sf::Vector2f back_pos;
        sf::Vector2f left_pos;
        sf::Vector2f right_pos;
        std::vector<std::string> components;
        int credits;
        int credits_earned;
        int targeted_component;
        int target_id;
        int enemy_id;
        int mission;
        bool guns_firing;
        bool cannon_firing;
        bool player_firing;
        bool muzzle_flash;
        bool cannon_flash;
        bool hit_target;
        bool turn_left;
        bool turn_right;
        bool look_left;
        bool look_right;
        bool look_up;
        bool look_down;
        float muzzle_flash_timer;
        float cannon_flash_timer;
        float look_offset;
        float torso_angle;
        void reset();
        void init(std::string cwd, assets &resources);
        void collision_check(entity other, float view_range);
        void fire_guns(std::vector<entity> &entities, int entity_count, float window_width);
        void fire_cannon(std::vector<entity> &entities, int entity_count, float window_width);
        void lock_target(std::vector<entity> &entities, int entity_count, float window_width);
        void update(sf::RenderWindow &window, float frame_time);
        void handle_events(sf::RenderWindow &window, sf::Event event);
        void fixed_update(sf::Transformable player);

    private:
        assets resources;
        float stomp_timer;
        float step_timer;
        float mouse_move_timer;
        float guns_timer;
        float cannon_timer;
        bool move_forward;
        bool move_back;
        bool throttle_up;
        bool throttle_down;
        bool mouse_moved;
};

#endif
