#ifndef MECH_H
#define MECH_H

#include <string>

class mech
{
    public:
        mech();

        int weapon;
        int weight;

        int reactor_integrity;
        int cooler_integrity;
        int left_leg_integrity;
        int right_leg_integrity;
        int left_arm_integrity;
        int right_arm_integrity;
        int cockpit_integrity;
        int total_integrity();

        int cooler_modifier;
        int guns_modifier;
        int cannons_modifier;
        int max_reactor_integrity;
        int max_cooler_integrity;
        int max_left_leg_integrity;
        int max_right_leg_integrity;
        int max_left_arm_integrity;
        int max_right_arm_integrity;
        int max_cockpit_integrity;
        int max_total_integrity();

        std::string primary_weapon;
        std::string secondary_weapon;
        std::string reactor;
        std::string cooler;
        std::string left_leg;
        std::string right_leg;
        std::string left_arm;
        std::string right_arm;
        std::string cockpit;

        float heat;
        float speed;
        float damage_timer;
        bool is_player;
        bool power_down;
        bool taking_damage;
        bool can_move();
        bool can_fire();
        bool destroyed();
        bool left_arm_destroyed();
        bool right_arm_destroyed();
        void update();
        void repair();
        void take_damage(std::string target, float distance, int weapon);
};

#endif // MECH_H
