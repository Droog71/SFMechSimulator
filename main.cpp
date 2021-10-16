#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif

#include <hud.h>
#include <math.h>
#include <chrono>
#include <sstream>
#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include <entity.h>
#include <string.h>
#include <cockpit.h>
#include <tutorial.h>
#include <settings.h>
#include <main_menu.h>
#include <calc_helper.h>
#include <file_handler.h>
#include <SFML/Audio.hpp>
#include <settings_menu.h>
#include <SFML/Graphics.hpp>
#include <world_generator.h>
#include <player_controller.h>
#include <intermission_menu.h>

// Class objects
assets resources;
player_controller pc;
world_generator world_gen;
main_menu m_menu;
settings_menu s_menu;
intermission_menu i_menu;
hud player_hud;

// Player
sf::Transformable player;
sf::Transformable camera;

// Graphics
int view_range = 60;
int camera_width = 60;
int ray_count = view_range * camera_width;
int wall_height = 40;
float fov_mod = 0;
float sky_x;
float sky_y;
std::vector<sf::Vector2f> camera_plane(camera_width);
std::vector<sf::Vector2f> rays(ray_count);
std::vector<sf::Vector2f> origins(ray_count);

// Engine
int draw_count = 0;
int entity_count = 2000;
bool flipped_vertical;
bool flipped_horizontal;
bool show_fps;
float fps;
float frame_time;
float frame_timer;
std::string cwd;
std::vector<entity> entities(entity_count);
std::vector<entity> mobs(entity_count);


// Game
bool show_map = true;
bool show_keys = false;
bool bullet_hit = false;
bool main_menu = true;
bool intermission_menu = false;
bool game_started = false;
bool show_victory_notice = false;
float victory_timer;
float game_over_timer;
float map_scale = 0.25;
float bullet_delay;
float damage_timer;
bool taking_damage;
bool took_damage;

// Framerate
std::chrono::high_resolution_clock::time_point fps_start;
std::chrono::high_resolution_clock::time_point fps_finish;

void start_game()
{
    int rand_map = rand() % 100;
    world_gen.maze = rand_map > 50 ? true : false;
    int rand_theme = rand() % 100;
    world_gen.theme = rand_theme > 50 ? 1 : 2;
    world_gen.mission = pc.mission;
    world_gen.generate_world(resources, entities, entity_count);
    player.rotate(90);
    camera.rotate(90);
    game_started = true;
    resources.power_up_sound.setVolume(50 * audio_volume);
    resources.power_up_sound.play();
}

void complete_mission()
{
    player.setRotation(0);
    camera.setRotation(0);
    sky_x = 0;
    sky_y = 0;
    s_menu.visible = false;
    pc.credits += (pc.credits_earned + 20000);
    pc.reset();
    pc.mission++;
    bullet_delay = 0;
    game_started = false;
    i_menu.market.generate_items();
    i_menu.start_game = false;
    intermission_menu = true;
}

void abort_mission()
{
    resources.mission_music.stop();
    player.setRotation(0);
    camera.setRotation(0);
    sky_x = 0;
    sky_y = 0;
    pc.reset();
    bullet_delay = 0;
    game_started = false;
    s_menu.visible = false;
    intermission_menu = true;
    i_menu.start_game = false;
    s_menu.abort_mission = false;
}

