#include <player_controller.h>
#include <SFML/Graphics.hpp>
#include <settings.h>
#include <iostream>
#include <cstring>
#include <math.h>

// Constructor
player_controller::player_controller()
{
    credits = 0;
    credits_earned = 0;
    cannon_flash_timer = 0;
    muzzle_flash_timer = 0;
    target_id = 0;
    enemy_id = 0;
    mission = 1;
    guns_timer = 0;
    cannon_timer = 0;
    stomp_timer = 0;
    step_timer = 0;
    torso_angle = 0;
    look_offset = -6;
    player_pos.x = 140;
    player_pos.y = 140;
    targeted_component = 0;
    mouse_move_timer = 0;
    components = {"reactor", "cooler", "left arm", "right arm", "left leg", "right leg", "cockpit"};
}

// Gets current directory, initializes resources and key bindings
void player_controller::init(std::string cwd, assets &resources)
{
    this->resources = resources;
    kb.load(cwd);
}

// Collision checking
void player_controller::collision_check(entity other, float view_range)
{
    if (other.type == "wall")
    {
        if (get_distance(other.position, player_pos) < view_range * 0.4)
        {
            resources.crash_sound.setVolume(100 * audio_volume);
            resources.crash_sound.play();
            player_mech.speed = 0;

            if (other.position.x > player_pos.x)
            {
                player_pos.x -= 20;
            }

            if (other.position.x < player_pos.x)
            {
                player_pos.x += 20;
            }

            if (other.position.y < player_pos.y)
            {
                player_pos.y += 20;
            }

            if (other.position.y > player_pos.y)
            {
                player_pos.y -= 20;
            }
        }
    }
}

// Target locking
void player_controller::lock_target(std::vector<entity> &entities, int entity_count, float window_width)
{
    for (int i = 0; i < entity_count; i++)
    {
        if (entities[i].visible == true)
        {
            float scale = 3 - (entities[i].distance * 0.05) - look_offset * 0.005;
            float sprite_width = entities[i].sprite.getTexture()->getSize().x * scale;
            float center = entities[i].draw_x + (sprite_width / 2);

            if (entities[i].visible == true &&
            entities[i].dead == false &&
            center > window_width * 0.45 &&
            center < window_width * 0.55)
            {
                target_id = entities[i].id;
                break;
            }
        }
    }
}

// Firing guns
void player_controller::fire_guns(std::vector<entity> &entities, int entity_count, float window_width)
{
    if(player_mech.can_fire() == true && guns_firing == false && cannon_firing == false)
    {
        guns_firing = true;
        muzzle_flash = true;
        player_mech.heat = player_mech.heat >= 90 ? 100 : player_mech.heat + 10 + player_mech.guns_modifier;

        for (int i = 0; i < entity_count; i++)
        {
            if (entities[i].visible == true && hit_target == false)
            {
                float scale = 3 - (entities[i].distance * 0.05) - look_offset * 0.005;
                float sprite_width = entities[i].sprite.getTexture()->getSize().x * scale;
                float center = entities[i].draw_x + (sprite_width / 2);

                if (entities[i].visible == true &&
                entities[i].dead == false &&
                center > window_width * 0.45 &&
                center < window_width * 0.55)
                {
                    if (target_id != entities[i].id)
                    {
                        target_id = entities[i].id;
                    }

                    hit_target = true;
                    break;
                }
            }
        }

        resources.gun_sound.setVolume(50 * audio_volume);
        resources.gun_sound.play();
    }
}

// Firing cannon
void player_controller::fire_cannon(std::vector<entity> &entities, int entity_count, float window_width)
{
    if(player_mech.can_fire() == true && cannon_firing == false && guns_firing == false)
    {
        cannon_firing = true;
        cannon_flash = true;
        player_mech.heat = player_mech.heat >= 50 ? 100 : player_mech.heat + 50 + player_mech.cannons_modifier;

        for (int i = 0; i < entity_count; i++)
        {
            if (entities[i].visible == true && hit_target == false)
            {
                float scale = 3 - (entities[i].distance * 0.05) - look_offset * 0.005;
                float sprite_width = entities[i].sprite.getTexture()->getSize().x * scale;
                float center = entities[i].draw_x + (sprite_width / 2);

                if (entities[i].visible == true &&
                entities[i].dead == false &&
                center > window_width * 0.45 &&
                center < window_width * 0.55)
                {
                    if (target_id != entities[i].id)
                    {
                        target_id = entities[i].id;
                    }

                    hit_target = true;
                    break;
                }
            }
        }

        resources.cannon_sound.setVolume(50 * audio_volume);
        resources.cannon_sound.play();
    }
}

// Resets all volatile variables
void player_controller::reset()
{
    throttle_up = false;
    throttle_down = false;
    move_forward = false;
    move_back = false;
    turn_left = false;
    turn_right = false;
    look_left = false;
    look_right = false;
    look_up = false;
    look_down = false;
    player_firing = false;
    target_id = 0;
    enemy_id = 0;
    guns_timer = 0;
    stomp_timer = 0;
    step_timer = 0;
    torso_angle = 0;
    look_offset = -6;
    player_mech.speed = 0;
    player_pos.x = 140;
    player_pos.y = 140;
    targeted_component = 0;
    credits_earned = 0;
}

