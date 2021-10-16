#include <assets.h>
#include <SFML/Graphics.hpp>
#include <iostream>

// Loads sounds from file
void assets::load_sound_buffers(std::string cwd)
{
    if (!main_menu_music_buffer.loadFromFile(cwd + "/assets/sounds/main_menu.ogg"))
    {
        std::cout << "Error loading sound file main_menu.ogg";
        std::cout << "\n";
    }

    if (!intermission_music_buffer.loadFromFile(cwd + "/assets/sounds/intermission_menu.ogg"))
    {
        std::cout << "Error loading sound file intermission_menu.ogg";
        std::cout << "\n";
    }

    if (!mission_music_buffer.loadFromFile(cwd + "/assets/sounds/mission.ogg"))
    {
        std::cout << "Error loading sound file mission.ogg";
        std::cout << "\n";
    }

    if (!power_down_sound_buffer.loadFromFile(cwd + "/assets/sounds/power_down.ogg"))
    {
        std::cout << "Error loading sound file power_down.ogg";
        std::cout << "\n";
    }

    if (!victory_sound_buffer.loadFromFile(cwd + "/assets/sounds/victory.ogg"))
    {
        std::cout << "Error loading sound file victory.ogg";
        std::cout << "\n";
    }

    if (!power_up_sound_buffer.loadFromFile(cwd + "/assets/sounds/power_up.ogg"))
    {
        std::cout << "Error loading sound file power_up.ogg";
        std::cout << "\n";
    }

    if (!hydraulic_sound_buffer.loadFromFile(cwd + "/assets/sounds/hydraulic.ogg"))
    {
        std::cout << "Error loading sound file hydraulic.ogg";
        std::cout << "\n";
    }

    if (!gun_sound_buffer.loadFromFile(cwd + "/assets/sounds/guns.ogg"))
    {
        std::cout << "Error loading sound file guns.ogg";
        std::cout << "\n";
    }

    if (!cannon_sound_buffer.loadFromFile(cwd + "/assets/sounds/cannon.ogg"))
    {
        std::cout << "Error loading sound file cannon.ogg";
        std::cout << "\n";
    }

    if (!explo_sound_buffer.loadFromFile(cwd + "/assets/sounds/explosion.ogg"))
    {
        std::cout << "Error loading sound file explosion.ogg";
        std::cout << "\n";
    }

    if (!stomp_sound_buffer.loadFromFile(cwd + "/assets/sounds/stomp.ogg"))
    {
        std::cout << "Error loading sound file stomp.ogg";
        std::cout << "\n";
    }

    if (!crash_sound_buffer.loadFromFile(cwd + "/assets/sounds/crash.ogg"))
    {
        std::cout << "Error loading sound file crash.ogg";
        std::cout << "\n";
    }

    if (!impact_sound_buffer.loadFromFile(cwd + "/assets/sounds/impact.ogg"))
    {
        std::cout << "Error loading sound file impact.ogg";
        std::cout << "\n";
    }

    if (!purchase_sound_buffer.loadFromFile(cwd + "/assets/sounds/purchase.ogg"))
    {
        std::cout << "Error loading sound file purchase.ogg";
        std::cout << "\n";
    }
}

