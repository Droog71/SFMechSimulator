#ifndef SETTINGS_MENU_H
#define SETTINGS_MENU_H

#include <SFML/Graphics.hpp>

class settings_menu
{
    public:
        bool visible;
        bool in_game;
        bool abort_mission;
        bool abort_prompt_open;
        void init(std::string cwd, assets &resources, bool in_game);
        void handle_events(sf::Event event, sf::Vector2i mouse_position);
        void draw_menu(sf::RenderWindow &window, sf::Vector2i mouse_position, float frame_time);
    private:
        assets resources;
        std::string cwd;
        std::vector<sf::VertexArray> buttons;
        std::vector<sf::VertexArray> abort_buttons;
        std::vector<sf::Text> button_labels;
        std::vector<sf::Text> abort_button_labels;
        std::vector<sf::Text> button_values;
        std::vector<std::string> button_text;
        std::vector<std::string> abort_button_text;
};

#endif // SETTINGS_MENU_H
