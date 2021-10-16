#ifndef ASSETS_H
#define ASSETS_H

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

class assets
{
    public:
        // Sounds
        sf::SoundBuffer gun_sound_buffer;
        sf::Sound gun_sound;

        sf::SoundBuffer cannon_sound_buffer;
        sf::Sound cannon_sound;

        sf::SoundBuffer explo_sound_buffer;
        sf::Sound explosion_sound;

        sf::SoundBuffer hydraulic_sound_buffer;
        sf::Sound hydraulic_sound;

        sf::SoundBuffer stomp_sound_buffer;
        sf::Sound stomp_sound;

        sf::SoundBuffer crash_sound_buffer;
        sf::Sound crash_sound;

        sf::SoundBuffer impact_sound_buffer;
        sf::Sound impact_sound;

        sf::SoundBuffer power_down_sound_buffer;
        sf::Sound power_down_sound;

        sf::SoundBuffer power_up_sound_buffer;
        sf::Sound power_up_sound;

        sf::SoundBuffer purchase_sound_buffer;
        sf::Sound purchase_sound;

        sf::SoundBuffer main_menu_music_buffer;
        sf::Sound main_menu_music;

        sf::SoundBuffer intermission_music_buffer;
        sf::Sound intermission_music;

        sf::SoundBuffer mission_music_buffer;
        sf::Sound mission_music;

        sf::SoundBuffer victory_sound_buffer;
        sf::Sound victory_sound;

        // Textures
        sf::Texture mech_status_texture;
        sf::Texture mech_texture;
        sf::Texture mech_fire_guns_texture;
        sf::Texture mech_fire_guns_left_texture;
        sf::Texture mech_fire_guns_right_texture;
        sf::Texture mech_fire_cannons_texture;
        sf::Texture mech_fire_cannons_left_texture;
        sf::Texture mech_fire_cannons_right_texture;
        sf::Texture mech_hit_center_texture;
        sf::Texture mech_hit_left_leg_texture;
        sf::Texture mech_hit_right_leg_texture;
        sf::Texture mech_hit_left_arm_texture;
        sf::Texture mech_hit_right_arm_texture;
        sf::Texture mech_hit_cockpit_texture;
        std::vector<sf::Texture> mech_textures;

        sf::Texture cockpit_texture;
        sf::Texture cockpit_fire_texture;
        sf::Texture cockpit_fire_left_texture;
        sf::Texture cockpit_fire_right_texture;
        sf::Texture cockpit_cannon_texture;
        sf::Texture cockpit_cannon_left_texture;
        sf::Texture cockpit_cannon_right_texture;
        sf::Texture cockpit_impact_texture;
        sf::Texture cockpit_destroyed_texture;

        sf::Texture explosion_texture;
        sf::Texture crosshair_texture;
        sf::Texture ground_texture;
        sf::Texture ground_2_texture;
        sf::Sprite ground_sprite;
        sf::Texture sky_texture;
        sf::Texture sky_2_texture;
        sf::Texture wall_texture;
        sf::Texture wall_2_texture;
        sf::Texture tree_texture;
        sf::Texture tree_2_texture;
        sf::Texture tree_3_texture;
        sf::Texture tree_4_texture;
        sf::Texture player_icon_texture;
        sf::Texture mob_icon_texture;
        sf::Texture target_icon_texture;
        sf::Texture wall_icon_texture;

        sf::Texture gui_background_texture;
        sf::Texture gui_background_2_texture;
        sf::Texture target_gui_background_texture;

        sf::Texture menu_background_texture;
        sf::Texture menu_mech_texture;
        sf::Texture menu_mech_spark_1_texture;
        sf::Texture menu_mech_spark_2_texture;
        sf::Texture term_texture;

        sf::Texture start_game_button_texture;
        sf::Texture start_game_button_hover_texture;
        sf::Texture main_menu_button_texture;
        sf::Texture main_menu_button_hover_texture;
        sf::Texture save_game_button_texture;
        sf::Texture save_game_button_hover_texture;
        sf::Texture load_game_button_texture;
        sf::Texture load_game_button_hover_texture;
        sf::Texture next_mission_button_texture;
        sf::Texture next_mission_button_hover_texture;
        sf::Texture repair_button_texture;
        sf::Texture repair_button_hover_texture;
        sf::Texture market_button_texture;
        sf::Texture market_button_hover_texture;
        sf::Texture exit_game_button_texture;
        sf::Texture exit_game_button_hover_texture;
        sf::Texture create_new_button_texture;
        sf::Texture create_new_button_hover_texture;
        sf::Texture cancel_button_texture;
        sf::Texture cancel_button_hover_texture;
        sf::Texture options_button_texture;
        sf::Texture options_button_hover_texture;

        // Sprites
        sf::Sprite cockpit_sprite;
        sf::Sprite sky_sprite;
        sf::Sprite map_sprite;
        sf::Sprite term_sprite;
        sf::Sprite crosshair_sprite;
        sf::Sprite player_icon;
        sf::Sprite mob_icon;
        sf::Sprite wall_icon;
        sf::Sprite target_icon;

        sf::Sprite start_game_button_sprite;
        sf::Sprite main_menu_button_sprite;
        sf::Sprite save_game_button_sprite;
        sf::Sprite create_new_button_sprite;
        sf::Sprite cancel_button_sprite;
        sf::Sprite load_game_button_sprite;
        sf::Sprite options_button_sprite;
        sf::Sprite next_mission_button_sprite;
        sf::Sprite repair_button_sprite;
        sf::Sprite market_button_sprite;
        sf::Sprite exit_game_button_sprite;
        sf::Sprite menu_background_sprite;
        sf::Sprite menu_mech_sprite;

        // Fonts
        sf::Font orbitron;
        sf::Font exoplanetaria;

        // Text Objects
        sf::Text notice;
        sf::Text keys;
        sf::Text fps_counter;
        sf::Text throttle_display;
        sf::Text torso_display;
        sf::Text input_text;
        sf::Text mech_status;
        sf::Text target_status;
        sf::Text target_info;

        void init(std::string cwd);

    private:
        void load_sound_buffers(std::string cwd);
        void load_textures(std::string cwd);
        void load_fonts(std::string cwd);
        void init_sounds();
        void init_sprites();
        void init_text();
};

#endif // ASSETS_H