// Loads textures from file
void assets::load_textures(std::string cwd)
{
    if (!mech_texture.loadFromFile(cwd + "/assets/textures/mech/mech.bmp"))
    {
        std::cout << "Error loading image file mech.bmp";
        std::cout << "\n";
    }

    if (!mech_fire_guns_texture.loadFromFile(cwd + "/assets/textures/mech/mech_fire.bmp"))
    {
        std::cout << "Error loading image file mech_fire.bmp";
        std::cout << "\n";
    }

    if (!mech_fire_guns_left_texture.loadFromFile(cwd + "/assets/textures/mech/mech_fire_left.bmp"))
    {
        std::cout << "Error loading image file mech_fire_left.bmp";
        std::cout << "\n";
    }

    if (!mech_fire_guns_right_texture.loadFromFile(cwd + "/assets/textures/mech/mech_fire_right.bmp"))
    {
        std::cout << "Error loading image file mech_fire_right.bmp";
        std::cout << "\n";
    }

    if (!mech_fire_cannons_texture.loadFromFile(cwd + "/assets/textures/mech/mech_cannon_fire.bmp"))
    {
        std::cout << "Error loading image file mech_cannon_fire.bmp";
        std::cout << "\n";
    }

    if (!mech_fire_cannons_left_texture.loadFromFile(cwd + "/assets/textures/mech/mech_cannon_left.bmp"))
    {
        std::cout << "Error loading image file mech_cannon_fire_left.bmp";
        std::cout << "\n";
    }

    if (!mech_fire_cannons_right_texture.loadFromFile(cwd + "/assets/textures/mech/mech_cannon_right.bmp"))
    {
        std::cout << "Error loading image file mech_cannon_fire_right.bmp";
        std::cout << "\n";
    }

    if (!mech_hit_center_texture.loadFromFile(cwd + "/assets/textures/mech/mech_hit_center.bmp"))
    {
        std::cout << "Error loading image file mech_hit_center.bmp";
        std::cout << "\n";
    }

    if (!mech_hit_cockpit_texture.loadFromFile(cwd + "/assets/textures/mech/mech_hit_cockpit.bmp"))
    {
        std::cout << "Error loading image file mech_hit_cockpit.bmp";
        std::cout << "\n";
    }

    if (!mech_hit_left_leg_texture.loadFromFile(cwd + "/assets/textures/mech/mech_hit_left_leg.bmp"))
    {
        std::cout << "Error loading image file mech_hit_left_leg.bmp";
        std::cout << "\n";
    }

    if (!mech_hit_right_leg_texture.loadFromFile(cwd + "/assets/textures/mech/mech_hit_right_leg.bmp"))
    {
        std::cout << "Error loading image file mech_hit_right_leg.bmp";
        std::cout << "\n";
    }

    if (!mech_hit_left_arm_texture.loadFromFile(cwd + "/assets/textures/mech/mech_hit_left_arm.bmp"))
    {
        std::cout << "Error loading image file mech_hit_left_arm.bmp";
        std::cout << "\n";
    }

    if (!mech_hit_right_arm_texture.loadFromFile(cwd + "/assets/textures/mech/mech_hit_right_arm.bmp"))
    {
        std::cout << "Error loading image file mech_hit_right_arm.bmp";
        std::cout << "\n";
    }

    if (!explosion_texture.loadFromFile(cwd + "/assets/textures/mech/explosion.png"))
    {
        std::cout << "Error loading image file explosion.bmp";
        std::cout << "\n";
    }

    if (!crosshair_texture.loadFromFile(cwd + "/assets/textures/crosshair.png"))
    {
        std::cout << "Error loading image file crosshair.bmp";
        std::cout << "\n";
    }

    if (!cockpit_texture.loadFromFile(cwd + "/assets/textures/cockpit/cockpit.bmp"))
    {
        std::cout << "Error loading image file cockpit.bmp";
        std::cout << "\n";
    }

    if (!cockpit_fire_texture.loadFromFile(cwd + "/assets/textures/cockpit/cockpit_fire.bmp"))
    {
        std::cout << "Error loading image file cockpit_fire.bmp";
        std::cout << "\n";
    }

    if (!cockpit_fire_left_texture.loadFromFile(cwd + "/assets/textures/cockpit/cockpit_fire_left.bmp"))
    {
        std::cout << "Error loading image file cockpit_fire_left.bmp";
        std::cout << "\n";
    }

    if (!cockpit_fire_right_texture.loadFromFile(cwd + "/assets/textures/cockpit/cockpit_fire_right.bmp"))
    {
        std::cout << "Error loading image file cockpit_fire_right.bmp";
        std::cout << "\n";
    }

    if (!cockpit_cannon_texture.loadFromFile(cwd + "/assets/textures/cockpit/cockpit_cannon.bmp"))
    {
        std::cout << "Error loading image file cockpit_cannon.bmp";
        std::cout << "\n";
    }

    if (!cockpit_cannon_left_texture.loadFromFile(cwd + "/assets/textures/cockpit/cockpit_cannon_left.bmp"))
    {
        std::cout << "Error loading image file cockpit_cannon_left.bmp";
        std::cout << "\n";
    }

    if (!cockpit_cannon_right_texture.loadFromFile(cwd + "/assets/textures/cockpit/cockpit_cannon_right.bmp"))
    {
        std::cout << "Error loading image file cockpit_cannon_right.bmp";
        std::cout << "\n";
    }

    if (!cockpit_impact_texture.loadFromFile(cwd + "/assets/textures/cockpit/cockpit_impact.bmp"))
    {
        std::cout << "Error loading image file cockpit_impact.bmp";
        std::cout << "\n";
    }

    if (!cockpit_destroyed_texture.loadFromFile(cwd + "/assets/textures/cockpit/cockpit_destroyed.bmp"))
    {
        std::cout << "Error loading image file cockpit_destroyed.bmp";
        std::cout << "\n";
    }

    if (!ground_texture.loadFromFile(cwd + "/assets/textures/ground.bmp"))
    {
        std::cout << "Error loading image file ground.bmp";
        std::cout << "\n";
    }

    if (!ground_2_texture.loadFromFile(cwd + "/assets/textures/ground_2.bmp"))
    {
        std::cout << "Error loading image file ground_2.bmp";
        std::cout << "\n";
    }

    if (!sky_texture.loadFromFile(cwd + "/assets/textures/sky.bmp"))
    {
        std::cout << "Error loading image file sky.bmp";
        std::cout << "\n";
    }

    if (!sky_2_texture.loadFromFile(cwd + "/assets/textures/sky_2.png"))
    {
        std::cout << "Error loading image file sky_2.bmp";
        std::cout << "\n";
    }

    if (!mech_status_texture.loadFromFile(cwd + "/assets/textures/mech_status.bmp"))
    {
        std::cout << "Error loading image file mech_status.bmp";
        std::cout << "\n";
    }

    if (!gui_background_texture.loadFromFile(cwd + "/assets/textures/gui_background.png"))
    {
        std::cout << "Error loading image file gui_background.bmp";
        std::cout << "\n";
    }

    if (!gui_background_2_texture.loadFromFile(cwd + "/assets/textures/gui_background_2.png"))
    {
        std::cout << "Error loading image file gui_background_2.bmp";
        std::cout << "\n";
    }

    if (!target_gui_background_texture.loadFromFile(cwd + "/assets/textures/target_gui_background.png"))
    {
        std::cout << "Error loading image file target_gui_background.bmp";
        std::cout << "\n";
    }

    if (!wall_texture.loadFromFile(cwd + "/assets/textures/wall.bmp"))
    {
        std::cout << "Error loading image file wall.bmp";
        std::cout << "\n";
    }

    if (!wall_2_texture.loadFromFile(cwd + "/assets/textures/wall_2.bmp"))
    {
        std::cout << "Error loading image file wall_2.bmp";
        std::cout << "\n";
    }

    if (!tree_texture.loadFromFile(cwd + "/assets/textures/tree.bmp"))
    {
        std::cout << "Error loading image file tree.bmp";
        std::cout << "\n";
    }

    if (!tree_2_texture.loadFromFile(cwd + "/assets/textures/tree_2.png"))
    {
        std::cout << "Error loading image file tree_2.bmp";
        std::cout << "\n";
    }

    if (!tree_3_texture.loadFromFile(cwd + "/assets/textures/tree_3.png"))
    {
        std::cout << "Error loading image file tree_3.bmp";
        std::cout << "\n";
    }

    if (!tree_4_texture.loadFromFile(cwd + "/assets/textures/tree_4.png"))
    {
        std::cout << "Error loading image file tree_4.bmp";
        std::cout << "\n";
    }

    if (!player_icon_texture.loadFromFile(cwd + "/assets/textures/player_icon.png"))
    {
        std::cout << "Error loading image file player_icon.bmp";
        std::cout << "\n";
    }

    if (!mob_icon_texture.loadFromFile(cwd + "/assets/textures/mob_icon.png"))
    {
        std::cout << "Error loading image file mob_icon.bmp";
        std::cout << "\n";
    }

    if (!target_icon_texture.loadFromFile(cwd + "/assets/textures/target_icon.png"))
    {
        std::cout << "Error loading image file target_icon.bmp";
        std::cout << "\n";
    }

    if (!wall_icon_texture.loadFromFile(cwd + "/assets/textures/wall_icon.png"))
    {
        std::cout << "Error loading image file wall_icon.bmp";
        std::cout << "\n";
    }

    if (!menu_background_texture.loadFromFile(cwd + "/assets/textures/menu_background.png"))
    {
        std::cout << "Error loading image file menu_background.bmp";
        std::cout << "\n";
    }

    if (!menu_mech_texture.loadFromFile(cwd + "/assets/textures/mech_repair.png"))
    {
        std::cout << "Error loading image file mech_repair.bmp";
        std::cout << "\n";
    }

    if (!menu_mech_spark_1_texture.loadFromFile(cwd + "/assets/textures/mech_repair_spark_1.png"))
    {
        std::cout << "Error loading image file mech_repair_spark_1.bmp";
        std::cout << "\n";
    }

    if (!menu_mech_spark_2_texture.loadFromFile(cwd + "/assets/textures/mech_repair_spark_2.png"))
    {
        std::cout << "Error loading image file mech_repair_spark_2.bmp";
        std::cout << "\n";
    }

    if (!start_game_button_texture.loadFromFile(cwd + "/assets/textures/buttons/start_game_button.png"))
    {
        std::cout << "Error loading image file start_game_button.bmp";
        std::cout << "\n";
    }

    if (!start_game_button_hover_texture.loadFromFile(cwd + "/assets/textures/buttons/start_game_button_hover.png"))
    {
        std::cout << "Error loading image file start_game_button_hover.bmp";
        std::cout << "\n";
    }

    if (!main_menu_button_texture.loadFromFile(cwd + "/assets/textures/buttons/main_menu_button.png"))
    {
        std::cout << "Error loading image file main_menu_button.bmp";
        std::cout << "\n";
    }

    if (!main_menu_button_hover_texture.loadFromFile(cwd + "/assets/textures/buttons/main_menu_button_hover.png"))
    {
        std::cout << "Error loading image file main_menu_button_hover.bmp";
        std::cout << "\n";
    }

    if (!save_game_button_texture.loadFromFile(cwd + "/assets/textures/buttons/save_button.png"))
    {
        std::cout << "Error loading image file save_button.bmp";
        std::cout << "\n";
    }

    if (!save_game_button_hover_texture.loadFromFile(cwd + "/assets/textures/buttons/save_button_hover.png"))
    {
        std::cout << "Error loading image file save_button_hover.bmp";
        std::cout << "\n";
    }

    if (!load_game_button_texture.loadFromFile(cwd + "/assets/textures/buttons/load_button.png"))
    {
        std::cout << "Error loading image file load_button.bmp";
        std::cout << "\n";
    }

    if (!load_game_button_hover_texture.loadFromFile(cwd + "/assets/textures/buttons/load_button_hover.png"))
    {
        std::cout << "Error loading image file load_button_hover.bmp";
        std::cout << "\n";
    }

    if (!options_button_texture.loadFromFile(cwd + "/assets/textures/buttons/options_button.png"))
    {
        std::cout << "Error loading image file options_button.bmp";
        std::cout << "\n";
    }

    if (!options_button_hover_texture.loadFromFile(cwd + "/assets/textures/buttons/options_button_hover.png"))
    {
        std::cout << "Error loading image file options_button_hover.bmp";
        std::cout << "\n";
    }

    if (!repair_button_texture.loadFromFile(cwd + "/assets/textures/buttons/repair_button.png"))
    {
        std::cout << "Error loading image file repair_button.bmp";
        std::cout << "\n";
    }

    if (!market_button_texture.loadFromFile(cwd + "/assets/textures/buttons/market_button.png"))
    {
        std::cout << "Error loading image file market_button.bmp";
        std::cout << "\n";
    }

    if (!market_button_hover_texture.loadFromFile(cwd + "/assets/textures/buttons/market_button_hover.png"))
    {
        std::cout << "Error loading image file market_button_hover.bmp";
        std::cout << "\n";
    }

    if (!repair_button_hover_texture.loadFromFile(cwd + "/assets/textures/buttons/repair_button_hover.png"))
    {
        std::cout << "Error loading image file repair_button_hover.bmp";
        std::cout << "\n";
    }

    if (!exit_game_button_texture.loadFromFile(cwd + "/assets/textures/buttons/exit_game_button.png"))
    {
        std::cout << "Error loading image file exit_game_button.bmp";
        std::cout << "\n";
    }

    if (!exit_game_button_hover_texture.loadFromFile(cwd + "/assets/textures/buttons/exit_game_button_hover.png"))
    {
        std::cout << "Error loading image file exit_game_button_hover.bmp";
        std::cout << "\n";
    }

    if (!next_mission_button_texture.loadFromFile(cwd + "/assets/textures/buttons/next_mission_button.png"))
    {
        std::cout << "Error loading image file next_mission_button.bmp";
        std::cout << "\n";
    }

    if (!next_mission_button_hover_texture.loadFromFile(cwd + "/assets/textures/buttons/next_mission_button_hover.png"))
    {
        std::cout << "Error loading image file next_mission_button_hover.bmp";
        std::cout << "\n";
    }

    if (!create_new_button_texture.loadFromFile(cwd + "/assets/textures/buttons/create_new_button.png"))
    {
        std::cout << "Error loading image file create_new_button.bmp";
        std::cout << "\n";
    }

    if (!create_new_button_hover_texture.loadFromFile(cwd + "/assets/textures/buttons/create_new_button_hover.png"))
    {
        std::cout << "Error loading image file create_new_button_hover.bmp";
        std::cout << "\n";
    }

    if (!cancel_button_texture.loadFromFile(cwd + "/assets/textures/buttons/cancel_button.png"))
    {
        std::cout << "Error loading image file cancel_button.bmp";
        std::cout << "\n";
    }

    if (!cancel_button_hover_texture.loadFromFile(cwd + "/assets/textures/buttons/cancel_button_hover.png"))
    {
        std::cout << "Error loading image file cancel_button_hover.bmp";
        std::cout << "\n";
    }

    if (!term_texture.loadFromFile(cwd + "/assets/textures/term.bmp"))
    {
        std::cout << "Error loading image file term.bmp";
        std::cout << "\n";
    }
}

