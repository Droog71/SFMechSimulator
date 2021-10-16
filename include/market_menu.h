#ifndef MARKET_MENU_H
#define MARKET_MENU_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <player_controller.h>

class market_menu
{
    public:
        market_menu();

        struct item
        {
            std::string name;
            std::string type;
            int level;
            int modifier;
            int secondary_modifier;
            int price;
        };

        std::vector<int> item_worth;
        std::string notice;
        bool visible;
        bool show_notice;
        void generate_items();
        void init(std::string cwd);
        void handle_events(sf::Event event, player_controller &pc, sf::Vector2i mouse_position);
        void draw_menu(sf::RenderWindow &window, player_controller &pc, sf::Vector2i mouse_position);

    private:
        sf::Font market_font;
        sf::Texture gui_background_texture;
        sf::VertexArray exit_button;

        sf::SoundBuffer purchase_sound_buffer;
        sf::Sound purchase_sound;

        std::vector<std::string> sell_categories;

        std::vector<item> guns;
        std::vector<item> cannons;
        std::vector<item> reactors;
        std::vector<item> coolers;
        std::vector<item> cockpits;
        std::vector<item> arms;
        std::vector<item> legs;

        std::vector<sf::VertexArray> sell_buttons;
        std::vector<sf::VertexArray> gun_buttons;
        std::vector<sf::VertexArray> cannon_buttons;
        std::vector<sf::VertexArray> reactor_buttons;
        std::vector<sf::VertexArray> cooler_buttons;
        std::vector<sf::VertexArray> cockpit_buttons;
        std::vector<sf::VertexArray> arm_buttons;
        std::vector<sf::VertexArray> leg_buttons;

        std::vector<sf::Text> sell_button_labels;
        std::vector<sf::Text> gun_button_labels;
        std::vector<sf::Text> cannon_button_labels;
        std::vector<sf::Text> reactor_button_labels;
        std::vector<sf::Text> cooler_button_labels;
        std::vector<sf::Text> cockpit_button_labels;
        std::vector<sf::Text> arm_button_labels;
        std::vector<sf::Text> leg_button_labels;

        std::vector<sf::Text> gun_descriptions;
        std::vector<sf::Text> cannon_descriptions;
        std::vector<sf::Text> reactor_descriptions;
        std::vector<sf::Text> cooler_descriptions;
        std::vector<sf::Text> cockpit_descriptions;
        std::vector<sf::Text> arm_descriptions;
        std::vector<sf::Text> leg_descriptions;

        void purchase_item(player_controller &pc, item item_bought);
        void sell_item(player_controller &pc, std::string category);
};

#endif // MARKET_MENU_H