// Called by main window event handler to handle events related to the player controller
void player_controller::handle_events(sf::RenderWindow &window, sf::Event event)
{
    if(event.type == sf::Event::KeyPressed)
    {
        if (player_mech.destroyed() == false)
        {
            if(event.key.code == kb.bindings["throttle_up"])
            {
                throttle_up = true;
            }

            if(event.key.code == kb.bindings["throttle_down"])
            {
                throttle_down = true;
            }

            if(event.key.code == kb.bindings["turn_left"])
            {
                turn_left = true;
            }

            if(event.key.code == kb.bindings["turn_right"])
            {
                turn_right = true;
            }

            if(event.key.code == kb.bindings["look_left"])
            {
                look_left = true;
            }

            if(event.key.code == kb.bindings["look_right"])
            {
                look_right = true;
            }

            if (event.key.code == kb.bindings["look_down"])
            {
                look_down = true;
            }

            if (event.key.code == kb.bindings["look_up"])
            {
                look_up = true;
            }

            if(event.key.code == kb.bindings["select_component"])
            {
                if (targeted_component < 6)
                {
                    targeted_component++;
                }
                else
                {
                    targeted_component = 0;
                }
            }

            if (event.key.code == kb.bindings["fire_guns"])
            {
                player_mech.weapon = 1;
                player_firing = true;
            }

            if (event.key.code == kb.bindings["fire_cannon"])
            {
                player_mech.weapon = 5;
                player_firing = true;
            }
        }
    }

    if(event.type == sf::Event::KeyReleased)
    {
        if(event.key.code == kb.bindings["throttle_up"])
        {
            throttle_up = false;
        }

        if(event.key.code == kb.bindings["throttle_down"])
        {
            throttle_down = false;
        }

        if(event.key.code == kb.bindings["turn_left"])
        {
            turn_left = false;
        }

        if(event.key.code == kb.bindings["turn_right"])
        {
            turn_right = false;
        }

        if(event.key.code == kb.bindings["look_left"])
        {
            look_left = false;
        }

        if(event.key.code == kb.bindings["look_right"])
        {
            look_right = false;
        }

        if(event.key.code == kb.bindings["look_down"])
        {
            look_down = false;
        }

        if(event.key.code == kb.bindings["look_up"])
        {
            look_up = false;
        }

        if (event.key.code == kb.bindings["fire_guns"])
        {
            player_firing = false;
        }

        if (event.key.code == kb.bindings["fire_cannon"])
        {
            player_firing = false;
        }
    }

    if(event.type == sf::Event::MouseMoved)
    {
        mouse_moved = true;

        sf::Vector2i mouse_pos = sf::Mouse().getPosition(window);

        if (mouse_pos.x >= window.getView().getSize().x * 0.51)
        {
            look_right = true;
            look_left = false;
            sf::Vector2i center;
            center.x = sf::Mouse().getPosition(window).x - 1;
            center.y = sf::Mouse().getPosition(window).y;
            sf::Mouse().setPosition(center, window);
        }

        if (mouse_pos.x <= window.getView().getSize().x * 0.49)
        {
            look_left = true;
            look_right = false;
            sf::Vector2i center;
            center.x = sf::Mouse().getPosition(window).x + 1;
            center.y = sf::Mouse().getPosition(window).y;
            sf::Mouse().setPosition(center, window);
        }

        if (mouse_pos.y > window.getView().getSize().y * 0.55)
        {
            if (invert_mouse == true)
            {
                look_up = true;
                look_down = false;
            }
            else
            {
                look_down = true;
                look_up = false;
            }

            sf::Vector2i center;
            center.x = sf::Mouse().getPosition(window).x;
            center.y = window.getView().getSize().y * 0.55;
            sf::Mouse().setPosition(center, window);
        }

        if (mouse_pos.y < window.getView().getSize().y * 0.45)
        {
            if (invert_mouse == true)
            {
                look_down = true;
                look_up = false;
            }
            else
            {
                look_up = true;
                look_down = false;
            }

            sf::Vector2i center;
            center.x = sf::Mouse().getPosition(window).x;
            center.y = window.getView().getSize().y * 0.45;
            sf::Mouse().setPosition(center, window);
        }
    }

    if (event.type == sf::Event::MouseButtonPressed)
    {
        if(event.mouseButton.button == sf::Mouse::Left)
        {
            player_mech.weapon = 1;
            player_firing = true;
        }

        if(event.mouseButton.button == sf::Mouse::Right)
        {
            player_mech.weapon = 5;
            player_firing = true;
        }
    }

    if (event.type == sf::Event::MouseButtonReleased)
    {
        if(event.mouseButton.button == sf::Mouse::Left)
        {
            player_firing = false;
        }

        if(event.mouseButton.button == sf::Mouse::Right)
        {
            player_firing = false;
        }
    }
}

