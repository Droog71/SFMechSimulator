#include <intermission_menu.h>
#include <settings.h>
#include <iostream>

// Constructor
intermission_menu::intermission_menu()
{
    kp = 0;
    spark_timer = 0;
    start_game = false;
    return_to_main = false;
}

// Gets the current directory, initializes resources, market menu and settings menu
void intermission_menu::init(std::string cwd, assets &resources)
{
    this->cwd = cwd;
    this->resources = resources;
    market.init(cwd);
    s_menu.init(cwd, resources, false);
}

// Returns true if a prompt is displayed
bool intermission_menu::prompt_displayed()
{
    return save_prompt_open == true || load_prompt_open == true || repair_prompt_open == true;
}

// Displays a notice with the given string
void intermission_menu::display_notice(sf::RenderWindow &window, std::string notice, float frame_time)
{
    sf::Vector2f notice_pos;
    notice_pos.x = (window.getView().getSize().x / 2) - (resources.notice.getGlobalBounds().width / 2);
    notice_pos.y = (window.getView().getSize().y / 2) - 100;
    resources.notice.setString(notice);
    resources.notice.setPosition(notice_pos);
    window.draw(resources.notice);

    notice_timer += 10 * frame_time;
    if (notice_timer >= 30)
    {
        notice_timer = 0;
        show_notice = false;
        market.show_notice = false;
    }
}

// Draws butons associated with saved games
void intermission_menu::draw_saved_game_buttons(sf::RenderWindow &window)
{
    float x = window.getView().getSize().x / 2 - 150;

    for (unsigned int i = 0; i < saved_game_labels.size(); i++)
    {
        saved_game_buttons[i] = sf::VertexArray(sf::Quads, 4);
        saved_game_buttons[i][0].position = sf::Vector2f(x, (200 + i * 35) - 4);
        saved_game_buttons[i][1].position = sf::Vector2f(x, (200 + i * 35) + 24);
        saved_game_buttons[i][2].position = sf::Vector2f(x + 225, (200 + i * 35) + 24);
        saved_game_buttons[i][3].position = sf::Vector2f(x + 225, (200 + i * 35) - 4);

        sf::VertexArray saved_game_shadow = sf::VertexArray(sf::Quads, 4);
        saved_game_shadow[0].position = sf::Vector2f(x, (200 + i * 35) - 4);
        saved_game_shadow[1].position = sf::Vector2f(x, (200 + i * 35) + 27);
        saved_game_shadow[2].position = sf::Vector2f(x + 228, (200 + i * 35) + 27);
        saved_game_shadow[3].position = sf::Vector2f(x + 228, (200 + i * 35) - 4);

        saved_game_shadow[0].color = sf::Color::Black;
        saved_game_shadow[1].color = sf::Color::Black;
        saved_game_shadow[2].color = sf::Color::Black;
        saved_game_shadow[3].color = sf::Color::Black;

        if (saved_game_buttons[i].getBounds().contains(mouse_position.x, mouse_position.y))
        {
            saved_game_buttons[i][0].color = sf::Color(53, 53, 53, 255);
            saved_game_buttons[i][1].color = sf::Color(53, 53, 53, 255);
            saved_game_buttons[i][2].color = sf::Color(53, 53, 53, 255);
            saved_game_buttons[i][3].color = sf::Color(53, 53, 53, 255);
        }
        else
        {
            saved_game_buttons[i][0].color = sf::Color(35, 35, 35, 255);
            saved_game_buttons[i][1].color = sf::Color(35, 35, 35, 255);
            saved_game_buttons[i][2].color = sf::Color(35, 35, 35, 255);
            saved_game_buttons[i][3].color = sf::Color(35, 35, 35, 255);
        }

        saved_game_labels[i].setFont(resources.exoplanetaria);
        saved_game_labels[i].setCharacterSize(16);
        saved_game_labels[i].setFillColor(sf::Color::Black);
        saved_game_labels[i].setPosition(x + 20, 200 + (i * 35));

        if (saved_game_labels[i].getString() != "")
        {
            window.draw(saved_game_shadow);
            window.draw(saved_game_buttons[i]);
            window.draw(saved_game_labels[i]);
        }
    }
}

