#include <assets.h>
#include <iostream>
#include <settings.h>
#include <settings_menu.h>

// Gets the current working directory from main, initializes variables and objects
void settings_menu::init(std::string cwd, assets &resources, bool in_game)
{
    this->cwd = cwd;
    this->resources = resources;
    this->in_game = in_game;
    visible = false;
    abort_prompt_open = false;
    buttons.resize(5);
    button_text.resize(5);
    button_labels.resize(5);
    button_values.resize(5);
    abort_buttons.resize(2);
    abort_button_text.resize(2);
    abort_button_labels.resize(2);
    button_text[0] = " INVERT MOUSE";
    button_text[1] = " ENABLE MUSIC";
    button_text[2] = " AUDIO VOLUME";
    button_text[3] = "  RESUME GAME";
    button_text[4] = "ABORT MISSION";
    abort_button_text[0] = "ABORT";
    abort_button_text[1] = "RESUME";
}

// Mouse click events
void settings_menu::handle_events(sf::Event event, sf::Vector2i mouse_position)
{
    if (event.type == sf::Event::MouseButtonPressed)
    {
        if(event.mouseButton.button == sf::Mouse::Left)
        {
            if (abort_prompt_open == false)
            {
                for (unsigned int i = 0; i < buttons.size(); i++)
                {
                    if (buttons[i].getBounds().contains(mouse_position.x, mouse_position.y))
                    {
                        if (i == 0)
                        {
                            invert_mouse = !invert_mouse;
                        }
                        else if (i == 1)
                        {
                            music = !music;
                        }
                        else if (i == 2)
                        {
                            if (audio_volume <= 0.9)
                            {
                                audio_volume += 0.1;
                            }
                            else
                            {
                                audio_volume = 0.1;
                            }
                        }
                        else if (i == 3)
                        {
                            save_settings(cwd);
                            visible = false;
                        }
                        else if (i == 4 && in_game == true)
                        {
                            abort_prompt_open = true;
                        }
                    }
                }
            }
            else
            {
                for (unsigned int i = 0; i < abort_buttons.size(); i++)
                {
                    if (abort_buttons[i].getBounds().contains(mouse_position.x, mouse_position.y))
                    {
                        if (i == 0)
                        {
                            abort_mission = true;
                            abort_prompt_open = false;
                        }
                        else if (i == 1)
                        {
                            abort_prompt_open = false;
                        }
                    }
                }
            }
        }
    }
}