// Loads fonts from file
void assets::load_fonts(std::string cwd)
{
    if (!orbitron.loadFromFile(cwd + "/assets/Orbitron Medium.ttf"))
    {
        std::cout << "Error loading font file Orbitron Medium.ttf";
        std::cout << "\n";
    }

    if (!exoplanetaria.loadFromFile(cwd + "/assets/Exoplanetaria-gxxJ5.ttf"))
    {
        std::cout << "Error loading font file Exoplanetaria-gxxJ5.ttf";
        std::cout << "\n";
    }
}

// Assigns sound buffers
void assets::init_sounds()
{
    main_menu_music.setBuffer(main_menu_music_buffer);
    intermission_music.setBuffer(intermission_music_buffer);
    mission_music.setBuffer(mission_music_buffer);
    power_down_sound.setBuffer(power_down_sound_buffer);
    victory_sound.setBuffer(victory_sound_buffer);
    power_up_sound.setBuffer(power_up_sound_buffer);
    hydraulic_sound.setBuffer(hydraulic_sound_buffer);
    gun_sound.setBuffer(gun_sound_buffer);
    cannon_sound.setBuffer(cannon_sound_buffer);
    explosion_sound.setBuffer(explo_sound_buffer);
    stomp_sound.setBuffer(stomp_sound_buffer);
    crash_sound.setBuffer(crash_sound_buffer);
    impact_sound.setBuffer(impact_sound_buffer);
    purchase_sound.setBuffer(purchase_sound_buffer);
}

