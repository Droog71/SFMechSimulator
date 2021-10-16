#include <math.h>
#include <iostream>
#include <entity.h>
#include <settings.h>

entity::entity()
{
    id = 0;
    draw_x = 0;
    draw_y = 0;
    move_x = 0;
    move_y = 0;
    old_pos = 0;
    distance = 0;
    think_timer = 0;
    targeted_component = 0;

    dead = false;
    init = false;
    dying = false;
    firing = false;
    visible = false;

    components[0] = "reactor";
    components[1] = "cooler";
    components[2] = "left arm";
    components[3] = "right arm";
    components[4] = "left leg";
    components[5] = "right leg";
    components[6] = "cockpit";
}

// Prevents mobs from running into walls
void entity::avoid_walls(bool maze)
{
    if (position.x < 65)
    {
        position.x += 1;
    }

    if (position.x > 545)
    {
        position.x -= 1;
    }

    if (position.y < 45)
    {
        position.y += 1;
    }

    if (position.y > 645)
    {
        position.y -= 1;
    }

    if (maze == true)
    {
        if (position.x < 300 && position.y > 395)
        {
            position.y -= 1;
        }

        if (position.x > 175 && position.x < 180 && position.y < 280)
        {
            position.x -= 1;
            position.y += 5;
        }

        if (position.x < 185 && position.x > 180 && position.y < 280)
        {
            position.x += 1;
            position.y += 5;
        }

        if (position.x > 295 && position.x < 300 && position.y > 150)
        {
            position.x -= 1;
            position.y -= 5;
        }

        if (position.x > 300 && position.x < 305 && position.y > 150)
        {
            position.x += 1;
            position.y -= 5;
        }

        if (position.x > 415 && position.x < 420 && position.y < 520)
        {
            position.x -= 1;
            position.y += 5;
        }

        if (position.x > 420 && position.x < 425 && position.y < 520)
        {
            position.x += 1;
            position.y += 5;
        }
    }
}

// Returns true if there is a wall between this entity and the player
bool entity::wall_blocking(sf::Vector2f camera_pos, bool maze)
{
    if (maze == false)
    {
        return false;
    }

    if (camera_pos.x < 180 && position.x > 180 && position.y < 280)
    {
        return true;
    }

    if (camera_pos.x > 180 && position.x < 180 && position.y < 280)
    {
        return true;
    }

    if (camera_pos.x < 300 && position.x > 300 && position.y > 150)
    {
        return true;
    }

    if (camera_pos.x > 300 && position.x < 300 && position.y > 150)
    {
        return true;
    }

    if (camera_pos.x < 420 && position.x > 420 && position.y < 520)
    {
        return true;
    }

    if (camera_pos.x > 420 && position.x < 420 && position.y < 520)
    {
        return true;
    }

    return false;
}

// NPC mech weapons firing
void entity::fire_weapons(assets &resources)
{
    if (sprite.getTexture() == &resources.mech_texture)
    {
        if (entity_mech.weapon == 1)
        {
            if (entity_mech.left_arm_destroyed() == true)
            {
                sprite.setTexture(resources.mech_fire_guns_right_texture);
            }
            else if (entity_mech.right_arm_destroyed() == true)
            {
                sprite.setTexture(resources.mech_fire_guns_left_texture);
            }
            else
            {
                sprite.setTexture(resources.mech_fire_guns_texture);
            }

            resources.gun_sound.setVolume(25 * audio_volume);
            resources.gun_sound.play();

            float heat_gen = entity_mech.heat + 10 + entity_mech.guns_modifier;
            entity_mech.heat = entity_mech.heat >= 90 ? 100 : heat_gen;
        }
        else
        {
            if (entity_mech.left_arm_destroyed() == true)
            {
                sprite.setTexture(resources.mech_fire_cannons_right_texture);
            }
            else if (entity_mech.right_arm_destroyed() == true)
            {
                sprite.setTexture(resources.mech_fire_cannons_left_texture);
            }
            else
            {
                sprite.setTexture(resources.mech_fire_cannons_texture);
            }

            resources.cannon_sound.setVolume(25 * audio_volume);
            resources.cannon_sound.play();

            float heat_gen = entity_mech.heat + 50 + entity_mech.cannons_modifier;
            entity_mech.heat = entity_mech.heat >= 50 ? 100 : heat_gen;
        }
        firing = false;
    }
}

// Handles npc logic
void entity::update(sf::Vector2f camera_pos, bool maze)
{
    if (type == "mob" && sub_type == "mech")
    {
        think_timer++;

        if (think_timer >= 10)
        {
            float camera_range = get_distance(camera_pos, position);

            if (entity_mech.can_move() == true)
            {
                int leg_integrity = entity_mech.left_leg_integrity + entity_mech.right_leg_integrity;
                entity_mech.speed = camera_range > 60 ? leg_integrity * 0.00002 : leg_integrity * 0.00001;
                float dir = entity_mech.speed;

                if (entity_mech.taking_damage == true || entity_mech.heat >= 50)
                {
                    dir = -entity_mech.speed;
                }

                if (position.x < camera_pos.x)
                {
                    move_x = dir;
                }

                if (position.x > camera_pos.x)
                {
                    move_x = -dir;
                }

                if (position.y < camera_pos.y)
                {
                    move_y = dir;
                }

                if (position.y > camera_pos.y)
                {
                    move_y = -dir;
                }
            }
            else
            {
                move_x = 0;
                move_y = 0;
            }

            if (entity_mech.can_fire() == true && entity_mech.heat <= 50)
            {
                if (camera_range < 60 && wall_blocking(camera_pos, maze) == false)
                {
                    int fire_decision = rand() % 100;

                    if (fire_decision > 25)
                    {
                        targeted_component = rand() % 7;
                        int weapon_decision = rand() % 100;
                        entity_mech.weapon = weapon_decision >= 75 ? 5 : 1;
                        firing = true;
                    }
                    else
                    {
                        firing = false;
                    }
                }
            }

            think_timer = 0;
        }

        avoid_walls(maze);
        entity_mech.update();
        position.x += move_x;
        position.y += move_y;
    }
}