// Update function called every frame
void player_controller::update(sf::RenderWindow &window, float frame_time)
{
    if (mouse_moved == true)
    {
        mouse_move_timer += frame_time;
        if (mouse_move_timer >= frame_time * 3)
        {
            mouse_moved = false;
            mouse_move_timer = 0;
            look_right = false;
            look_left = false;
            look_up = false;
            look_down = false;
        }
    }
}

// Update function called ten times per second
void player_controller::fixed_update(sf::Transformable player)
{
    player_mech.update();

    // Player movement vectors
    look_pos.x = player.getPosition().x + 30 * cos (player.getRotation() * (3.14 / 180));
    look_pos.y = player.getPosition().y + 30 * sin (player.getRotation() * (3.14 / 180));

    back_pos.x = player.getPosition().x + 30 * cos ((player.getRotation() - 180) * (3.14 / 180));
    back_pos.y = player.getPosition().y + 30 * sin ((player.getRotation() - 180) * (3.14 / 180));

    left_pos.x = player.getPosition().x + 30 * cos ((player.getRotation() - 90) * (3.14 / 180));
    left_pos.y = player.getPosition().y + 30 * sin ((player.getRotation() - 90) * (3.14 / 180));

    right_pos.x = player.getPosition().x + 30 * cos ((player.getRotation() + 90) * (3.14 / 180));
    right_pos.y = player.getPosition().y + 30 * sin ((player.getRotation() + 90) * (3.14 / 180));

    // Movement
    if (player_mech.speed > 0)
    {
        move_forward = true;
    }
    else
    {
        move_forward = false;
    }

    if (player_mech.speed < 0)
    {
        move_back = true;
    }
    else
    {
        move_back = false;
    }

    if (move_forward)
    {
        if (player_pos.x < look_pos.x)
        {
            player_pos.x += player_mech.speed;
        }
        if (player_pos.y < look_pos.y)
        {
            player_pos.y += player_mech.speed;
        }
        if (player_pos.x > look_pos.x)
        {
            player_pos.x -= player_mech.speed;
        }
        if (player_pos.y > look_pos.y)
        {
            player_pos.y -= player_mech.speed;
        }
    }

    if (move_back)
    {
        if (player_pos.x < back_pos.x)
        {
            player_pos.x -= player_mech.speed;
        }
        if (player_pos.y < back_pos.y)
        {
            player_pos.y -= player_mech.speed;
        }
        if (player_pos.x > back_pos.x)
        {
            player_pos.x += player_mech.speed;
        }
        if (player_pos.y > back_pos.y)
        {
            player_pos.y += player_mech.speed;
        }
    }

    look_offset = look_offset > 15 ? 15 : look_offset < -27 ? -27 : look_offset;

    // Throttle
    if (throttle_up == true && player_mech.can_move() == true)
    {
        if (player_mech.speed < 0.125)
        {
            player_mech.speed += 0.001;
        }
    }

    if (throttle_down == true && player_mech.can_move() == true)
    {
        if (player_mech.speed > -0.0625)
        {
            player_mech.speed -= 0.001;
        }
    }

    if (player_mech.can_move() == false)
    {
        player_mech.speed = 0;
    }

    // Mech stomp sounds
    if (player_mech.speed != 0)
    {
        if (player_mech.speed > 0)
        {
            step_timer += player_mech.speed;
        }
        else
        {
            step_timer += -player_mech.speed;
        }

        if (step_timer >= 0.25)
        {
            stomp_timer += 0.1;

            if (stomp_timer >= 0 && stomp_timer < 0.2)
            {
                resources.hydraulic_sound.setVolume(15 * audio_volume);
                resources.hydraulic_sound.play();
                if (look_offset < 10)
                {
                    look_offset -= 0.5;
                }
            }
            else if (stomp_timer >= 0.2 && stomp_timer < 0.5)
            {
                if (look_offset > -10)
                {
                    look_offset += 0.5;
                }
            }
            else if (stomp_timer >= 0.5 && stomp_timer < 0.7)
            {
                if (look_offset < 10)
                {
                    look_offset -= 0.5;
                }
            }

            if (stomp_timer >= 0.7)
            {
                resources.stomp_sound.setVolume(50 * audio_volume);
                resources.stomp_sound.play();
                step_timer = 0;
                stomp_timer = 0;
            }
        }
    }

    // Weapons
    if (muzzle_flash == true)
    {
        muzzle_flash_timer++;
        if (muzzle_flash_timer >= 4)
        {
            muzzle_flash_timer = 0;
            muzzle_flash = false;
        }
    }

    if (cannon_flash == true)
    {
        cannon_flash_timer++;
        if (cannon_flash_timer >= 4)
        {
            cannon_flash_timer = 0;
            cannon_flash = false;
        }
    }

    if (guns_firing == true)
    {
        guns_timer++;
        if (guns_timer >= 6)
        {
            guns_timer = 0;
            guns_firing = false;
        }
    }

    if (cannon_firing == true)
    {
        cannon_timer++;
        if (cannon_timer >= 24)
        {
            cannon_timer = 0;
            cannon_firing = false;
        }
    }
}