// Draws buttons used to delete saved games
void intermission_menu::draw_delete_buttons(sf::RenderWindow &window)
{
    float x = window.getView().getSize().x / 2 + 100;

    for (unsigned int i = 0; i < saved_game_labels.size(); i++)
    {
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

        if (saved_game_labels[i].getString() != "")
        {
            window.draw(delete_save_shadow);
            window.draw(delete_save_buttons[i]);
            window.draw(delete_save_labels[i]);
        }
    }
}

// Returns saved game data as a single string
std::string intermission_menu::get_save_data(player_controller &pc)
{
    return std::to_string(pc.credits) + "\n" +
            std::to_string(pc.mission) + "\n" +
            std::to_string(pc.player_mech.cockpit_integrity) + "\n" +
            std::to_string(pc.player_mech.reactor_integrity) + "\n" +
            std::to_string(pc.player_mech.cooler_integrity)+ "\n" +
            std::to_string(pc.player_mech.left_arm_integrity) + "\n" +
            std::to_string(pc.player_mech.right_arm_integrity) + "\n" +
            std::to_string(pc.player_mech.left_leg_integrity) + "\n" +
            std::to_string(pc.player_mech.right_leg_integrity) + "\n" +
            std::to_string(pc.player_mech.max_cockpit_integrity) + "\n" +
            std::to_string(pc.player_mech.max_reactor_integrity) + "\n" +
            std::to_string(pc.player_mech.max_cooler_integrity) + "\n" +
            std::to_string(pc.player_mech.max_left_arm_integrity) + "\n" +
            std::to_string(pc.player_mech.max_right_arm_integrity) + "\n" +
            std::to_string(pc.player_mech.max_left_leg_integrity) + "\n" +
            std::to_string(pc.player_mech.max_right_leg_integrity) + "\n" +
            std::to_string(pc.player_mech.cooler_modifier) + "\n" +
            std::to_string(pc.player_mech.guns_modifier) + "\n" +
            std::to_string(pc.player_mech.cannons_modifier) + "\n" +
            std::to_string(pc.player_mech.weight) + "\n" +
            pc.player_mech.primary_weapon + "\n" +
            pc.player_mech.secondary_weapon + "\n" +
            pc.player_mech.reactor + "\n" +
            pc.player_mech.cooler + "\n" +
            pc.player_mech.left_leg + "\n" +
            pc.player_mech.right_leg + "\n" +
            pc.player_mech.left_arm + "\n" +
            pc.player_mech.right_arm + "\n" +
            pc.player_mech.cockpit;
}

// Creates a new save game
void intermission_menu::create_save(player_controller &pc)
{
    std::string saves = get_file_contents(cwd + "/save/saves.list");
    std::string delimiter = "\n";
    std::string token;

    int index = 0;
    size_t pos = 0;
    while ((pos = saves.find(delimiter)) != std::string::npos)
    {
        token = saves.substr(0, pos);
        saves.erase(0, pos + delimiter.length());
        index++;
    }

    if (index < 10)
    {
        std::string save = append_file(cwd + "/save/saves.list", input);
        std::string result = write_to_file(cwd + "/save/" + input + ".sav", get_save_data(pc));
        save_prompt_open = false;
        create_save_prompt_open = false;
        notice = "GAME SAVED";
        show_notice = true;
    }
    else
    {
        notice = "SAVE LIMIT REACHED";
        show_notice = true;
    }

    input = "";
    resources.input_text.setString(input);
}

// Overwrites an existing save game
void intermission_menu::save_game(player_controller &pc, int i)
{
    std::string result = write_to_file(cwd + "/save/" + saved_game_labels[i].getString() + ".sav", get_save_data(pc));
    save_prompt_open = false;
    notice = "GAME SAVED";
    show_notice = true;
}

