#include <main_menu.h>
#include <settings.h>
#include <iostream>

// Gets current directory, initializes resources and settings menu
void main_menu::init(std::string cwd, assets &resources)
{
    this->cwd = cwd;
    this->resources = resources;
    s_menu.init(cwd, resources, false);
}

// Loads saved game data from file
void main_menu::load_game(std::string cwd, std::string file, player_controller &pc)
{
    int index = 0;
    size_t pos = 0;
    std::string token;
    std::string delimiter = "\n";
    std::vector<std::string> values(30);
    std::string data = get_file_contents(cwd + "/save/" + file + ".sav");

    while ((pos = data.find(delimiter)) != std::string::npos)
    {
        values[index] = data.substr(0, pos);
        data.erase(0, pos + delimiter.length());
        index++;
    }

    pc.credits = std::stoi(values[0]);
    pc.mission = std::stoi(values[1]);
    pc.player_mech.cockpit_integrity = std::stoi(values[2]);
    pc.player_mech.reactor_integrity = std::stoi(values[3]);
    pc.player_mech.cooler_integrity = std::stoi(values[4]);
    pc.player_mech.left_arm_integrity = std::stoi(values[5]);
    pc.player_mech.right_arm_integrity = std::stoi(values[6]);
    pc.player_mech.left_leg_integrity = std::stoi(values[7]);
    pc.player_mech.right_leg_integrity = std::stoi(values[8]);
    pc.player_mech.max_cockpit_integrity = std::stoi(values[9]);
    pc.player_mech.max_reactor_integrity = std::stoi(values[10]);
    pc.player_mech.max_cooler_integrity = std::stoi(values[11]);
    pc.player_mech.max_left_arm_integrity = std::stoi(values[12]);
    pc.player_mech.max_right_arm_integrity = std::stoi(values[13]);
    pc.player_mech.max_left_leg_integrity = std::stoi(values[14]);
    pc.player_mech.max_right_leg_integrity = std::stoi(values[15]);
    pc.player_mech.cooler_modifier = std::stoi(values[16]);
    pc.player_mech.guns_modifier = std::stoi(values[17]);
    pc.player_mech.cannons_modifier = std::stoi(values[18]);
    pc.player_mech.weight = std::stoi(values[19]);
    pc.player_mech.primary_weapon = values[20];
    pc.player_mech.secondary_weapon = values[21];
    pc.player_mech.reactor = values[22];
    pc.player_mech.cooler = values[23];
    pc.player_mech.left_leg = values[24];
    pc.player_mech.right_leg = values[25];
    pc.player_mech.left_arm = values[26];
    pc.player_mech.right_arm = values[27];
    pc.player_mech.cockpit = values[28];
}

// Deletes a saved game
void main_menu::delete_save_game(int i)
{
    std::string save_to_delete = cwd + "/save/" + load_game_labels[i].getString() + ".sav";
    char file [100];
    sprintf(file, "%s", save_to_delete.c_str());
    std::remove(file);
    std::string saves = get_file_contents(cwd + "/save/saves.list");
    std::string delimiter = "\n";
    std::string new_saves;
    std::string token;
    size_t pos = 0;
    while ((pos = saves.find(delimiter)) != std::string::npos)
    {
        token = saves.substr(0, pos);
        if (token != load_game_labels[i].getString())
        {
            new_saves += token + "\n";
        }
        saves.erase(0, pos + delimiter.length());
    }
    new_saves.erase(new_saves.find_last_not_of(" \n\r\t")+1);
    write_to_file(cwd + "/save/saves.list", new_saves);
    load_prompt_open = false;
    show_delete_notice = true;
}

