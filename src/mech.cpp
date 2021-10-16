#include <mech.h>
#include <string>
#include <iostream>

// Constructor
mech::mech()
{
    heat = 0;
    speed = 0;
    weapon = 0;
    weight = 70;

    cockpit_integrity = 1000;
    right_leg_integrity = 1000;
    left_leg_integrity = 1000;
    right_arm_integrity = 1000;
    left_arm_integrity = 1000;
    cooler_integrity = 1000;
    reactor_integrity = 1000;

    guns_modifier = 0;
    cannons_modifier = 0;
    cooler_modifier = 0;
    max_reactor_integrity = 1000;
    max_cooler_integrity = 1000;
    max_left_leg_integrity = 1000;
    max_right_leg_integrity = 1000;
    max_left_arm_integrity = 1000;
    max_right_arm_integrity = 1000;
    max_cockpit_integrity = 1000;

    primary_weapon = "Standard Pulse Laser";
    secondary_weapon = "Standard Autocannon";
    reactor = "Standard Reactor";
    cooler = "Standard Cooler";
    left_leg = "Standard Left Leg";
    right_leg = "Standard Right Leg";
    left_arm = "Standard Left Arm";
    right_arm = "Standard Right Arm";
    cockpit = "Standard Cockpit";

    is_player = false;
    power_down = false;
    taking_damage = false;
}

// Removes all damage from the mech
void mech::repair()
{
    power_down = false;
    heat = 0;
    cockpit_integrity = max_cockpit_integrity;
    right_leg_integrity = max_right_leg_integrity;
    left_leg_integrity = max_left_leg_integrity;
    right_arm_integrity = max_right_arm_integrity;
    left_arm_integrity = max_left_arm_integrity;
    cooler_integrity = max_cooler_integrity;
    reactor_integrity = max_reactor_integrity;
}

// Heat and damage calculations
void mech::update()
{
    if (heat >= 90)
    {
        reactor_integrity = reactor_integrity >= 1 ? reactor_integrity - 1 : 0;
    }

    float cooling = ((1 + cooler_modifier) * ((float)cooler_integrity / (float)max_cooler_integrity)) + 0.01;
    heat = heat > 0 ? heat - cooling : 0;

    if (taking_damage == true)
    {
        damage_timer++;
        if (damage_timer >= 100)
        {
            taking_damage = false;
            damage_timer = 0;
        }
    }
}

// Returns the total integrity of the mech
int mech::total_integrity()
{
    return reactor_integrity +
    cooler_integrity + right_arm_integrity +
    left_arm_integrity + right_leg_integrity +
    left_leg_integrity + cockpit_integrity;
}

// Returns the maximum total integrity of the mech
int mech::max_total_integrity()
{
    return max_reactor_integrity +
    max_cooler_integrity + max_right_arm_integrity +
    max_left_arm_integrity + max_right_leg_integrity +
    max_left_leg_integrity + max_cockpit_integrity;
}

// Returns true if the mech's legs are not destroyed
bool mech::can_move()
{
    return left_leg_integrity > 0 && right_leg_integrity > 0;
}

// Returns true if the mech's arms are not destroyed
bool mech::can_fire()
{
    return left_arm_integrity > 0 || right_arm_integrity > 0;
}

// Returns true if only the left arm has been destroyed
bool mech::left_arm_destroyed()
{
    return left_arm_integrity < 1 && right_arm_integrity > 0;
}

// Returns true if only the right arm has been destroyed
bool mech::right_arm_destroyed()
{
    return left_arm_integrity > 0 && right_arm_integrity < 1;
}

// Returns true if the mech's total integrity is less than 50% or the mech's reactor is destroyed
bool mech::destroyed()
{
    if (reactor_integrity < 1)
    {
        return true;
    }

    if (total_integrity() < max_total_integrity() / 2)
    {
        return true;
    }

    return false;
}

// Calculates damage dealt to the targeted component
void mech::take_damage(std::string target, float distance, int weapon)
{
    float dist_mod = weapon == 1 ? 0.05 : 0.01;
    taking_damage = true;
    damage_timer = 0;

    if (target == "reactor")
    {
        int damage_dealt = weapon * ((rand() % 10) - (distance * dist_mod) - (speed * 10));
        damage_dealt = damage_dealt > 0 ? damage_dealt : 0;
        reactor_integrity = reactor_integrity - damage_dealt > 0 ? reactor_integrity - damage_dealt : 0;
    }
    else if (target == "cooler")
    {
        int damage_dealt =  weapon * ((rand() % 20) - (distance * dist_mod) - (speed * 20));
        damage_dealt = damage_dealt > 0 ? damage_dealt : 0;
        cooler_integrity = cooler_integrity - damage_dealt > 0 ? cooler_integrity - damage_dealt : 0;
    }
    else if (target == "left arm")
    {
        int damage_dealt =  weapon * ((rand() % 30) - (distance * dist_mod) - (speed * 30));
        damage_dealt = damage_dealt > 0 ? damage_dealt : 0;
        left_arm_integrity = left_arm_integrity - damage_dealt > 0 ? left_arm_integrity - damage_dealt : 0;
    }
    else if (target == "right arm")
    {
        int damage_dealt =  weapon * ((rand() % 30) - (distance * dist_mod) - (speed * 30));
        damage_dealt = damage_dealt > 0 ? damage_dealt : 0;
        right_arm_integrity = right_arm_integrity - damage_dealt > 0 ? right_arm_integrity - damage_dealt : 0;
    }
    else if (target == "left leg")
    {
        int damage_dealt =  weapon * ((rand() % 40) - (distance * dist_mod) - (speed * 40));
        damage_dealt = damage_dealt > 0 ? damage_dealt : 0;
        left_leg_integrity = left_leg_integrity - damage_dealt > 0 ? left_leg_integrity - damage_dealt : 0;
    }
    else if (target == "right leg")
    {
        int damage_dealt =  weapon * ((rand() % 40) - (distance * dist_mod) - (speed * 40));
        damage_dealt = damage_dealt > 0 ? damage_dealt : 0;
        right_leg_integrity = right_leg_integrity - damage_dealt > 0 ? right_leg_integrity - damage_dealt : 0;
    }
    else if (target == "cockpit")
    {
        int damage_dealt =  weapon * ((rand() % 30) - (distance * dist_mod) - (speed * 30));
        damage_dealt = damage_dealt > 0 ? damage_dealt : 0;
        cockpit_integrity = cockpit_integrity - damage_dealt > 0 ? cockpit_integrity - damage_dealt : 0;
    }
}