// Loads a saved game
void intermission_menu::load_game(std::string cwd, std::string file, player_controller &pc)
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
void intermission_menu::delete_save_game(int i)
{
    std::string save_to_delete = cwd + "/save/" + saved_game_labels[i].getString() + ".sav";
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
        if (token != saved_game_labels[i].getString())
        {
            new_saves += token + "\n";
        }
        saves.erase(0, pos + delimiter.length());
    }
    new_saves.erase(new_saves.find_last_not_of(" \n\r\t")+1);
    write_to_file(cwd + "/save/saves.list", new_saves);
    notice = "SAVE DELETED";
    show_notice = true;
}

// Resets all game related progress
void intermission_menu::reset_game(player_controller &pc)
{
    pc.credits = 0;
    pc.mission = 1;
    pc.player_mech.cockpit_integrity = 1000;
    pc.player_mech.reactor_integrity = 1000;
    pc.player_mech.cooler_integrity = 1000;
    pc.player_mech.left_arm_integrity = 1000;
    pc.player_mech.right_arm_integrity = 1000;
    pc.player_mech.left_leg_integrity = 1000;
    pc.player_mech.right_leg_integrity = 1000;
    pc.player_mech.max_cockpit_integrity = 1000;
    pc.player_mech.max_reactor_integrity = 1000;
    pc.player_mech.max_cooler_integrity = 1000;
    pc.player_mech.max_left_arm_integrity = 1000;
    pc.player_mech.max_right_arm_integrity = 1000;
    pc.player_mech.max_left_leg_integrity = 1000;
    pc.player_mech.max_right_leg_integrity = 1000;
    pc.player_mech.cooler_modifier = 0;
    pc.player_mech.guns_modifier = 0;
    pc.player_mech.cannons_modifier = 0;
    pc.player_mech.weight = 70;
    pc.player_mech.primary_weapon = "Standard Pulse Laser";
    pc.player_mech.secondary_weapon = "Standard Autocannon";
    pc.player_mech.reactor = "Standard Reactor";
    pc.player_mech.cooler = "Standard Cooler";
    pc.player_mech.left_leg = "Standard Left Leg";
    pc.player_mech.right_leg = "Standard Right Leg";
    pc.player_mech.left_arm = "Standard Left Arm";
    pc.player_mech.right_arm = "Standard Right Arm";
    pc.player_mech.cockpit = "Standard Cockpit";
}

// Draws the repair menu
void intermission_menu::draw_repair_menu(sf::RenderWindow &window, player_controller &pc)
{
    // Title
    int cost_to_repair = 10 * (pc.player_mech.max_total_integrity() - pc.player_mech.total_integrity());
    sf::Vector2f notice_pos;
    notice_pos.x = (window.getView().getSize().x / 2) - (resources.notice.getGlobalBounds().width / 2);
    notice_pos.y = (window.getView().getSize().y / 2) - 120;
    if (cost_to_repair > 0)
    {
        resources.notice.setString("Repairing your mech will cost " + std::to_string(cost_to_repair) + " credits.");
    }
    else
    {
        resources.notice.setString("Your mech is not in need of repair.");
    }
    resources.notice.setPosition(notice_pos);
    window.draw(resources.notice);

    // Repair Button
    if (resources.repair_button_sprite.getGlobalBounds().contains(mouse_position.x, mouse_position.y))
    {
        resources.repair_button_sprite.setTexture(resources.repair_button_hover_texture);
    }
    else
    {
        resources.repair_button_sprite.setTexture(resources.repair_button_texture);
    }
    float b3x = (window.getView().getSize().x / 2) - (resources.repair_button_texture.getSize().x / 2);
    float b3y = (window.getView().getSize().y / 2) - 20;
    sf::Vector2f b3v(b3x, b3y);
    resources.repair_button_sprite.setPosition(b3v);
    window.draw(resources.repair_button_sprite);

    // Cancel Button
    if (resources.cancel_button_sprite.getGlobalBounds().contains(mouse_position.x, mouse_position.y))
    {
        resources.cancel_button_sprite.setTexture(resources.cancel_button_hover_texture);
    }
    else
    {
        resources.cancel_button_sprite.setTexture(resources.cancel_button_texture);
    }
    float cx = (window.getView().getSize().x / 2) - (resources.cancel_button_texture.getSize().x / 2);
    float cy =  (window.getView().getSize().y / 2) + 20;
    sf::Vector2f cv(cx, cy);
    resources.cancel_button_sprite.setPosition(cv);
    window.draw(resources.cancel_button_sprite);
}