// Assigns textures to sprites
void assets::init_sprites()
{
    crosshair_sprite.setTexture(crosshair_texture);
    cockpit_sprite.setTexture(cockpit_texture);
    ground_sprite.setTexture(ground_texture);
    sky_sprite.setTexture(sky_texture);
    player_icon.setTexture(player_icon_texture);
    mob_icon.setTexture(mob_icon_texture);
    target_icon.setTexture(target_icon_texture);
    wall_icon.setTexture(wall_icon_texture);
    menu_background_sprite.setTexture(menu_background_texture);
    menu_mech_sprite.setTexture(menu_mech_texture);
    start_game_button_sprite.setTexture(start_game_button_texture);
    main_menu_button_sprite.setTexture(main_menu_button_texture);
    save_game_button_sprite.setTexture(save_game_button_texture);
    load_game_button_sprite.setTexture(load_game_button_texture);
    options_button_sprite.setTexture(options_button_texture);
    repair_button_sprite.setTexture(repair_button_texture);
    market_button_sprite.setTexture(market_button_texture);
    exit_game_button_sprite.setTexture(exit_game_button_texture);
    next_mission_button_sprite.setTexture(next_mission_button_texture);
    create_new_button_sprite.setTexture(create_new_button_texture);
    cancel_button_sprite.setTexture(cancel_button_texture);
    term_sprite.setTexture(term_texture);
}

