#ifndef INTERMISSION_MENU_H
#define INTERMISSION_MENU_H

#include <stdio.h>
#include <assets.h>
#include <market_menu.h>
#include <file_handler.h>
#include <settings_menu.h>
#include <SFML/Graphics.hpp>
#include <player_controller.h>

class intermission_menu
{
    public:
        intermission_menu();
        market_menu market;
        bool start_game;
        bool return_to_main;
        void init(std::string cwd, assets &resources);
        bool draw_menu(sf::RenderWindow &window, player_controller &pc, float frame_time);

    private:
        assets resources;
        settings_menu s_menu;
        sf::Vector2i mouse_position;
        sf::String input;
        std::string cwd;
        std::string notice;
        std::string get_save_data(player_controller &pc);
        std::vector<sf::VertexArray> saved_game_buttons;
        std::vector<sf::VertexArray> delete_save_buttons;
        std::vector<sf::Text> delete_save_labels;
        std::vector<sf::Text> saved_game_labels;
        int kp;
        float notice_timer;
        float spark_timer;
        bool create_save_prompt_open;
        bool save_prompt_open;
        bool load_prompt_open;
        bool repair_prompt_open;
        bool show_notice;
        bool prompt_displayed();
        void create_save(player_controller &pc);
        void save_game(player_controller &pc, int i);
        void display_notice(sf::RenderWindow &window, std::string notice, float frame_time);
        void reset_game(player_controller &pc);
        void load_game(std::string cwd, std::string file, player_controller &pc);
        void delete_save_game(int i);
        void draw_saved_game_buttons(sf::RenderWindow &window);
        void draw_delete_buttons(sf::RenderWindow &window);
        void draw_save_menu(sf::RenderWindow &window);
        void draw_load_menu(sf::RenderWindow &window);
        void draw_repair_menu(sf::RenderWindow &window, player_controller &pc);
};

#endif // INTERMISSION_MENU_H