// Draws the save game menu
void intermission_menu::draw_save_menu(sf::RenderWindow &window)
{
    if (create_save_prompt_open == true)
    {
        sf::Vector2f term_pos;
        sf::Vector2f text_pos;
        term_pos.x = (window.getView().getSize().x / 2) - (resources.term_sprite.getTexture()->getSize().x / 2);
        term_pos.y = (window.getView().getSize().y / 2) - 70;
        text_pos.x = term_pos.x + 8;
        text_pos.y = term_pos.y + 8;
        resources.term_sprite.setPosition(term_pos);
        resources.input_text.setPosition(text_pos);
        window.draw(resources.term_sprite);
        window.draw(resources.input_text);

        sf::Vector2f notice_pos;
        notice_pos.x = (window.getView().getSize().x / 2) - (resources.notice.getGlobalBounds().width / 2);
        notice_pos.y = (window.getView().getSize().y / 2) - 120;
        resources.notice.setString("Enter a name for your saved game.");
        resources.notice.setPosition(notice_pos);
        window.draw(resources.notice);

        // Save Button
        if (resources.save_game_button_sprite.getGlobalBounds().contains(mouse_position.x, mouse_position.y))
        {
            resources.save_game_button_sprite.setTexture(resources.save_game_button_hover_texture);
        }
        else
        {
            resources.save_game_button_sprite.setTexture(resources.save_game_button_texture);
        }
        float b3x = (window.getView().getSize().x / 2) - (resources.save_game_button_texture.getSize().x / 2);
        float b3y = (window.getView().getSize().y / 2) - 20;
        sf::Vector2f b3v(b3x, b3y);
        resources.save_game_button_sprite.setPosition(b3v);
        window.draw(resources.save_game_button_sprite);

        // Cancel Button
        if (resources.cancel_button_sprite.getGlobalBounds().contains(mouse_position.x, mouse_position.y))
        {
            resources.cancel_button_sprite.setTexture(resources.cancel_button_hover_texture);
        }
        else
        {
            resources.cancel_button_sprite.setTexture(resources.cancel_button_texture);
        }
        float b4x = (window.getView().getSize().x / 2) - (resources.load_game_button_texture.getSize().x / 2);
        float b4y = (window.getView().getSize().y / 2) + 20;
        sf::Vector2f b4v(b4x, b4y);
        resources.cancel_button_sprite.setPosition(b4v);
        window.draw(resources.cancel_button_sprite);
    }
    else
    {
        // Create new save button
        if (resources.create_new_button_sprite.getGlobalBounds().contains(mouse_position.x, mouse_position.y))
        {
            resources.create_new_button_sprite.setTexture(resources.create_new_button_hover_texture);
        }
        else
        {
            resources.create_new_button_sprite.setTexture(resources.create_new_button_texture);
        }
        float bx = (window.getView().getSize().x / 2) - (resources.create_new_button_texture.getSize().x / 2);
        float by = 150;
        sf::Vector2f bv(bx, by);
        resources.create_new_button_sprite.setPosition(bv);
        window.draw(resources.create_new_button_sprite);

        // Cancel button
        if (resources.cancel_button_sprite.getGlobalBounds().contains(mouse_position.x, mouse_position.y))
        {
            resources.cancel_button_sprite.setTexture(resources.cancel_button_hover_texture);
        }
        else
        {
            resources.cancel_button_sprite.setTexture(resources.cancel_button_texture);
        }
        float cx = (window.getView().getSize().x / 2) - (resources.cancel_button_texture.getSize().x / 2);
        float cy = 100;
        sf::Vector2f cv(cx, cy);
        resources.cancel_button_sprite.setPosition(cv);
        window.draw(resources.cancel_button_sprite);

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

        // Resize arrays
        saved_game_buttons.resize(index);
        saved_game_labels.resize(index);
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
            saved_game_labels[index].setString(token);
            saves.erase(0, pos + delimiter.length());
            index++;
        }

        // Save game buttons
        draw_saved_game_buttons(window);

        // Delete save buttons
        draw_delete_buttons(window);
    }
}

