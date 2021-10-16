#ifndef TUTORIAL_H
#define TUTORIAL_H

#include <math.h>
#include <iostream>
#include <SFML/Graphics.hpp>

class tutorial
{
    public:
        int step;
        bool visible;
        tutorial(std::string cwd);
        void draw_tutorial(sf::RenderWindow &window, bool show_keys, float speed, float torso_angle, float heat);

    private:
        sf::Texture gui_background_texture;
        sf::Sprite gui_background_sprite;
        sf::Text tutorial_text;
        sf::Font tutorial_font;
};

#endif // TUTORIAL_H