// Draws the load game menu
void main_menu::draw_load_menu(sf::RenderWindow &window)
{
    int index = 0;
    size_t pos = 0;
    std::string saves = get_file_contents(cwd + "/save/saves.list");
    std::string delimiter = "\n";
    std::string token;

    // Get the number of saved games
    while ((pos = saves.find(delimiter)) != std::string::npos)
    {
        token = saves.substr(0, pos);
        saves.erase(0, pos + delimiter.length());
        index++;
    }

    load_game_buttons.resize(index);
    load_game_labels.resize(index);
    delete_save_buttons.resize(index);
    delete_save_labels.resize(index);

    // Reset variables
    pos = 0;
    index = 0;
    saves = get_file_contents(cwd + "/save/saves.list");

    // Create text objects for all existing save files
    while ((pos = saves.find(delimiter)) != std::string::npos)
    {
        token = saves.substr(0, pos);
        load_game_labels[index].setString(token);
        saves.erase(0, pos + delimiter.length());
        index++;
    }

    // Load game buttons
    for (unsigned int i = 0; i < load_game_labels.size(); i++)
    {
        float x = window.getView().getSize().x / 2 - 150;

        load_game_buttons[i] = sf::VertexArray(sf::Quads, 4);
        load_game_buttons[i][0].position = sf::Vector2f(x, (200 + i * 35) - 4);
        load_game_buttons[i][1].position = sf::Vector2f(x, (200 + i * 35) + 24);
        load_game_buttons[i][2].position = sf::Vector2f(x + 225, (200 + i * 35) + 24);
        load_game_buttons[i][3].position = sf::Vector2f(x + 225, (200 + i * 35) - 4);

        sf::VertexArray load_game_shadow = sf::VertexArray(sf::Quads, 4);
        load_game_shadow[0].position = sf::Vector2f(x, (200 + i * 35) - 4);
        load_game_shadow[1].position = sf::Vector2f(x, (200 + i * 35) + 27);
        load_game_shadow[2].position = sf::Vector2f(x + 228, (200 + i * 35) + 27);
        load_game_shadow[3].position = sf::Vector2f(x + 228, (200 + i * 35) - 4);

        load_game_shadow[0].color = sf::Color::Black;
        load_game_shadow[1].color = sf::Color::Black;
        load_game_shadow[2].color = sf::Color::Black;
        load_game_shadow[3].color = sf::Color::Black;

        if (load_game_buttons[i].getBounds().contains(mouse_position.x, mouse_position.y))
        {
            load_game_buttons[i][0].color = sf::Color(53, 53, 53, 255);
            load_game_buttons[i][1].color = sf::Color(53, 53, 53, 255);
            load_game_buttons[i][2].color = sf::Color(53, 53, 53, 255);
            load_game_buttons[i][3].color = sf::Color(53, 53, 53, 255);
        }
        else
        {
            load_game_buttons[i][0].color = sf::Color(35, 35, 35, 255);
            load_game_buttons[i][1].color = sf::Color(35, 35, 35, 255);
            load_game_buttons[i][2].color = sf::Color(35, 35, 35, 255);
            load_game_buttons[i][3].color = sf::Color(35, 35, 35, 255);
        }

        load_game_labels[i].setFont(resources.exoplanetaria);
        load_game_labels[i].setCharacterSize(16);
        load_game_labels[i].setFillColor(sf::Color::Black);
        load_game_labels[i].setPosition(x + 20, 202 + (i * 35 - 2));

        if (load_game_labels[i].getString() != "")
        {
            window.draw(load_game_shadow);
            window.draw(load_game_buttons[i]);
            window.draw(load_game_labels[i]);
        }
    }

    // Delete save buttons
    for (unsigned int i = 0; i < load_game_labels.size(); i++)
    {
        float x = window.getView().getSize().x / 2 + 100;

        delete_save_buttons[i] = sf::VertexArray(sf::Quads, 4);
        delete_save_buttons[i][0].position = sf::Vector2f(x, (200 + i * 35) - 4);
        delete_save_buttons[i][1].position = sf::Vector2f(x, (200 + i * 35) + 24);
        delete_save_buttons[i][2].position = sf::Vector2f(x + 70, (200 + i * 35) + 24);
        delete_save_buttons[i][3].position = sf::Vector2f(x + 70, (200 + i * 35) - 4);

        sf::VertexArray delete_save_shadow = sf::VertexArray(sf::Quads, 4);
        delete_save_shadow[0].position = sf::Vector2f(x, (200 + i * 35) - 4);
        delete_save_shadow[1].position = sf::Vector2f(x, (200 + i * 35) + 27);
        delete_save_shadow[2].position = sf::Vector2f(x + 73, (200 + i * 35) + 27);
        delete_save_shadow[3].position = sf::Vector2f(x + 73, (200 + i * 35) - 4);

        delete_save_shadow[0].color = sf::Color::Black;
        delete_save_shadow[1].color = sf::Color::Black;
        delete_save_shadow[2].color = sf::Color::Black;
        delete_save_shadow[3].color = sf::Color::Black;

        if (delete_save_buttons[i].getBounds().contains(mouse_position.x, mouse_position.y))
        {
            delete_save_buttons[i][0].color = sf::Color(53, 53, 53, 255);
            delete_save_buttons[i][1].color = sf::Color(53, 53, 53, 255);
            delete_save_buttons[i][2].color = sf::Color(53, 53, 53, 255);
            delete_save_buttons[i][3].color = sf::Color(53, 53, 53, 255);
        }
        else
        {
            delete_save_buttons[i][0].color = sf::Color(35, 35, 35, 255);
            delete_save_buttons[i][1].color = sf::Color(35, 35, 35, 255);
            delete_save_buttons[i][2].color = sf::Color(35, 35, 35, 255);
            delete_save_buttons[i][3].color = sf::Color(35, 35, 35, 255);
        }

        delete_save_labels[i].setFont(resources.exoplanetaria);
        delete_save_labels[i].setCharacterSize(16);
        delete_save_labels[i].setFillColor(sf::Color::Black);
        delete_save_labels[i].setPosition(x + 10, 200 + (i * 35));
        delete_save_labels[i].setString("DELETE");

        if (load_game_labels[i].getString() != "")
        {
            window.draw(delete_save_shadow);
            window.draw(delete_save_buttons[i]);
            window.draw(delete_save_labels[i]);
        }
    }

    // Cancel Button
    if (resources.cancel_button_sprite.getGlobalBounds().contains(mouse_position.x, mouse_position.y))
    {
        resources.cancel_button_sprite.setTexture(resources.cancel_button_hover_texture);
    }
    else
    {
        resources.cancel_button_sprite.setTexture(resources.cancel_button_texture);
    }
    float bx = (window.getView().getSize().x / 2) - (resources.cancel_button_texture.getSize().x / 2);
    float by = 150;
    sf::Vector2f bv(bx, by);
    resources.cancel_button_sprite.setPosition(bv);
    window.draw(resources.cancel_button_sprite);
}