// Draws the load game menu
void intermission_menu::draw_load_menu(sf::RenderWindow &window)
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

    // Resize arrays
    saved_game_buttons.resize(index);
    saved_game_labels.resize(index);
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
        saved_game_labels[index].setString(token);
        saves.erase(0, pos + delimiter.length());
        index++;
    }

    // Load game buttons
    draw_saved_game_buttons(window);

    // Delete save buttons
    draw_delete_buttons(window);

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
bool intermission_menu::draw_menu(sf::RenderWindow &window, player_controller &pc, float frame_time)
{
    if (start_game == false && return_to_main == false)
    {
        // Play intermission music
        resources.intermission_music.setVolume(50 * audio_volume);

        if (resources.intermission_music.getStatus() != sf::Sound::Playing)
        {
            resources.intermission_music.play();
        }

        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window : exit
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            if(event.type == sf::Event::MouseMoved)
            {
                mouse_position = sf::Mouse().getPosition(window);
            }

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if(event.mouseButton.button == sf::Mouse::Left)
                {
                    if (prompt_displayed() == false && show_notice == false && market.visible == false && s_menu.visible == false)
                    {
                        if (resources.next_mission_button_sprite.getGlobalBounds().contains(mouse_position.x, mouse_position.y))
                        {
                            if (pc.player_mech.destroyed() == false)
                            {
                                resources.intermission_music.stop();
                                start_game = true;
                            }
                            else
                            {
                                notice = "YOUR MECH IS INOPERABLE";
                                show_notice = true;
                            }
                        }

                        if (resources.repair_button_sprite.getGlobalBounds().contains(mouse_position.x, mouse_position.y))
                        {
                            repair_prompt_open = true;
                        }

                        if (resources.market_button_sprite.getGlobalBounds().contains(mouse_position.x, mouse_position.y))
                        {
                            market.visible = true;
                        }

                        if (resources.save_game_button_sprite.getGlobalBounds().contains(mouse_position.x, mouse_position.y))
                        {
                            save_prompt_open = true;
                        }

                        if (resources.load_game_button_sprite.getGlobalBounds().contains(mouse_position.x, mouse_position.y))
                        {
                            load_prompt_open = true;
                        }

                        if (resources.options_button_sprite.getGlobalBounds().contains(mouse_position.x, mouse_position.y))
                        {
                            s_menu.visible = true;
                        }

                        if (resources.main_menu_button_sprite.getGlobalBounds().contains(mouse_position.x, mouse_position.y))
                        {
                            resources.intermission_music.stop();
                            reset_game(pc);
                            return_to_main = true;
                        }
                    }
                    else if (save_prompt_open == true)
                    {
                        if (create_save_prompt_open == true)
                        {
                            if (resources.save_game_button_sprite.getGlobalBounds().contains(mouse_position.x, mouse_position.y))
                            {
                                create_save(pc);
                            }

                            if (resources.cancel_button_sprite.getGlobalBounds().contains(mouse_position.x, mouse_position.y))
                            {
                                create_save_prompt_open = false;
                            }
                        }
                        else
                        {
                            if (resources.create_new_button_sprite.getGlobalBounds().contains(mouse_position.x, mouse_position.y))
                            {
                                create_save_prompt_open = true;
                            }

                            if (resources.cancel_button_sprite.getGlobalBounds().contains(mouse_position.x, mouse_position.y))
                            {
                                save_prompt_open = false;
                            }

                            for (unsigned int i = 0; i < saved_game_labels.size(); i++)
                            {
                                if (saved_game_buttons[i].getBounds().contains(mouse_position.x, mouse_position.y))
                                {
                                    save_game(pc, i);
                                }
                            }

                            for (unsigned int i = 0; i < delete_save_labels.size(); i++)
                            {
                                if (delete_save_buttons[i].getBounds().contains(mouse_position.x, mouse_position.y))
                                {
                                    delete_save_game(i);
                                    save_prompt_open = false;
                                }
                            }
                        }
                    }
                    else if (load_prompt_open == true)
                    {
                        if (resources.cancel_button_sprite.getGlobalBounds().contains(mouse_position.x, mouse_position.y))
                        {
                            load_prompt_open = false;
                        }

                        for (unsigned int i = 0; i < saved_game_labels.size(); i++)
                        {
                            if (saved_game_buttons[i].getBounds().contains(mouse_position.x, mouse_position.y))
                            {
                                load_game(cwd, saved_game_labels[i].getString(), pc);
                                load_prompt_open = false;
                                notice = "GAME LOADED";
                                show_notice = true;
                            }
                        }

                        for (unsigned int i = 0; i < delete_save_labels.size(); i++)
                        {
                            if (delete_save_buttons[i].getBounds().contains(mouse_position.x, mouse_position.y))
                            {
                                delete_save_game(i);
                                load_prompt_open = false;
                            }
                        }
                    }
                    else if (repair_prompt_open == true)
                    {
                        if (resources.repair_button_sprite.getGlobalBounds().contains(mouse_position.x, mouse_position.y))
                        {
                            int cost_to_repair = 10 * (pc.player_mech.max_total_integrity() - pc.player_mech.total_integrity());
                            if (cost_to_repair > 0)
                            {
                                if (pc.credits >= cost_to_repair)
                                {
                                    pc.credits -= cost_to_repair;
                                    pc.player_mech.repair();
                                    resources.purchase_sound.setVolume(100 * audio_volume);
                                    resources.purchase_sound.play();
                                    repair_prompt_open = false;
                                    notice = "MECH REPAIRED";
                                    show_notice = true;
                                }
                                else
                                {
                                    notice = "INSUFFICIENT FUNDS";
                                    show_notice = true;
                                }
                            }
                        }

                        if (resources.cancel_button_sprite.getGlobalBounds().contains(mouse_position.x, mouse_position.y))
                        {
                            repair_prompt_open = false;
                        }
                    }
                    else if (market.visible == true)
                    {
                        market.handle_events(event, pc, mouse_position);
                    }
                    else if (s_menu.visible == true)
                    {
                        s_menu.handle_events(event, mouse_position);
                    }
                }
            }

            if (event.type == sf::Event::TextEntered && save_prompt_open == true)
            {
                if (event.text.unicode != '\b' && event.text.unicode != '`' && input.getSize() < 24)
                {
                    input += event.text.unicode;
                    resources.input_text.setString(input);
                    kp++;
                }
            }

            if (event.type == sf::Event::KeyPressed)
            {
                if (save_prompt_open == true)
                {
                    if (event.key.code == sf::Keyboard::Return)
                    {
                        input += "\n";
                        resources.input_text.setString(input);
                        kp = 0;
                    }

                    if (event.key.code == sf::Keyboard::BackSpace)
                    {
                        if (input.getSize() > 0)
                        {
                            input.erase(input.getSize() - 1, 1);
                            resources.input_text.setString(input);
                        }
                    }

                    if (event.key.code == sf::Keyboard::Escape)
                    {
                        save_prompt_open = false;
                    }
                }
                else if (load_prompt_open == true)
                {
                    if (event.key.code == sf::Keyboard::Escape)
                    {
                        load_prompt_open = false;
                    }
                }
                else if (repair_prompt_open == true)
                {
                    if (event.key.code == sf::Keyboard::Escape)
                    {
                        repair_prompt_open = false;
                    }
                }
                else if (market.visible == true)
                {
                    if (event.key.code == sf::Keyboard::Escape)
                    {
                         market.visible = false;
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

        // Draw saved game information
        sf::Sprite bg_sprite = sf::Sprite(resources.gui_background_2_texture);
        bg_sprite.setPosition(10, window.getView().getSize().y * 0.23);
        bg_sprite.setScale(0.24, 1);
        window.draw(bg_sprite);

        sf::String status =
        "CREDITS: " + std::to_string(pc.credits) + "\n" +
        "MISSION: " + std::to_string(pc.mission) + "\n\n" +
        "MECH LOADOUT\n\nWEIGHT: " + std::to_string(pc.player_mech.weight) + "/110" + "\n" +
        "PRIMARY WEAPON: " + pc.player_mech.primary_weapon+ " +" + std::to_string(pc.player_mech.guns_modifier) + "\n" +
        "SECONDARY WEAPON: " + pc.player_mech.secondary_weapon + " +" + std::to_string(pc.player_mech.cannons_modifier) + "\n" +
        "COCKPIT: " + pc.player_mech.cockpit + "\n" +
        "REACTOR: " + pc.player_mech.reactor + "\n" +
        "COOLER: " + pc.player_mech.cooler + " +" + std::to_string(pc.player_mech.cooler_modifier) + "\n" +
        "LEFT ARM: " + pc.player_mech.left_arm + "\n" +
        "RIGHT ARM: " + pc.player_mech.right_arm + "\n" +
        "LEFT LEG: " + pc.player_mech.left_leg + "\n" +
        "RIGHT LEG: " + pc.player_mech.right_leg + "\n\n" +
        "MECH STATUS\n\nRIGHT LEG: " + std::to_string(pc.player_mech.right_leg_integrity) + " / " + std::to_string(pc.player_mech.max_right_leg_integrity) + "\n" +
        "LEFT LEG: " + std::to_string(pc.player_mech.left_leg_integrity) + " / " + std::to_string(pc.player_mech.max_left_leg_integrity) + "\n" +
        "RIGHT ARM: " + std::to_string(pc.player_mech.right_arm_integrity) + " / " + std::to_string(pc.player_mech.max_right_arm_integrity) + "\n" +
        "LEFT ARM: " + std::to_string(pc.player_mech.left_arm_integrity) + " / " + std::to_string(pc.player_mech.max_left_arm_integrity) + "\n" +
        "REACTOR: " + std::to_string(pc.player_mech.reactor_integrity) + " / " + std::to_string(pc.player_mech.max_reactor_integrity) + "\n" +
        "COOLER: " + std::to_string(pc.player_mech.cooler_integrity) + " / " + std::to_string(pc.player_mech.max_cooler_integrity) + "\n" +
        "COCKPIT: " + std::to_string(pc.player_mech.cockpit_integrity) + " / " + std::to_string(pc.player_mech.max_cockpit_integrity);
        resources.mech_status.setString(status);
        resources.mech_status.setPosition(20, window.getView().getSize().y * 0.25);
        window.draw(resources.mech_status);

        if (prompt_displayed() == false && show_notice == false && market.visible == false && s_menu.visible == false)
        {
            // Next Mission
            if (resources.next_mission_button_sprite.getGlobalBounds().contains(mouse_position.x, mouse_position.y))
            {
                resources.next_mission_button_sprite.setTexture(resources.next_mission_button_hover_texture);
            }
            else
            {
                resources.next_mission_button_sprite.setTexture(resources.next_mission_button_texture);
            }
            float bx = (window.getView().getSize().x / 2) - (resources.next_mission_button_texture.getSize().x / 2);
            float by = resources.menu_mech_sprite.getPosition().y - 120;
            sf::Vector2f bv(bx, by);
            resources.next_mission_button_sprite.setPosition(bv);
            window.draw(resources.next_mission_button_sprite);

            // Repair
            if (resources.repair_button_sprite.getGlobalBounds().contains(mouse_position.x, mouse_position.y))
            {
                resources.repair_button_sprite.setTexture(resources.repair_button_hover_texture);
            }
            else
            {
                resources.repair_button_sprite.setTexture(resources.repair_button_texture);
            }
            float b2x = (window.getView().getSize().x / 2) - (resources.repair_button_texture.getSize().x / 2);
            float b2y = resources.menu_mech_sprite.getPosition().y - 70;
            sf::Vector2f b2v(b2x, b2y);
            resources.repair_button_sprite.setPosition(b2v);
            window.draw(resources.repair_button_sprite);

            // Market
            if (resources.market_button_sprite.getGlobalBounds().contains(mouse_position.x, mouse_position.y))
            {
                resources.market_button_sprite.setTexture(resources.market_button_hover_texture);
            }
            else
            {
                resources.market_button_sprite.setTexture(resources.market_button_texture);
            }
            float b3x = (window.getView().getSize().x / 2) - (resources.market_button_texture.getSize().x / 2);
            float b3y = resources.menu_mech_sprite.getPosition().y - 20;
            sf::Vector2f b3v(b3x, b3y);
            resources.market_button_sprite.setPosition(b3v);
            window.draw(resources.market_button_sprite);

            // Save
            if (resources.save_game_button_sprite.getGlobalBounds().contains(mouse_position.x, mouse_position.y))
            {
                resources.save_game_button_sprite.setTexture(resources.save_game_button_hover_texture);
            }
            else
            {
                resources.save_game_button_sprite.setTexture(resources.save_game_button_texture);
            }
            float b4x = (window.getView().getSize().x / 2) - (resources.save_game_button_texture.getSize().x / 2);
            float b4y = resources.menu_mech_sprite.getPosition().y + 30;
            sf::Vector2f b4v(b4x, b4y);
            resources.save_game_button_sprite.setPosition(b4v);
            window.draw(resources.save_game_button_sprite);

            // Load
            if (resources.load_game_button_sprite.getGlobalBounds().contains(mouse_position.x, mouse_position.y))
            {
                resources.load_game_button_sprite.setTexture(resources.load_game_button_hover_texture);
            }
            else
            {
                resources.load_game_button_sprite.setTexture(resources.load_game_button_texture);
            }
            float b5x = (window.getView().getSize().x / 2) - (resources.load_game_button_texture.getSize().x / 2);
            float b5y = resources.menu_mech_sprite.getPosition().y + 80;
            sf::Vector2f b5v(b5x, b5y);
            resources.load_game_button_sprite.setPosition(b5v);
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
            float b6x = (window.getView().getSize().x / 2) - (resources.options_button_texture.getSize().x / 2);
            float b6y = resources.menu_mech_sprite.getPosition().y + 130;
            sf::Vector2f b6v(b6x, b6y);
            resources.options_button_sprite.setPosition(b6v);
            window.draw(resources.options_button_sprite);

            // Main Menu
            if (resources.main_menu_button_sprite.getGlobalBounds().contains(mouse_position.x, mouse_position.y))
            {
                resources.main_menu_button_sprite.setTexture(resources.main_menu_button_hover_texture);
            }
            else
            {
                resources.main_menu_button_sprite.setTexture(resources.main_menu_button_texture);
            }
            float b7x = (window.getView().getSize().x / 2) - (resources.main_menu_button_texture.getSize().x / 2);
            float b7y = resources.menu_mech_sprite.getPosition().y + 180;
            sf::Vector2f b7v(b7x, b7y);
            resources.main_menu_button_sprite.setPosition(b7v);
            window.draw(resources.main_menu_button_sprite);
        }
        else if (save_prompt_open == true)
        {
            draw_save_menu(window);
        }
        else if (load_prompt_open == true)
        {
            draw_load_menu(window);
        }
        else if (repair_prompt_open == true)
        {
            draw_repair_menu(window, pc);
        }
        else if (prompt_displayed() == false)
        {
            if (show_notice == true)
            {
                display_notice(window, notice, frame_time);
            }
            else if (market.visible == true)
            {
                if (market.show_notice == true)
                {
                    display_notice(window, market.notice, frame_time);
                }
                else
                {
                    market.draw_menu(window, pc, mouse_position);
                }
            }
            else if (s_menu.visible == true)
            {
                s_menu.draw_menu(window, mouse_position, frame_time);
            }
        }

        window.display();
        return true;
    }
    else
    {
        return false;
    }
}