// Draws the menu
void settings_menu::draw_menu(sf::RenderWindow &window, sf::Vector2i mouse_position, float frame_time)
{
    if (abort_prompt_open == false)
    {
        sf::Sprite bg_sprite = sf::Sprite(resources.gui_background_2_texture);
        bg_sprite.setPosition(window.getView().getSize().x / 2 - 100, window.getView().getSize().y / 2 - 200);
        float y_scale = in_game == true ? 0.6 : 0.5;
        bg_sprite.setScale(0.2, y_scale);
        window.draw(bg_sprite);

        float y = window.getView().getSize().y / 2 - 180;

        button_text[3] = in_game == true ? "  RESUME GAME" : "    EXIT MENU";
        button_values[0].setString(invert_mouse == true ? "YES" :"NO");
        button_values[1].setString(music == true ? "YES" :"NO");
        button_values[2].setString(std::to_string((int)((100 * audio_volume) + 0.5)) + "%");

        for (unsigned int i = 0; i < buttons.size(); i++)
        {
            float x = window.getView().getSize().x / 2 - 70;

            buttons[i] = sf::VertexArray(sf::Quads, 4);
            buttons[i][0].position = sf::Vector2f(x, (y + i * 35) - 4);
            buttons[i][1].position = sf::Vector2f(x, (y + i * 35) + 24);
            buttons[i][2].position = sf::Vector2f(x + 140, (y + i * 35) + 24);
            buttons[i][3].position = sf::Vector2f(x + 140, (y + i * 35) - 4);

            sf::VertexArray button_shadow = sf::VertexArray(sf::Quads, 4);
            button_shadow[0].position = sf::Vector2f(x, (y + i * 35) - 4);
            button_shadow[1].position = sf::Vector2f(x, (y + i * 35) + 27);
            button_shadow[2].position = sf::Vector2f(x + 143, (y + i * 35) + 27);
            button_shadow[3].position = sf::Vector2f(x + 143, (y + i * 35) - 4);

            button_shadow[0].color = sf::Color::Black;
            button_shadow[1].color = sf::Color::Black;
            button_shadow[2].color = sf::Color::Black;
            button_shadow[3].color = sf::Color::Black;

            if (buttons[i].getBounds().contains(mouse_position.x, mouse_position.y))
            {
                buttons[i][0].color = sf::Color(53, 53, 53, 255);
                buttons[i][1].color = sf::Color(53, 53, 53, 255);
                buttons[i][2].color = sf::Color(53, 53, 53, 255);
                buttons[i][3].color = sf::Color(53, 53, 53, 255);
            }
            else
            {
                buttons[i][0].color = sf::Color(35, 35, 35, 255);
                buttons[i][1].color = sf::Color(35, 35, 35, 255);
                buttons[i][2].color = sf::Color(35, 35, 35, 255);
                buttons[i][3].color = sf::Color(35, 35, 35, 255);
            }

            button_labels[i].setFont(resources.exoplanetaria);
            button_labels[i].setCharacterSize(16);
            button_labels[i].setFillColor(sf::Color::Black);
            button_labels[i].setString(button_text[i]);

            button_values[i].setFont(resources.exoplanetaria);
            button_values[i].setCharacterSize(14);
            button_values[i].setFillColor(sf::Color::White);

            if (i == 0)
                button_labels[i].setPosition(x + 12, y);
            else
                button_labels[i].setPosition(x + 12, y + (i * 35));

            if (i == 0)
                button_values[i].setPosition(x + 180, y);
            else
                button_values[i].setPosition(x + 180, y + (i * 35));

            bool draw = true;

            if (i == 4)
            {
                draw = in_game == false? false : true;
            }

            if (draw == true)
            {
                window.draw(button_shadow);
                window.draw(buttons[i]);
                window.draw(button_labels[i]);
                window.draw(button_values[i]);
            }
        }
    }
    else
    {
        resources.notice.setFont(resources.orbitron);
        resources.notice.setString("ABORT MISSION?");
        sf::Vector2f text_pos;
        text_pos.x = (window.getView().getSize().x / 2) - (resources.notice.getGlobalBounds().width / 2);
        text_pos.y = (window.getView().getSize().y / 2) - 150;
        resources.notice.setPosition(text_pos);
        window.draw(resources.notice);
        resources.notice.setFont(resources.exoplanetaria);

        float x = window.getView().getSize().x / 2 - 70;
        float y = window.getView().getSize().y / 2 - 75;

        for (unsigned int i = 0; i < abort_buttons.size(); i++)
        {
            abort_buttons[i] = sf::VertexArray(sf::Quads, 4);
            abort_buttons[i][0].position = sf::Vector2f(x, (y + i * 35) - 4);
            abort_buttons[i][1].position = sf::Vector2f(x, (y + i * 35) + 24);
            abort_buttons[i][2].position = sf::Vector2f(x + 130, (y + i * 35) + 24);
            abort_buttons[i][3].position = sf::Vector2f(x + 130, (y + i * 35) - 4);

            sf::VertexArray button_shadow = sf::VertexArray(sf::Quads, 4);
            button_shadow[0].position = sf::Vector2f(x, (y + i * 35) - 4);
            button_shadow[1].position = sf::Vector2f(x, (y + i * 35) + 27);
            button_shadow[2].position = sf::Vector2f(x + 133, (y + i * 35) + 27);
            button_shadow[3].position = sf::Vector2f(x + 133, (y + i * 35) - 4);

            button_shadow[0].color = sf::Color::Black;
            button_shadow[1].color = sf::Color::Black;
            button_shadow[2].color = sf::Color::Black;
            button_shadow[3].color = sf::Color::Black;

            if (abort_buttons[i].getBounds().contains(mouse_position.x, mouse_position.y))
            {
                abort_buttons[i][0].color = sf::Color(53, 53, 53, 255);
                abort_buttons[i][1].color = sf::Color(53, 53, 53, 255);
                abort_buttons[i][2].color = sf::Color(53, 53, 53, 255);
                abort_buttons[i][3].color = sf::Color(53, 53, 53, 255);
            }
            else
            {
                abort_buttons[i][0].color = sf::Color(35, 35, 35, 255);
                abort_buttons[i][1].color = sf::Color(35, 35, 35, 255);
                abort_buttons[i][2].color = sf::Color(35, 35, 35, 255);
                abort_buttons[i][3].color = sf::Color(35, 35, 35, 255);
            }

            abort_button_labels[i].setFont(resources.exoplanetaria);
            abort_button_labels[i].setCharacterSize(16);
            abort_button_labels[i].setFillColor(sf::Color::Black);
            abort_button_labels[i].setString(abort_button_text[i]);

            if (i == 0)
                abort_button_labels[i].setPosition(x + 38, y);
            else
                abort_button_labels[i].setPosition(x + 38, y + (i * 35));

            window.draw(button_shadow);
            window.draw(abort_buttons[i]);
            window.draw(abort_button_labels[i]);
        }
    }
}