// Sets up text objects
void assets::init_text()
{
    fps_counter.setFont(orbitron);
    fps_counter.setString("0");
    fps_counter.setCharacterSize(12);
    fps_counter.setFillColor(sf::Color::White);

    keys.setFont(exoplanetaria);
    keys.setString("");
    keys.setCharacterSize(12);
    keys.setFillColor(sf::Color::White);

    mech_status.setFont(orbitron);
    mech_status.setString("");
    mech_status.setCharacterSize(12);
    mech_status.setFillColor(sf::Color::Green);

    target_status.setFont(orbitron);
    target_status.setString("");
    target_status.setCharacterSize(12);
    target_status.setFillColor(sf::Color::Red);

    throttle_display.setFont(orbitron);
    throttle_display.setString("0");
    throttle_display.setCharacterSize(12);
    throttle_display.setFillColor(sf::Color::Green);

    torso_display.setFont(orbitron);
    torso_display.setString("0");
    torso_display.setCharacterSize(12);
    torso_display.setFillColor(sf::Color::Green);

    target_info.setFont(orbitron);
    target_info.setString("");
    target_info.setCharacterSize(12);
    target_info.setFillColor(sf::Color::Red);

    input_text.setFont(orbitron);
    input_text.setString("");
    input_text.setCharacterSize(12);
    input_text.setFillColor(sf::Color::White);

    notice.setFont(exoplanetaria);
    notice.setString("");
    notice.setCharacterSize(24);
    notice.setFillColor(sf::Color::White);
}

// Initializes all assets
void assets::init(std::string cwd)
{
    load_sound_buffers(cwd);
    load_textures(cwd);
    load_fonts(cwd);

    init_sounds();
    init_sprites();
    init_text();

    mech_textures = {mech_hit_center_texture,
                    mech_hit_center_texture,
                    mech_hit_left_arm_texture,
                    mech_hit_right_arm_texture,
                    mech_hit_left_leg_texture,
                    mech_hit_right_leg_texture,
                    mech_hit_cockpit_texture};

    sky_texture.setRepeated(true);
    sky_2_texture.setRepeated(true);

    unsigned int x = sf::VideoMode::getDesktopMode().width;
    unsigned int y = sf::VideoMode::getDesktopMode().height;
    sky_sprite.setTextureRect(sf::IntRect(0, 0, x, y));
}
