#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include <SFML/Graphics.hpp>
#include <assets.h>
#include <file_handler.h>
#include <settings_menu.h>
#include <player_controller.h>

class main_menu
{
    public:
        bool start_game;
        bool game_loaded;
        void init(std::string cwd, assets &resources);
        bool draw_menu(sf::RenderWindow &window, player_controller &pc, float frame_time);

    private:
        assets resources;
        settings_menu s_menu;
        sf::Vector2i mouse_position;
        bool load_prompt_open;
        bool show_load_notice;
        bool show_delete_notice;
        float delete_notice_timer;
        float load_notice_timer;
        float spark_timer;
        std::string cwd;
        std::vector<sf::VertexArray> load_game_buttons;
        std::vector<sf::Text> load_game_labels;
        std::vector<sf::VertexArray> delete_save_buttons;
        std::vector<sf::Text> delete_save_labels;
        void load_game(std::string cwd, std::string file, player_controller &pc);
        void delete_save_game(int i);
        void draw_load_menu(sf::RenderWindow &window);
};

#endif // MAIN_MENU_H