// Handles all drawing and interaction with the menu
bool main_menu::draw_menu(sf::RenderWindow &window, player_controller &pc, float frame_time)
{
    if (start_game == false)
    {
        // Play music
        resources.main_menu_music.setVolume(100 * audio_volume);

        if (resources.main_menu_music.getStatus() != sf::Sound::Playing)
        {
            resources.main_menu_music.play();
        }

        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::MouseMoved)
            {
                mouse_position = sf::Mouse().getPosition(window);
            }

            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            if (s_menu.visible == false)
            {
                if (event.type == sf::Event::MouseButtonPressed)
                {
                    if(event.mouseButton.button == sf::Mouse::Left)
                    {
                        if (load_prompt_open == false)
                        {
                            if (resources.start_game_button_sprite.getGlobalBounds().contains(mouse_position.x, mouse_position.y))
                            {
                                resources.main_menu_music.stop();
                                start_game = true;
                            }

                            if (resources.options_button_sprite.getGlobalBounds().contains(mouse_position.x, mouse_position.y))
                            {
                                s_menu.visible = true;
                            }

                            if (resources.load_game_button_sprite.getGlobalBounds().contains(mouse_position.x, mouse_position.y))
                            {
                                load_prompt_open = true;
                            }

                            if (resources.exit_game_button_sprite.getGlobalBounds().contains(mouse_position.x, mouse_position.y))
                            {
                                window.close();
                            }
                        }
                        else
                        {
                            if (resources.cancel_button_sprite.getGlobalBounds().contains(mouse_position.x, mouse_position.y))
                            {
                                load_prompt_open = false;
                            }

                            for (unsigned int i = 0; i < load_game_labels.size(); i++)
                            {
                                if (load_game_buttons[i].getBounds().contains(mouse_position.x, mouse_position.y))
                                {
                                    load_game(cwd, load_game_labels[i].getString(), pc);
                                    load_prompt_open = false;
                                    show_load_notice = true;
                                }
                            }

                            for (unsigned int i = 0; i < delete_save_labels.size(); i++)
                            {
                                if (delete_save_buttons[i].getBounds().contains(mouse_position.x, mouse_position.y))
                                {
                                    delete_save_game(i);
                                }
                            }
                        }
                    }
                }

                if (event.type == sf::Event::KeyPressed)
                {
                    if (load_prompt_open == true)
                    {
                        if (event.key.code == sf::Keyboard::Escape)
                        {
                            load_prompt_open = false;
                        }
                    }
                    else if (s_menu.visible == true)
                    {
                        if (event.key.code == sf::Keyboard::Escape)
                        {
                            s_menu.visible = false;
                        }
                    }
                }
            }
            else
            {
                s_menu.handle_events(event, mouse_position);
            }
        }
        window.clear();

        // Draw the background
        resources.menu_background_sprite.setPosition(0,0);
        resources.menu_background_sprite.setScale(
            window.getView().getSize().x / resources.menu_background_sprite.getTexture()->getSize().x,
            window.getView().getSize().y / resources.menu_background_sprite.getTexture()->getSize().y);
        window.draw(resources.menu_background_sprite);

        // Randomly display welding sparks for the mech being repaired in the background
        spark_timer += 10 * frame_time;
        if (spark_timer >= 10)
        {
            spark_timer = 0;
            int random_spark = rand() % 90;

            if (random_spark >= 0 && random_spark < 30)
            {
                resources.menu_mech_sprite.setTexture(resources.menu_mech_texture);
            }
            else if (random_spark >= 30 && random_spark < 60)
            {
                resources.menu_mech_sprite.setTexture(resources.menu_mech_spark_1_texture);
            }
            else if (random_spark >= 60)
            {
                resources.menu_mech_sprite.setTexture(resources.menu_mech_spark_2_texture);
            }
        }
        resources.menu_mech_sprite.setScale(1.1, 1.1);
        float mech_x = window.getView().getSize().x / 2 - ((resources.menu_mech_sprite.getTexture()->getSize().x * 1.1) / 2);
        float mech_y = window.getView().getSize().y - 550;
        sf::Vector2f mech_position = sf::Vector2f(mech_x, mech_y);
        resources.menu_mech_sprite.setPosition(mech_position);
        window.draw(resources.menu_mech_sprite);

        if (load_prompt_open == false && s_menu.visible == false && show_load_notice == false && show_delete_notice == false)
        {
            // Start Game Button
            if (resources.start_game_button_sprite.getGlobalBounds().contains(mouse_position.x, mouse_position.y))
            {
                resources.start_game_button_sprite.setTexture(resources.start_game_button_hover_texture);
            }
            else
            {
                resources.start_game_button_sprite.setTexture(resources.start_game_button_texture);
            }
            float bx = (window.getView().getSize().x / 2) - (resources.start_game_button_texture.getSize().x / 2);
            float by = resources.menu_mech_sprite.getPosition().y + 40;
            sf::Vector2f bv(bx, by);
            resources.start_game_button_sprite.setPosition(bv);
            window.draw(resources.start_game_button_sprite);

            // Load Game Button
            if (resources.load_game_button_sprite.getGlobalBounds().contains(mouse_position.x, mouse_position.y))
            {
                resources.load_game_button_sprite.setTexture(resources.load_game_button_hover_texture);
            }
            else
            {
                resources.load_game_button_sprite.setTexture(resources.load_game_button_texture);
            }
            float b2x = (window.getView().getSize().x / 2) - (resources.load_game_button_texture.getSize().x / 2);
            float b2y = resources.menu_mech_sprite.getPosition().y + 90;
            sf::Vector2f b2v(b2x, b2y);
            resources.load_game_button_sprite.setPosition(b2v);
            window.draw(resources.load_game_button_sprite);

            // Options
            if (resources.options_button_sprite.getGlobalBounds().contains(mouse_position.x, mouse_position.y))
            {
                resources.options_button_sprite.setTexture(resources.options_button_hover_texture);
            }
            else
            {
                resources.options_button_sprite.setTexture(resources.options_button_texture);
            }
            float b3x = (window.getView().getSize().x / 2) - (resources.options_button_texture.getSize().x / 2);
            float b3y = resources.menu_mech_sprite.getPosition().y + 140;
            sf::Vector2f b3v(b3x, b3y);
            resources.options_button_sprite.setPosition(b3v);
            window.draw(resources.options_button_sprite);

            // Exit Button
            if (resources.exit_game_button_sprite.getGlobalBounds().contains(mouse_position.x, mouse_position.y))
            {
                resources.exit_game_button_sprite.setTexture(resources.exit_game_button_hover_texture);
            }
            else
            {
                resources.exit_game_button_sprite.setTexture(resources.exit_game_button_texture);
            }
            float b4x = (window.getView().getSize().x / 2) - (resources.exit_game_button_texture.getSize().x / 2);
            float b4y = resources.menu_mech_sprite.getPosition().y + 190;
            sf::Vector2f b4v(b4x, b4y);
            resources.exit_game_button_sprite.setPosition(b4v);
            window.draw(resources.exit_game_button_sprite);
        }
        else if (load_prompt_open == true)
        {
            draw_load_menu(window);
        }
        else if (show_load_notice == true && show_delete_notice == false)
        {
            sf::Vector2f text_pos;
            text_pos.x = (window.getView().getSize().x / 2) - (resources.notice.getGlobalBounds().width / 2);
            text_pos.y = (window.getView().getSize().y / 2) - 100;
            resources.notice.setString("GAME LOADED");
            resources.notice.setPosition(text_pos);
            window.draw(resources.notice);

            load_notice_timer += 10 * frame_time;
            if (load_notice_timer >= 30)
            {
                resources.main_menu_music.stop();
                load_notice_timer = 0;
                show_load_notice = false;
                game_loaded = true;
                start_game = true;
            }
        }
        else if (show_load_notice == false && show_delete_notice == true)
        {
            sf::Vector2f text_pos;
            text_pos.x = (window.getView().getSize().x / 2) - (resources.notice.getGlobalBounds().width / 2);
            text_pos.y = (window.getView().getSize().y / 2) - 100;
            resources.notice.setString("SAVE DELETED");
            resources.notice.setPosition(text_pos);
            window.draw(resources.notice);

            delete_notice_timer += 10 * frame_time;
            if (delete_notice_timer >= 30)
            {
                delete_notice_timer = 0;
                show_delete_notice = false;
            }
        }
        else if (s_menu.visible == true)
        {
            s_menu.draw_menu(window, mouse_position, frame_time);
        }

        window.display();
        return true;
    }
    else
    {
        return false;
    }
}