int main(int argc, char * argv[])
{
    srand(time(NULL));

    char cwd_char[PATH_MAX];
    if (getcwd(cwd_char, sizeof(cwd_char)) != NULL)
    {
       cwd = cwd_char;
    }

    tutorial tut(cwd);
    load_settings(cwd);
    resources.init(cwd);

    pc.init(cwd, resources);
    player_hud.init(resources);
    m_menu.init(cwd, resources);
    i_menu.init(cwd, resources);
    s_menu.init(cwd, resources, true);
    i_menu.market.generate_items();

    sf::RenderWindow window;

    bool windowed = false;

    if (argc > 3)
    {
        if (strcmp(argv[1], "-window") == 0)
        {
            windowed = true;
            unsigned int x = std::stoi(argv[2]) < 1280 ? 1280 : std::stoi(argv[2]);
            unsigned int y = std::stoi(argv[3]) < 720 ? 720 : std::stoi(argv[3]);
            window.create(sf::VideoMode(x, y), "SF Mech Simulator", sf::Style::Close);
        }
    }

    if (windowed == false)
    {
        window.create(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), "SF Mech Simulator", sf::Style::Fullscreen);
    }

    window.setFramerateLimit(60);

    // Start the game loop
    while (window.isOpen())
    {
        fps_start = std::chrono::high_resolution_clock::now();

        if (main_menu == true)
        {
            window.setMouseCursorVisible(true);
            main_menu = m_menu.draw_menu(window, pc, frame_time);
        }
        else if (m_menu.game_loaded == true)
        {
            m_menu.game_loaded = false;
            i_menu.market.generate_items();
            intermission_menu = true;
        }
        else if (intermission_menu == true)
        {
            if (i_menu.return_to_main == false)
            {
                window.setMouseCursorVisible(true);
                intermission_menu = i_menu.draw_menu(window, pc, frame_time);
            }
            else
            {
                i_menu.return_to_main = false;
                m_menu.game_loaded = false;
                m_menu.start_game = false;
                intermission_menu = false;
                game_started = false;
                main_menu = true;
            }
        }
        else
        {
            if (game_started == false)
            {
                start_game();
            }

            if (intermission_menu == false && pc.player_mech.power_down == false && show_victory_notice == false)
            {
                resources.mission_music.setVolume(50 * audio_volume);

                if (music == true && resources.mission_music.getStatus() != sf::Sound::Playing)
                {
                    resources.mission_music.play();
                }
            }

            window.setMouseCursorVisible(s_menu.visible);

            // Process events
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (s_menu.visible == true)
                {
                    sf::Vector2i mouse_pos = sf::Mouse().getPosition(window);
                    s_menu.handle_events(event, mouse_pos);
                }
                else
                {
                    pc.handle_events(window, event);
                }

                if (event.type == sf::Event::Closed)
                {
                    window.close();
                }

                if(event.type == sf::Event::KeyPressed)
                {
                    if (pc.player_mech.destroyed() == false)
                    {
                        if(event.key.code == pc.kb.bindings["lock_target"])
                        {
                            int j = 0;
                            for (int i = 0; i < entity_count; i++)
                            {
                                if (entities[i].type == "mob")
                                {
                                    mobs[j] = entities[i];
                                    j++;
                                }
                            }
                            mobs.resize(j);
                            pc.lock_target(mobs, j, window.getView().getSize().x);
                        }

                        if(event.key.code == pc.kb.bindings["map"])
                        {
                            if (show_map == true)
                            {
                                if (map_scale == 0.25)
                                {
                                    map_scale = 0.5;
                                }
                                else if (map_scale == 0.5)
                                {
                                    map_scale = 0.75;
                                }
                                else if (map_scale == 0.75)
                                {
                                    map_scale = 0.25;
                                    show_map = !show_map;
                                }
                            }
                            else
                            {
                                show_map = !show_map;
                            }
                        }

                        if (event.key.code == pc.kb.bindings["show_keys"])
                        {
                            show_keys = !show_keys;
                        }

                        if (event.key.code == pc.kb.bindings["show_tutorial"])
                        {
                            tut.visible = !tut.visible;
                        }

                        if (event.key.code == pc.kb.bindings["show_fps"])
                        {
                            show_fps = !show_fps;
                        }

                        if (event.key.code == sf::Keyboard::Escape && show_victory_notice == false)
                        {
                            s_menu.visible = !s_menu.visible;
                        }

                        if (tut.visible && event.key.code == sf::Keyboard::Return)
                        {
                            tut.step = tut.step < 10 ? tut.step + 1 : 0;
                        }
                    }
                }
            }

            if (s_menu.visible == false)
            {
                // Walls need to be placed in descending order of distance to the camera
                if (camera.getRotation() > 0 && camera.getRotation() < 180 && flipped_vertical == false)
                {
                    world_gen.flip_walls_vertical(entities, entity_count, true);
                    flipped_vertical = true;
                }

                if (camera.getRotation() >= 180 && flipped_vertical == true)
                {
                    world_gen.flip_walls_vertical(entities, entity_count, false);
                    flipped_vertical = false;
                }

                if ((camera.getRotation() >= 270 || camera.getRotation() <= 90) && flipped_horizontal == false)
                {
                    world_gen.flip_walls_horizontal(entities, entity_count, true);
                    flipped_horizontal = true;
                }

                if (camera.getRotation() > 90 && camera.getRotation() < 270 && flipped_horizontal == true)
                {
                    world_gen.flip_walls_horizontal(entities, entity_count, false);
                    flipped_horizontal = false;
                }

                if(pc.turn_left == true && pc.player_mech.can_move() == true)
                {
                    player.rotate(-10 * frame_time);
                    camera.rotate(-10 * frame_time);
                    sky_x -= 100 * frame_time;
                }

                if(pc.turn_right == true && pc.player_mech.can_move() == true)
                {
                    player.rotate(10 * frame_time);
                    camera.rotate(10 * frame_time);
                    sky_x += 100 * frame_time;
                }

                if (pc.look_left == true && pc.torso_angle > -89 && pc.player_mech.cockpit_integrity > 0)
                {
                    camera.rotate(-10 * frame_time);
                    pc.torso_angle -= 10 * frame_time;
                    sky_x -= 100 * frame_time;
                }

                if (pc.look_right == true && pc.torso_angle < 90 && pc.player_mech.cockpit_integrity > 0)
                {
                    camera.rotate(10 * frame_time);
                    pc.torso_angle += 10 * frame_time;
                    sky_x += 100 * frame_time;
                }

                // Vertical cockpit movement
                if (pc.look_up == true)
                {
                    if (pc.look_offset < 15 && pc.player_mech.cockpit_integrity > 0)
                    {
                        pc.look_offset += 5 * frame_time;
                        sky_y -= 50 * frame_time;
                    }
                }

                if (pc.look_down == true && pc.player_mech.cockpit_integrity > 0)
                {
                    if (pc.look_offset > -27)
                    {
                        pc.look_offset -= 5 * frame_time;
                        sky_y += 50 * frame_time;
                    }
                }

                pc.update(window, frame_time);

                // Frame rate independent updates
                frame_timer += frame_time;
                if (frame_timer >= 0.1)
                {
                    frame_timer = 0;

                    pc.fixed_update(player);

                    int mob_count = 0;
                    for (int i = 0; i < entity_count; i++)
                    {
                        if (entities[i].type == "mob" && entities[i].sub_type == "mech" && entities[i].dead == false)
                        {
                            mob_count++;
                            entities[i].update(camera_plane[camera_width / 2], world_gen.maze);
                            if (entities[i].firing == true && pc.player_mech.destroyed() == false && pc.enemy_id == 0)
                            {
                                entities[i].fire_weapons(resources);
                                taking_damage = true;
                                pc.enemy_id = i;
                            }
                        }
                    }

                    if (mob_count == 0)
                    {
                        show_victory_notice = true;
                    }

                    // Firing weapons
                    if (pc.player_firing == true)
                    {
                        int j = 0;
                        for (int i = 0; i < entity_count; i++)
                        {
                            if (entities[i].type == "mob")
                            {
                                mobs[j] = entities[i];
                                j++;
                            }
                        }
                        mobs.resize(j);

                        if (pc.player_mech.weapon == 1 && pc.guns_firing == false)
                        {
                            pc.fire_guns(mobs, j, window.getView().getSize().x);
                        }

                        if (pc.player_mech.weapon == 5 && pc.cannon_firing == false)
                        {
                            pc.fire_cannon(mobs, j, window.getView().getSize().x);
                        }
                    }

                    // Taking damage
                    if (taking_damage == true)
                    {
                        damage_timer++;
                        if (damage_timer >= 2 && damage_timer < 4)
                        {
                            entities[pc.enemy_id].sprite.setTexture(resources.mech_texture);
                        }
                        else if (damage_timer >= 4 && damage_timer < 6)
                        {
                            if (took_damage == false && pc.player_mech.destroyed() == false)
                            {
                                resources.impact_sound.setVolume(100 * audio_volume);
                                resources.impact_sound.play();

                                entity enemy = entities[pc.enemy_id];
                                mech enemy_mech = entities[pc.enemy_id].entity_mech;
                                std::string component = enemy.components[enemy.targeted_component];
                                int modifier = enemy_mech.weapon == 1 ? enemy_mech.guns_modifier : enemy_mech.cannons_modifier;
                                int damage = enemy_mech.weapon + modifier;

                                if (enemy_mech.left_arm_destroyed() || enemy_mech.right_arm_destroyed())
                                {
                                    damage = damage / 2;
                                }

                                pc.player_mech.take_damage(component, enemy.distance, damage);
                                took_damage = true;
                            }
                        }
                        else if (damage_timer >= 6)
                        {
                            taking_damage = false;
                            took_damage = false;
                            pc.enemy_id = 0;
                            damage_timer = 0;
                        }
                    }

                    // Dealing damage
                    if (pc.hit_target == true)
                    {
                        bullet_delay++;
                        if (bullet_delay >= 4 && bullet_delay < 6 && bullet_hit == false)
                        {
                            if (entities[pc.target_id].entity_mech.destroyed() == true)
                            {
                                resources.explosion_sound.setVolume(50 * audio_volume);
                                resources.explosion_sound.play();
                                entities[pc.target_id].sprite.setTexture(resources.explosion_texture);
                            }
                            else
                            {
                                resources.impact_sound.setVolume(50 * audio_volume);
                                resources.impact_sound.play();
                                entities[pc.target_id].sprite.setTexture(resources.mech_textures[pc.targeted_component]);
                            }
                            bullet_hit = true;
                        }
                        else if (bullet_delay >= 6)
                        {
                            if (entities[pc.target_id].entity_mech.destroyed() == true)
                            {
                                entities[pc.target_id].visible = false;
                                entities[pc.target_id].dead = true;
                                pc.credits_earned += 10000;
                            }
                            else
                            {
                                entities[pc.target_id].sprite.setTexture(resources.mech_texture);
                            }

                            mech player_mech = pc.player_mech;
                            entity target = entities[pc.target_id];
                            std::string component = pc.components[pc.targeted_component];
                            int modifier = player_mech.weapon == 1 ? player_mech.guns_modifier : player_mech.cannons_modifier;
                            int damage = player_mech.weapon + modifier;

                            if (player_mech.left_arm_destroyed() || player_mech.right_arm_destroyed())
                            {
                                damage = damage / 2;
                            }

                            entities[pc.target_id].entity_mech.take_damage(component, target.distance, damage);
                            pc.hit_target = false;
                            bullet_hit = false;
                            bullet_delay = 0;
                        }
                    }

                    if (pc.player_mech.destroyed() == true)
                    {
                        show_keys = false;
                        tut.visible = false;
                        s_menu.visible = false;
                        resources.cockpit_sprite.setTexture(resources.cockpit_destroyed_texture);
                        pc.player_mech.speed = 0;

                        if (pc.player_mech.power_down == false)
                        {
                            resources.mission_music.stop();
                            resources.power_down_sound.setVolume(50 * audio_volume);
                            resources.power_down_sound.play();
                            pc.player_mech.power_down = true;
                        }

                        game_over_timer++;
                        if (game_over_timer >= 100)
                        {
                            pc.player_mech.power_down = false;
                            game_over_timer = 0;
                            player.setRotation(0);
                            camera.setRotation(0);
                            sky_x = 0;
                            sky_y = 0;
                            pc.reset();
                            bullet_delay = 0;
                            game_started = false;
                            intermission_menu = true;
                            i_menu.start_game = false;
                        }
                    }
                    else
                    {
                        resources.cockpit_sprite.setTexture(resources.cockpit_texture);
                    }
                }
            }

            // Camera plane creation
            sf::Vector2f camera_pos;
            camera_pos.x = player.getPosition().x + 10 * cos (camera.getRotation() * (3.14 / 180));
            camera_pos.y = player.getPosition().y + 10 * sin (camera.getRotation() * (3.14 / 180));

            float pos = camera_width / 2;
            for (int i = 0; i < camera_width / 2; i++)
            {
                camera_plane[i].x = camera_pos.x + pos * cos ((camera.getRotation() - 90) * (3.14 / 180));
                camera_plane[i].y = camera_pos.y + pos * sin ((camera.getRotation() - 90) * (3.14 / 180));
                pos --;
            }

            pos = 0;
            for (int i = camera_width / 2; i < camera_width; i++)
            {
                camera_plane[i].x = camera_pos.x + pos * cos ((camera.getRotation() + 90) * (3.14 / 180));
                camera_plane[i].y = camera_pos.y + pos * sin ((camera.getRotation() + 90) * (3.14 / 180));
                pos ++;
            }

            // Raycasting
            int k = 0;
            for (int i = 0; i < view_range; i++)
            {
                for (int j = 0; j < camera_width; j++)
                {
                    float angle = j;
                    if (j < camera_width / 2)
                    {
                        angle = (((camera_width / 2) - j) * -1) * fov_mod;
                    }
                    else
                    {
                        angle = (j - (camera_width / 2)) * fov_mod;
                    }
                    rays[k].x = camera_plane[j].x + i * cos ((camera.getRotation() + angle) * (3.14 / 180));
                    rays[k].y = camera_plane[j].y + i * sin ((camera.getRotation() + angle) * (3.14 / 180));
                    origins[k] = camera_plane[j];
                    k++;
                }
            }

            // Determine entitites visible to the camera
            for (int i = 0; i < entity_count; i++)
            {
                float distance = get_distance(camera_plane[camera_width / 2], entities[i].position);
                if (distance < view_range)
                {
                    int index;
                    float wall_ray = 0;
                    float near_ray = 0;
                    float dist = 100;
                    bool visible = false;
                    bool culling = false;

                    for (int j = 0; j < ray_count; j++)
                    {
                        dist = (get_distance(rays[j], entities[i].position));
                        if (dist < 1 && entities[i].dead == false)
                        {
                            pc.collision_check(entities[i], view_range);
                            entities[i].distance = get_distance(entities[i].position, origins[j]);
                            index = j;
                            visible = true;

                            if (entities[i].type == "wall")
                            {
                                wall_ray = (float)j / (float)camera_width;
                                wall_ray = wall_ray - floor(wall_ray);
                                wall_ray = wall_ray * camera_width;
                                culling = true;
                            }
                        }

                        if (culling == true)
                        {
                            near_ray = (float)j / (float)camera_width;
                            near_ray = near_ray - floor(near_ray);
                            near_ray = near_ray * camera_width;
                            if (near_ray > wall_ray - 5 && near_ray < wall_ray + 5)
                            {
                                rays[j] = origins[j];
                            }
                        }
                    }

                    if (visible == true)
                    {
                        // Center the entity between the closest raycasts, for smoother movement
                        float dist_to_left = (get_distance(rays[index - 1], entities[i].position));
                        float dist_to_right = (get_distance(rays[index + 1], entities[i].position));
                        int offset = dist_to_left < dist_to_right ? index - 1 : index + 1;
                        float offset_percent = ((float)offset) / (float)camera_width;
                        offset_percent = offset_percent - floor(offset_percent);
                        float screen_percent = (float)index / (float)camera_width;
                        screen_percent = screen_percent - floor(screen_percent);
                        float final_pos = (offset_percent + screen_percent) / 2;
                        float distance_moved = 0;

                        if (entities[i].old_pos > final_pos)
                        {
                            distance_moved = entities[i].old_pos - final_pos;
                        }
                        else
                        {
                            distance_moved = final_pos - entities[i].old_pos;
                        }

                        if (distance_moved > 0.02)
                        {
                            final_pos = (final_pos + entities[i].old_pos) / 2;
                        }

                        float entity_draw_x = window.getView().getSize().x * final_pos;
                        entities[i].draw_x = entity_draw_x;
                        entities[i].old_pos = final_pos;
                    }

                    entities[i].visible = visible;
                }
                else
                {
                    entities[i].visible = false;
                    entities[i].old_pos = 0;
                }
            }

            // Position the player in the world
            player.setPosition(pc.player_pos.x, pc.player_pos.y);

            // Clear screen
            window.clear();

            // Draw the sky
            resources.sky_sprite.setTextureRect(sf::IntRect(sky_x, sky_y, window.getView().getSize().x, window.getView().getSize().y));
            if (world_gen.theme == 1)
            {
                resources.sky_sprite.setTexture(resources.sky_texture);
            }
            else
            {
                resources.sky_sprite.setTexture(resources.sky_2_texture);
            }
            window.draw(resources.sky_sprite);

            // Draw the ground
            resources.ground_sprite.setPosition(0, ((window.getView().getSize().y / 2) + pc.look_offset * 10));
            float ground_scale_x = window.getView().getSize().x / resources.ground_sprite.getLocalBounds().width;
            float ground_scale_y = resources.ground_sprite.getLocalBounds().height;
            resources.ground_sprite.setScale(ground_scale_x, ground_scale_y);
            if (world_gen.theme == 1)
            {
                resources.ground_sprite.setTexture(resources.ground_texture);
            }
            else
            {
                resources.ground_sprite.setTexture(resources.ground_2_texture);
            }
            window.draw(resources.ground_sprite);

            for (int i = 0; i < entity_count; i++)
            {
                if (entities[i].visible == true)
                {
                    draw_count++;
                }
            }

            if (draw_count > 0)
            {
                std::vector<entity> entities_to_draw(draw_count);
                draw_count = 0;

                // Find all visible objects
                for (int i = 0; i < entity_count; i++)
                {
                    if (entities[i].visible == true)
                    {
                        entities_to_draw[draw_count] = entities[i];
                        draw_count++;
                    }
                }

                // The upper and lower vertices of wall segments
                std::vector<sf::Vector2f> verts_low(draw_count);
                std::vector<sf::Vector2f> verts_high(draw_count);

                // Create sprites and wall segments for drawing to the screen
                for (int i = 0; i < draw_count; i++)
                {
                    if (entities_to_draw[i].type == "wall") // Create lines with scaled height for drawing wall quads
                    {
                        float scale = 6 - (entities_to_draw[i].distance * 0.095) - pc.look_offset * 0.005;
                        scale = scale < 0 ? 0 : scale;
                        sf::Vector2f v1;
                        v1.x = entities_to_draw[i].draw_x;
                        v1.y = (window.getView().getSize().y / 2) - (wall_height * scale) + pc.look_offset * 10;
                        sf::Vector2f v2;
                        v2.x = entities_to_draw[i].draw_x;
                        v2.y = (window.getView().getSize().y / 2) + (wall_height * scale) + pc.look_offset * 10;
                        verts_high[i] = v1;
                        verts_low[i] = v2;
                    }
                    else // Prepare sprites for drawing to the screen
                    {
                        float scale = 3 - (entities_to_draw[i].distance * 0.05) - pc.look_offset * 0.005;
                        scale = scale < 0 ? 0 : scale;
                        entities_to_draw[i].sprite.setScale(scale, scale);
                        entities_to_draw[i].sprite.setScale(scale, scale);
                        float window_center = window.getView().getSize().y / 2;
                        float sprite_width = entities_to_draw[i].sprite.getTexture()->getSize().y;
                        float sprite_scale = entities_to_draw[i].sprite.getScale().y;
                        entities_to_draw[i].draw_y = window_center - ((sprite_width * sprite_scale) / 2);
                        entities_to_draw[i].draw_y +=  (120 - (entities_to_draw[i].distance * 2)) + pc.look_offset * 10;
                        entities_to_draw[i].sprite.setPosition(entities_to_draw[i].draw_x, entities_to_draw[i].draw_y);
                    }
                }

                // Sort wall segments from left to right on the window's x axis, for drawing quads
                verts_low = x_sort(verts_low, draw_count);
                verts_high = x_sort(verts_high, draw_count);

                // Create the quads
                std::vector<sf::VertexArray> walls (draw_count);
                for (int wall_index = 0; wall_index < draw_count - 1; wall_index++)
                {
                    if (get_distance(verts_high[wall_index], verts_high[wall_index + 1]) < window.getView().getSize().x * 0.4)
                    {
                        if (verts_low[wall_index].x != 0)
                        {
                            sf::VertexArray quad(sf::Quads, 4);
                            quad[0].position = verts_low[wall_index];
                            quad[1].position = verts_low[wall_index + 1];
                            quad[2].position = verts_high[wall_index + 1];
                            quad[3].position = verts_high[wall_index];
                            quad[0].texCoords = sf::Vector2f(0.f, 512.f);
                            quad[1].texCoords = sf::Vector2f(512.f, 512.f);
                            quad[2].texCoords = sf::Vector2f(512.f, 0.f);
                            quad[3].texCoords = sf::Vector2f(0.f, 0.f);
                            if (world_gen.theme == 1)
                            {
                                window.draw(quad, &resources.wall_texture);
                            }
                            else
                            {
                                window.draw(quad, &resources.wall_2_texture);
                            }
                        }
                    }
                }

                // Sort sprites by their distance from the camera, so farther sprites are drawn first
                entity temp;
                int i, j;

                for(i = 0; i < draw_count; i++)
                {
                    for(j = i + 1; j < draw_count; j++)
                    {
                        if(entities_to_draw[i].distance < entities_to_draw[j].distance)
                        {
                            temp = entities_to_draw[i];
                            entities_to_draw[i] = entities_to_draw[j];
                            entities_to_draw[j] = temp;
                        }
                    }
                }

                // Draw sprites
                for (int i = 0; i < draw_count; i++)
                {
                    if (entities_to_draw[i].type != "wall")
                    {
                        window.draw(entities_to_draw[i].sprite);
                        if (entities_to_draw[i].type == "mob")
                        {
                            if (pc.target_id == entities_to_draw[i].id)
                            {
                                float scale = 3 - (entities_to_draw[i].distance * 0.05) - pc.look_offset * 0.005;
                                scale = scale < 0 ? 0 : scale;
                                float x = entities_to_draw[i].sprite.getPosition().x;
                                float y = entities_to_draw[i].sprite.getPosition().y;
                                float width = entities_to_draw[i].sprite.getTexture()->getSize().x * scale;
                                float height = entities_to_draw[i].sprite.getTexture()->getSize().y * scale;
                                sf::Vector2f top_left = sf::Vector2f(x - 10, y - 10);
                                sf::Vector2f bottom_left = sf::Vector2f(x - 10, y  + height + 10);
                                sf::Vector2f top_right = sf::Vector2f(x + width + 10, y - 10);
                                sf::Vector2f bottom_right = sf::Vector2f(x + width + 10, y  + height + 10);
                                sf::VertexArray target_box(sf::LineStrip, 5);
                                target_box[0].position = bottom_left;
                                target_box[1].position = bottom_right;
                                target_box[2].position = top_right;
                                target_box[3].position = top_left;
                                target_box[4].position = bottom_left;
                                for (int j = 0; j < 5; j++)
                                {
                                    target_box[j].color = sf::Color::Red;
                                }
                                window.draw(target_box);
                                std::string target_distance = std::to_string((int)entities[pc.target_id].distance * 10);
                                std::string info = "Distance: " + target_distance + " meters\nTargeting: " + pc.components[pc.targeted_component];
                                resources.target_info.setString(info);
                                sf::Vector2f info_pos = sf::Vector2f(top_left.x, top_left.y - 40);
                                resources.target_info.setPosition(info_pos);
                                window.draw(resources.target_info);
                            }
                        }
                    }
                }
            }

            // Draw the cockpit
            draw_cockpit(window, resources, pc, took_damage);

            //Draw the HUD
            player_hud.draw_hud(window, frame_time, pc.target_id, pc.player_mech.speed, pc.torso_angle, pc.player_mech, entities[pc.target_id].entity_mech);

            // Draw entities on the map
            for (int i = 0; i < entity_count; i++)
            {
                if (show_map == true && pc.player_mech.destroyed() == false)
                {
                    if (entities[i].type == "mob")
                    {
                        if (pc.target_id == entities[i].id)
                        {
                            entities[i].icon.setTexture(resources.target_icon_texture);
                        }
                        else
                        {
                            entities[i].icon.setTexture(resources.mob_icon_texture);
                        }
                    }
                    if (entities[i].dead == false)
                    {
                        entities[i].icon.setPosition(entities[i].position.x * map_scale, entities[i].position.y * map_scale);
                        window.draw(entities[i].icon);
                    }
                }
            }

            // Draw the player on the map
            if (show_map == true && pc.player_mech.destroyed() == false)
            {
                sf::VertexArray line1(sf::LinesStrip, 2);
                sf::Vector2f map_player_pos = sf::Vector2f(pc.player_pos.x * map_scale, pc.player_pos.y * map_scale);
                sf::Vector2f map_look_pos = sf::Vector2f(pc.look_pos.x * map_scale, pc.look_pos.y * map_scale);
                sf::Vector2f map_cam_pos = sf::Vector2f(rays[camera_width / 2 + camera_width * 5].x * map_scale, rays[camera_width / 2 + camera_width * 5].y * map_scale);
                sf::Vector2f mid = get_midpoint(map_player_pos, map_look_pos);

                resources.player_icon.setPosition(sf::Vector2f((pc.player_pos.x - 16) * map_scale, (pc.player_pos.y - 16) * map_scale));
                resources.player_icon.setScale(map_scale, map_scale);
                window.draw(resources.player_icon);

                line1[0].position = map_player_pos;
                line1[1].position = mid;
                line1[0].color = sf::Color::Green;
                line1[1].color = sf::Color::Green;
                window.draw(line1);

                sf::VertexArray line2(sf::LinesStrip, 2);
                line2[0].position = map_player_pos;
                line2[1].position = map_cam_pos;
                line2[0].color = sf::Color::Red;
                line2[1].color = sf::Color::Red;
                window.draw(line2);
            }

            if (show_keys == true)
            {
                sf::Vector2f bg_pos;
                float x = window.getView().getSize().x - 150;
                bg_pos.x = x - (resources.keys.getGlobalBounds().width / 2);
                bg_pos.y = (window.getView().getSize().y / 2) - 175;
                sf::Sprite bg = sf::Sprite(resources.gui_background_texture);
                bg.setPosition(bg_pos);
                bg.setScale(0.1, 1);
                window.draw(bg);

                std::string bindings = get_file_contents(cwd + "/bindings.list");
                resources.keys.setString(bindings);
                resources.keys.setPosition(x - 50, (window.getView().getSize().y / 2) - 150);
                window.draw(resources.keys);
            }

            if (tut.visible == true)
            {
                tut.draw_tutorial(window, show_keys, pc.player_mech.speed, pc.torso_angle, pc.player_mech.heat);
            }

            if (show_victory_notice == true)
            {
                resources.mission_music.stop();
                if (resources.victory_sound.getStatus() != sf::Sound::Playing)
                {
                    resources.victory_sound.setVolume(100 * audio_volume);
                    resources.victory_sound.play();
                }

                tut.visible = false;
                s_menu.visible = false;
                resources.notice.setFont(resources.orbitron);
                resources.notice.setString("MISSION COMPLETE");
                sf::Vector2f text_pos;
                text_pos.x = (window.getView().getSize().x / 2) - (resources.notice.getGlobalBounds().width / 2);
                text_pos.y = (window.getView().getSize().y / 2) - 150;
                resources.notice.setPosition(text_pos);
                window.draw(resources.notice);
                resources.notice.setFont(resources.exoplanetaria);

                victory_timer += 10 * frame_time;
                if (victory_timer >= 60)
                {
                    victory_timer = 0;
                    show_victory_notice = false;
                    complete_mission();
                }
            }

            if (s_menu.visible == true)
            {
                tut.visible = false;
                sf::Vector2i mouse_pos = sf::Mouse().getPosition(window);
                s_menu.draw_menu(window, mouse_pos, frame_time);

                if (s_menu.abort_mission == true)
                {
                    abort_mission();
                }
            }

            // Draw frame rate at the bottom left corner of the screen
            if (show_fps == true)
            {
                sf::String fps_string = "FPS: " + std::to_string(fps);
                resources.fps_counter.setString(fps_string);
                resources.fps_counter.setPosition(10, window.getView().getSize().y * 0.96);
                window.draw(resources.fps_counter);
            }

            // Display on screen what has been rendered to the window so far
            window.display();
        }

        // Calculate framerate
        fps_finish = std::chrono::high_resolution_clock::now();
        fps = (float)1e9/(float)std::chrono::duration_cast<std::chrono::nanoseconds>(fps_finish-fps_start).count();
        frame_time = 1 / fps;
    }

    return EXIT_SUCCESS;
}
