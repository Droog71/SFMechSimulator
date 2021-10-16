#include <market_menu.h>
#include <settings.h>

// Constructor
market_menu::market_menu()
{
    visible = false;
    item_worth.resize(7);
    sell_buttons.resize(7);
    sell_button_labels.resize(7);
    sell_categories = {"GUNS", "CANNONS", "COOLER", "REACTOR", "COCKPIT", "ARMS", "LEGS"};
}

// Loads resources from disk
void market_menu::init(std::string cwd)
{
    if (!market_font.loadFromFile(cwd + "/assets/Exoplanetaria-gxxJ5.ttf"))
    {
        std::cout << "Failed to load font.";
        std::cout << "\n";
    }

    if (!gui_background_texture.loadFromFile(cwd + "/assets/textures/gui_background_2.png"))
    {
        std::cout << "Failed to load textures.";
    }

    if (!purchase_sound_buffer.loadFromFile(cwd + "/assets/sounds/purchase.ogg"))
    {
        std::cout << "Error loading sound file purchase.ogg";
        std::cout << "\n";
    }

    purchase_sound.setBuffer(purchase_sound_buffer);
}

// Purchases an item from the market
void market_menu::purchase_item(player_controller &pc, item item_bought)
{
    if (pc.credits >= item_bought.price && pc.player_mech.weight <= 100)
    {
        purchase_sound.setVolume(100 * audio_volume);
        purchase_sound.play();
        pc.credits -= item_bought.price;
        pc.player_mech.weight += 10;

        if (item_bought.type == "guns")
        {
            pc.player_mech.primary_weapon = item_bought.name;
            pc.player_mech.guns_modifier = item_bought.modifier;
        }
        else if (item_bought.type == "cannons")
        {
            pc.player_mech.secondary_weapon = item_bought.name;
            pc.player_mech.cannons_modifier = item_bought.modifier;
        }
        else if (item_bought.type == "cooler")
        {
            pc.player_mech.cooler = item_bought.name;
            pc.player_mech.cooler_integrity = item_bought.modifier;
            pc.player_mech.max_cooler_integrity = item_bought.modifier;
            pc.player_mech.cooler_modifier = item_bought.secondary_modifier;
        }
        else if (item_bought.type == "reactor")
        {
            pc.player_mech.reactor = item_bought.name;
            pc.player_mech.reactor_integrity = item_bought.modifier;
            pc.player_mech.max_reactor_integrity = item_bought.modifier;
        }
        else if (item_bought.type == "cockpit")
        {
            pc.player_mech.cockpit = item_bought.name;
            pc.player_mech.cockpit_integrity = item_bought.modifier;
            pc.player_mech.max_cockpit_integrity = item_bought.modifier;
        }
        else if (item_bought.type == "arms")
        {
            pc.player_mech.left_arm = item_bought.name;
            pc.player_mech.left_arm_integrity = item_bought.modifier;
            pc.player_mech.max_left_arm_integrity = item_bought.modifier;

            pc.player_mech.right_arm = item_bought.name;
            pc.player_mech.right_arm_integrity = item_bought.modifier;
            pc.player_mech.max_right_arm_integrity = item_bought.modifier;
        }
        else if (item_bought.type == "legs")
        {
            pc.player_mech.left_leg = item_bought.name;
            pc.player_mech.left_leg_integrity = item_bought.modifier;
            pc.player_mech.max_left_leg_integrity = item_bought.modifier;

            pc.player_mech.right_leg = item_bought.name;
            pc.player_mech.right_leg_integrity = item_bought.modifier;
            pc.player_mech.max_right_leg_integrity = item_bought.modifier;
        }
    }
}

// Sells an item installed on the player's mech
void market_menu::sell_item(player_controller &pc, std::string category)
{
    if (category == "GUNS")
    {
        if (pc.player_mech.primary_weapon != "Standard Pulse Laser")
        {
            pc.credits += (item_worth[0]);
            pc.player_mech.weight -= 10;
            pc.player_mech.primary_weapon = "Standard Pulse Laser";
            pc.player_mech.guns_modifier = 0;
            purchase_sound.setVolume(100 * audio_volume);
            purchase_sound.play();
        }
        else
        {
            notice = "CANNOT SELL THIS ITEM";
            show_notice = true;
        }
    }
    else if (category == "CANNONS")
    {
        if (pc.player_mech.secondary_weapon != "Standard Autocannon")
        {
            pc.credits += (item_worth[1]);
            pc.player_mech.weight -= 10;
            pc.player_mech.secondary_weapon = "Standard Autocannon";
            pc.player_mech.cannons_modifier = 0;
            purchase_sound.setVolume(100 * audio_volume);
            purchase_sound.play();
        }
        else
        {
            notice = "CANNOT SELL THIS ITEM";
            show_notice = true;
        }
    }
    else if (category == "COOLER")
    {
        if (pc.player_mech.cooler != "Standard Cooler")
        {
            pc.credits += (item_worth[2]);
            pc.player_mech.weight -= 10;
            pc.player_mech.cooler = "Standard Cooler";
            pc.player_mech.cooler_modifier = 0;
            pc.player_mech.cooler_integrity = 1000;
            pc.player_mech.max_cooler_integrity = 1000;
            purchase_sound.setVolume(100 * audio_volume);
            purchase_sound.play();
        }
        else
        {
            notice = "CANNOT SELL THIS ITEM";
            show_notice = true;
        }
    }
    else if (category == "REACTOR")
    {
        if (pc.player_mech.reactor != "Standard Reactor")
        {
            pc.credits += (item_worth[3]);
            pc.player_mech.weight -= 10;
            pc.player_mech.reactor = "Standard Reactor";
            pc.player_mech.reactor_integrity = 1000;
            pc.player_mech.max_reactor_integrity = 1000;
            purchase_sound.setVolume(100 * audio_volume);
            purchase_sound.play();
        }
        else
        {
            notice = "CANNOT SELL THIS ITEM";
            show_notice = true;
        }
    }
    else if (category == "COCKPIT")
    {
        if (pc.player_mech.cockpit != "Standard Cockpit")
        {
            pc.credits += (item_worth[4]);
            pc.player_mech.weight -= 10;
            pc.player_mech.cockpit = "Standard Cockpit";
            pc.player_mech.cockpit_integrity = 1000;
            pc.player_mech.max_cockpit_integrity = 1000;
            purchase_sound.setVolume(100 * audio_volume);
            purchase_sound.play();
        }
        else
        {
            notice = "CANNOT SELL THIS ITEM";
            show_notice = true;
        }
    }
    else if (category == "ARMS")
    {
        if (pc.player_mech.left_arm != "Standard Left Arm")
        {
            pc.credits += (item_worth[5]);
            pc.player_mech.weight -= 10;

            pc.player_mech.left_arm = "Standard Left Arm";
            pc.player_mech.left_arm_integrity = 1000;
            pc.player_mech.max_left_arm_integrity = 1000;

            pc.player_mech.right_arm = "Standard Right Arm";
            pc.player_mech.right_arm_integrity = 1000;
            pc.player_mech.max_right_arm_integrity = 1000;

            purchase_sound.setVolume(100 * audio_volume);
            purchase_sound.play();
        }
        else
        {
            notice = "CANNOT SELL THIS ITEM";
            show_notice = true;
        }
    }
    else if (category == "LEGS")
    {
        if (pc.player_mech.left_leg != "Standard Left Leg")
        {
            pc.credits += (item_worth[6]);
            pc.player_mech.weight -= 10;

            pc.player_mech.left_leg = "Standard Left Leg";
            pc.player_mech.left_leg_integrity = 1000;
            pc.player_mech.max_left_leg_integrity = 1000;

            pc.player_mech.right_leg = "Standard Right Leg";
            pc.player_mech.right_leg_integrity = 1000;
            pc.player_mech.max_right_leg_integrity = 1000;

            purchase_sound.setVolume(100 * audio_volume);
            purchase_sound.play();
        }
        else
        {
            notice = "CANNOT SELL THIS ITEM";
            show_notice = true;
        }
    }
}

// Generates items for sale
void market_menu::generate_items()
{
    int gun_amount = 4;
    guns.resize(gun_amount);
    gun_buttons.resize(gun_amount);
    gun_button_labels.resize(gun_amount);
    gun_descriptions.resize(gun_amount);
    for (int i = 0; i < gun_amount; i++)
    {
        guns[i].type = "guns";

        int level = rand() % 100;

        if (level > 90)
        {
            guns[i].name = "L3 Pulse Laser";
            guns[i].level = 3;
            guns[i].modifier = 6 + ( rand() % ( 9 - 6 + 1 ) );
            guns[i].price = guns[i].modifier * 10000;
        }
        else if (level <= 90 && level > 60)
        {
            guns[i].name = "L2 Pulse Laser";
            guns[i].level = 2;
            guns[i].modifier = 4 + ( rand() % ( 6 - 4 + 1 ) );
            guns[i].price = guns[i].modifier * 10000;
        }
        else
        {
            guns[i].name = "L1 Pulse Laser";
            guns[i].level = 1;
            guns[i].modifier = 1 + ( rand() % ( 3 - 1 + 1 ) );
            guns[i].price = guns[i].modifier * 10000;
        }
    }

    int cannon_amount = 4;
    cannons.resize(cannon_amount);
    cannon_buttons.resize(cannon_amount);
    cannon_button_labels.resize(cannon_amount);
    cannon_descriptions.resize(cannon_amount);
    for (int i = 0; i < cannon_amount; i++)
    {
        cannons[i].type = "cannons";

        int level = rand() % 100;
        if (level > 90)
        {
            cannons[i].name = "L3 Autocannon";
            cannons[i].level = 3;
            cannons[i].modifier = 7 + ( rand() % ( 9 - 7 + 1 ) );
            cannons[i].price = cannons[i].modifier * 10000;
        }
        else if (level <= 90 && level > 60)
        {
            cannons[i].name = "L2 Autocannon";
            cannons[i].level = 2;
            cannons[i].modifier = 4 + ( rand() % ( 6 - 4 + 1 ) );
            cannons[i].price = cannons[i].modifier * 10000;
        }
        else
        {
            cannons[i].name = "L1 Autocannon";
            cannons[i].level = 1;
            cannons[i].modifier = 1 + ( rand() % ( 3 - 1 + 1 ) );
            cannons[i].price = cannons[i].modifier * 10000;
        }
    }

    int cooler_amount = 4;
    coolers.resize(cooler_amount);
    cooler_buttons.resize(cooler_amount);
    cooler_button_labels.resize(cooler_amount);
    cooler_descriptions.resize(cooler_amount);
    for (int i = 0; i < cooler_amount; i++)
    {
        coolers[i].type = "cooler";

        int level = rand() % 100;
        if (level > 90)
        {
            coolers[i].name = "L3 Cooler";
            coolers[i].level = 3;
            coolers[i].modifier = 3000 + ( rand() % ( 3500 - 3000 + 1 ) );
            coolers[i].secondary_modifier = 7 + ( rand() % ( 9 - 7 + 1 ) );
            coolers[i].price = coolers[i].modifier * 15 + coolers[i].secondary_modifier * 5000;
        }
        else if (level <= 90 && level > 60)
        {
            coolers[i].name = "L2 Cooler";
            coolers[i].level = 2;
            coolers[i].modifier = 2000 + ( rand() % ( 2500 - 2000 + 1 ) );
            coolers[i].secondary_modifier = 4 + ( rand() % ( 6 - 4 + 1 ) );
            coolers[i].price = coolers[i].modifier * 10 + coolers[i].secondary_modifier * 5000;
        }
        else
        {
            coolers[i].name = "L1 Cooler";
            coolers[i].level = 1;
            coolers[i].modifier = 1000 + ( rand() % ( 1500 - 1000 + 1 ) );
            coolers[i].secondary_modifier = 1 + ( rand() % ( 3 - 1 + 1 ) );
            coolers[i].price = coolers[i].modifier * 5 + coolers[i].secondary_modifier * 5000;
        }
    }

    int reactor_amount = 4;
    reactors.resize(reactor_amount);
    reactor_buttons.resize(reactor_amount);
    reactor_button_labels.resize(reactor_amount);
    reactor_descriptions.resize(reactor_amount);
    for (int i = 0; i < reactor_amount; i++)
    {
        reactors[i].type = "reactor";

        int level = rand() % 100;
        if (level > 90)
        {
            reactors[i].name = "L3 Reactor";
            reactors[i].level = 3;
            reactors[i].modifier = 3000 + ( rand() % ( 3500 - 3000 + 1 ) );
            reactors[i].price = reactors[i].modifier * 15;
        }
        else if (level <= 90 && level > 60)
        {
            reactors[i].name = "L2 Reactor";
            reactors[i].level = 2;
            reactors[i].modifier = 2000 + ( rand() % ( 2500 - 2000 + 1 ) );
            reactors[i].price = reactors[i].modifier * 10;
        }
        else
        {
            reactors[i].name = "L1 Reactor";
            reactors[i].level = 1;
            reactors[i].modifier = 1000 + ( rand() % ( 1500 - 1000 + 1 ) );
            reactors[i].price = reactors[i].modifier *5;
        }
    }

    int cockpit_amount = 4;
    cockpits.resize(cockpit_amount);
    cockpit_buttons.resize(cockpit_amount);
    cockpit_button_labels.resize(cockpit_amount);
    cockpit_descriptions.resize(cockpit_amount);
    for (int i = 0; i < cockpit_amount; i++)
    {
        cockpits[i].type = "cockpit";

        int level = rand() % 100;
        if (level > 90)
        {
            cockpits[i].name = "L3 Cockpit";
            cockpits[i].level = 3;
            cockpits[i].modifier = 4000 + ( rand() % ( 3500 - 3000 + 1 ) );
            cockpits[i].price = cockpits[i].modifier * 15;
        }
        else if (level <= 90 && level > 60)
        {
            cockpits[i].name = "L2 Cockpit";
            cockpits[i].level = 2;
            cockpits[i].modifier = 2000 + ( rand() % ( 2500 - 2000 + 1 ) );
            cockpits[i].price = cockpits[i].modifier *10;
        }
        else
        {
            cockpits[i].name = "L1 Cockpit";
            cockpits[i].level = 1;
            cockpits[i].modifier = 1000 + ( rand() % ( 1500 - 1000 + 1 ) );
            cockpits[i].price = cockpits[i].modifier * 5;
        }
    }

    int arm_amount = 4;
    arms.resize(arm_amount);
    arm_buttons.resize(arm_amount);
    arm_button_labels.resize(arm_amount);
    arm_descriptions.resize(arm_amount);
    for (int i = 0; i < arm_amount; i++)
    {
        arms[i].type = "arms";

        int level = rand() % 100;
        if (level > 90)
        {
            arms[i].name = "L3 Arms";
            arms[i].level = 3;
            arms[i].modifier = 3000 + ( rand() % ( 3500 - 3000 + 1 ) );
            arms[i].price = arms[i].modifier * 15;
        }
        else if (level <= 90 && level > 60)
        {
            arms[i].name = "L2 Arms";
            arms[i].level = 2;
            arms[i].modifier = 2000 + ( rand() % ( 2500 - 2000 + 1 ) );
            arms[i].price = arms[i].modifier * 10;
        }
        else
        {
            arms[i].name = "L1 Arms";
            arms[i].level = 1;
            arms[i].modifier = 1000 + ( rand() % ( 1500 - 1000 + 1 ) );
            arms[i].price = arms[i].modifier * 5;
        }
    }

    int leg_amount = 4;
    legs.resize(leg_amount);
    leg_buttons.resize(leg_amount);
    leg_button_labels.resize(leg_amount);
    leg_descriptions.resize(leg_amount);
    for (int i = 0; i < leg_amount; i++)
    {
        legs[i].type = "legs";

        int level = rand() % 100;
        if (level > 90)
        {
            legs[i].name = "L3 Legs";
            legs[i].level = 3;
            legs[i].modifier = 3000 + ( rand() % ( 3500 - 3000 + 1 ) );
            legs[i].price = legs[i].modifier * 15;
        }
        else if (level <= 90 && level > 60)
        {
            legs[i].name = "L2 Legs";
            legs[i].level = 2;
            legs[i].modifier = 2000 + ( rand() % ( 2500 - 2000 + 1 ) );
            legs[i].price = legs[i].modifier * 10;
        }
        else
        {
            legs[i].name = "L1 Legs";
            legs[i].level = 1;
            legs[i].modifier = 1000 + ( rand() % ( 1500 - 1000 + 1 ) );
            legs[i].price = legs[i].modifier * 5;
        }
    }
}

// Mouse click events
void market_menu::handle_events(sf::Event event, player_controller &pc, sf::Vector2i mouse_position)
{
    if (event.type == sf::Event::MouseButtonPressed)
    {
        if(event.mouseButton.button == sf::Mouse::Left)
        {
            for (unsigned int i = 0; i < gun_buttons.size(); i++)
            {
                if (gun_buttons[i].getBounds().contains(mouse_position.x, mouse_position.y))
                {
                    purchase_item(pc, guns[i]);
                }
            }

            for (unsigned int i = 0; i < cannon_buttons.size(); i++)
            {
                if (cannon_buttons[i].getBounds().contains(mouse_position.x, mouse_position.y))
                {
                    purchase_item(pc, cannons[i]);
                }
            }

            for (unsigned int i = 0; i < cooler_buttons.size(); i++)
            {
                if (cooler_buttons[i].getBounds().contains(mouse_position.x, mouse_position.y))
                {
                    purchase_item(pc, coolers[i]);
                }
            }

            for (unsigned int i = 0; i < reactor_buttons.size(); i++)
            {
                if (reactor_buttons[i].getBounds().contains(mouse_position.x, mouse_position.y))
                {
                    purchase_item(pc, reactors[i]);
                }
            }

            for (unsigned int i = 0; i < cockpit_buttons.size(); i++)
            {
                if (cockpit_buttons[i].getBounds().contains(mouse_position.x, mouse_position.y))
                {
                    purchase_item(pc, cockpits[i]);
                }
            }

            for (unsigned int i = 0; i < arm_buttons.size(); i++)
            {
                if (arm_buttons[i].getBounds().contains(mouse_position.x, mouse_position.y))
                {
                    purchase_item(pc, arms[i]);
                }
            }

            for (unsigned int i = 0; i < leg_buttons.size(); i++)
            {
                if (leg_buttons[i].getBounds().contains(mouse_position.x, mouse_position.y))
                {
                    purchase_item(pc, legs[i]);
                }
            }

            for (unsigned int i = 0; i < sell_buttons.size(); i++)
            {
                if (sell_buttons[i].getBounds().contains(mouse_position.x, mouse_position.y))
                {
                    sell_item(pc, sell_categories[i]);
                }
            }

            if (exit_button.getBounds().contains(mouse_position.x, mouse_position.y))
            {
                visible = false;
            }
        }
    }
}

// Draws the market menu
void market_menu::draw_menu(sf::RenderWindow &window, player_controller &pc, sf::Vector2i mouse_position)
{
    sf::Sprite bg_sprite = sf::Sprite(gui_background_texture);
    bg_sprite.setPosition(window.getView().getSize().x / 2 - 210, 20);
    bg_sprite.setScale(0.54, 2);
    window.draw(bg_sprite);

    for (unsigned int i = 0; i < gun_buttons.size(); i++)
    {
        float x = window.getView().getSize().x / 2 + 100;

        gun_buttons[i] = sf::VertexArray(sf::Quads, 4);
        gun_buttons[i][0].position = sf::Vector2f(x + 10, (80 + i * 35) - 4);
        gun_buttons[i][1].position = sf::Vector2f(x + 10, (80 + i * 35) + 24);
        gun_buttons[i][2].position = sf::Vector2f(x + 80, (80 + i * 35) + 24);
        gun_buttons[i][3].position = sf::Vector2f(x + 80, (80 + i * 35) - 4);

        sf::VertexArray gun_button_shadow = sf::VertexArray(sf::Quads, 4);
        gun_button_shadow[0].position = sf::Vector2f(x + 10, (80 + i * 35) - 4);
        gun_button_shadow[1].position = sf::Vector2f(x + 10, (80 + i * 35) + 27);
        gun_button_shadow[2].position = sf::Vector2f(x + 83, (80 + i * 35) + 27);
        gun_button_shadow[3].position = sf::Vector2f(x + 83, (80 + i * 35) - 4);

        gun_button_shadow[0].color = sf::Color::Black;
        gun_button_shadow[1].color = sf::Color::Black;
        gun_button_shadow[2].color = sf::Color::Black;
        gun_button_shadow[3].color = sf::Color::Black;

        if (gun_buttons[i].getBounds().contains(mouse_position.x, mouse_position.y))
        {
            gun_buttons[i][0].color = sf::Color(53, 53, 53, 255);
            gun_buttons[i][1].color = sf::Color(53, 53, 53, 255);
            gun_buttons[i][2].color = sf::Color(53, 53, 53, 255);
            gun_buttons[i][3].color = sf::Color(53, 53, 53, 255);
        }
        else
        {
            gun_buttons[i][0].color = sf::Color(35, 35, 35, 255);
            gun_buttons[i][1].color = sf::Color(35, 35, 35, 255);
            gun_buttons[i][2].color = sf::Color(35, 35, 35, 255);
            gun_buttons[i][3].color = sf::Color(35, 35, 35, 255);
        }

        std::string desc = guns[i].name + ": +" + std::to_string(guns[i].modifier) + " damage, $" + std::to_string(guns[i].price);
        gun_descriptions[i].setFont(market_font);
        gun_descriptions[i].setCharacterSize(14);
        if (guns[i].level == 3)
        {
            gun_descriptions[i].setFillColor(sf::Color::Green);
        }
        else if (guns[i].level == 2)
        {
            gun_descriptions[i].setFillColor(sf::Color::Yellow);
        }
        else if (guns[i].level == 1)
        {
            gun_descriptions[i].setFillColor(sf::Color::Red);
        }
        gun_descriptions[i].setPosition(x - 280, 80 + (i * 35));
        gun_descriptions[i].setString(desc);

        gun_button_labels[i].setFont(market_font);
        gun_button_labels[i].setCharacterSize(16);
        gun_button_labels[i].setFillColor(sf::Color::Black);
        gun_button_labels[i].setPosition(x + 28, 80 + (i * 35));
        gun_button_labels[i].setString("BUY");

        window.draw(gun_descriptions[i]);
        window.draw(gun_button_shadow);
        window.draw(gun_buttons[i]);
        window.draw(gun_button_labels[i]);
    }

    for (unsigned int i = 0; i < cannon_buttons.size(); i++)
    {
        float x = window.getView().getSize().x / 2 + 100;

        cannon_buttons[i] = sf::VertexArray(sf::Quads, 4);
        cannon_buttons[i][0].position = sf::Vector2f(x + 10, (220 + i * 35) - 4);
        cannon_buttons[i][1].position = sf::Vector2f(x + 10, (220 + i * 35) + 24);
        cannon_buttons[i][2].position = sf::Vector2f(x + 80, (220 + i * 35) + 24);
        cannon_buttons[i][3].position = sf::Vector2f(x + 80, (220 + i * 35) - 4);

        sf::VertexArray cannon_button_shadow = sf::VertexArray(sf::Quads, 4);
        cannon_button_shadow[0].position = sf::Vector2f(x + 10, (220 + i * 35) - 4);
        cannon_button_shadow[1].position = sf::Vector2f(x + 10, (220 + i * 35) + 27);
        cannon_button_shadow[2].position = sf::Vector2f(x + 83, (220 + i * 35) + 27);
        cannon_button_shadow[3].position = sf::Vector2f(x + 83, (220 + i * 35) - 4);

        cannon_button_shadow[0].color = sf::Color::Black;
        cannon_button_shadow[1].color = sf::Color::Black;
        cannon_button_shadow[2].color = sf::Color::Black;
        cannon_button_shadow[3].color = sf::Color::Black;

        if (cannon_buttons[i].getBounds().contains(mouse_position.x, mouse_position.y))
        {
            cannon_buttons[i][0].color = sf::Color(53, 53, 53, 255);
            cannon_buttons[i][1].color = sf::Color(53, 53, 53, 255);
            cannon_buttons[i][2].color = sf::Color(53, 53, 53, 255);
            cannon_buttons[i][3].color = sf::Color(53, 53, 53, 255);
        }
        else
        {
            cannon_buttons[i][0].color = sf::Color(35, 35, 35, 255);
            cannon_buttons[i][1].color = sf::Color(35, 35, 35, 255);
            cannon_buttons[i][2].color = sf::Color(35, 35, 35, 255);
            cannon_buttons[i][3].color = sf::Color(35, 35, 35, 255);
        }

        std::string desc = cannons[i].name + ": +" + std::to_string(cannons[i].modifier) + " damage, $" + std::to_string(cannons[i].price);
        cannon_descriptions[i].setFont(market_font);
        cannon_descriptions[i].setCharacterSize(14);
        if (cannons[i].level == 3)
        {
            cannon_descriptions[i].setFillColor(sf::Color::Green);
        }
        else if (cannons[i].level == 2)
        {
            cannon_descriptions[i].setFillColor(sf::Color::Yellow);
        }
        else if (cannons[i].level == 1)
        {
            cannon_descriptions[i].setFillColor(sf::Color::Red);
        }
        cannon_descriptions[i].setPosition(x - 280, 220 + (i * 35));
        cannon_descriptions[i].setString(desc);

        cannon_button_labels[i].setFont(market_font);
        cannon_button_labels[i].setCharacterSize(16);
        cannon_button_labels[i].setFillColor(sf::Color::Black);
        cannon_button_labels[i].setPosition(x + 28, 220 + (i * 35));
        cannon_button_labels[i].setString("BUY");

        window.draw(cannon_descriptions[i]);
        window.draw(cannon_button_shadow);
        window.draw(cannon_buttons[i]);
        window.draw(cannon_button_labels[i]);
    }

    for (unsigned int i = 0; i < cooler_buttons.size(); i++)
    {
        float x = window.getView().getSize().x / 2 + 100;

        cooler_buttons[i] = sf::VertexArray(sf::Quads, 4);
        cooler_buttons[i][0].position = sf::Vector2f(x + 10, (360 + i * 35) - 4);
        cooler_buttons[i][1].position = sf::Vector2f(x + 10, (360 + i * 35) + 24);
        cooler_buttons[i][2].position = sf::Vector2f(x + 80, (360 + i * 35) + 24);
        cooler_buttons[i][3].position = sf::Vector2f(x + 80, (360 + i * 35) - 4);

        sf::VertexArray cooler_button_shadow = sf::VertexArray(sf::Quads, 4);
        cooler_button_shadow[0].position = sf::Vector2f(x + 10, (360 + i * 35) - 4);
        cooler_button_shadow[1].position = sf::Vector2f(x + 10, (360 + i * 35) + 27);
        cooler_button_shadow[2].position = sf::Vector2f(x + 83, (360 + i * 35) + 27);
        cooler_button_shadow[3].position = sf::Vector2f(x + 83, (360 + i * 35) - 4);

        cooler_button_shadow[0].color = sf::Color::Black;
        cooler_button_shadow[1].color = sf::Color::Black;
        cooler_button_shadow[2].color = sf::Color::Black;
        cooler_button_shadow[3].color = sf::Color::Black;

        if (cooler_buttons[i].getBounds().contains(mouse_position.x, mouse_position.y))
        {
            cooler_buttons[i][0].color = sf::Color(53, 53, 53, 255);
            cooler_buttons[i][1].color = sf::Color(53, 53, 53, 255);
            cooler_buttons[i][2].color = sf::Color(53, 53, 53, 255);
            cooler_buttons[i][3].color = sf::Color(53, 53, 53, 255);
        }
        else
        {
            cooler_buttons[i][0].color = sf::Color(35, 35, 35, 255);
            cooler_buttons[i][1].color = sf::Color(35, 35, 35, 255);
            cooler_buttons[i][2].color = sf::Color(35, 35, 35, 255);
            cooler_buttons[i][3].color = sf::Color(35, 35, 35, 255);
        }

        std::string desc = coolers[i].name + ": " + std::to_string(coolers[i].modifier) + " armor, +" + std::to_string(coolers[i].secondary_modifier) + " kbtu, $"+ std::to_string(coolers[i].price);
        cooler_descriptions[i].setFont(market_font);
        cooler_descriptions[i].setCharacterSize(14);
        if (coolers[i].level == 3)
        {
            cooler_descriptions[i].setFillColor(sf::Color::Green);
        }
        else if (coolers[i].level == 2)
        {
            cooler_descriptions[i].setFillColor(sf::Color::Yellow);
        }
        else if (coolers[i].level == 1)
        {
            cooler_descriptions[i].setFillColor(sf::Color::Red);
        }
        cooler_descriptions[i].setPosition(x - 280, 360 + (i * 35));
        cooler_descriptions[i].setString(desc);

        cooler_button_labels[i].setFont(market_font);
        cooler_button_labels[i].setCharacterSize(16);
        cooler_button_labels[i].setFillColor(sf::Color::Black);
        cooler_button_labels[i].setPosition(x + 28, 360 + (i * 35));
        cooler_button_labels[i].setString("BUY");

        window.draw(cooler_descriptions[i]);
        window.draw(cooler_button_shadow);
        window.draw(cooler_buttons[i]);
        window.draw(cooler_button_labels[i]);
    }

    for (unsigned int i = 0; i < reactor_buttons.size(); i++)
    {
        float x = window.getView().getSize().x / 2 + 100;

        reactor_buttons[i] = sf::VertexArray(sf::Quads, 4);
        reactor_buttons[i][0].position = sf::Vector2f(x + 10, (500 + i * 35) - 4);
        reactor_buttons[i][1].position = sf::Vector2f(x + 10, (500 + i * 35) + 24);
        reactor_buttons[i][2].position = sf::Vector2f(x + 80, (500 + i * 35) + 24);
        reactor_buttons[i][3].position = sf::Vector2f(x + 80, (500 + i * 35) - 4);

        sf::VertexArray reactor_button_shadow = sf::VertexArray(sf::Quads, 4);
        reactor_button_shadow[0].position = sf::Vector2f(x + 10, (500 + i * 35) - 4);
        reactor_button_shadow[1].position = sf::Vector2f(x + 10, (500 + i * 35) + 27);
        reactor_button_shadow[2].position = sf::Vector2f(x + 83, (500 + i * 35) + 27);
        reactor_button_shadow[3].position = sf::Vector2f(x + 83, (500 + i * 35) - 4);

        reactor_button_shadow[0].color = sf::Color::Black;
        reactor_button_shadow[1].color = sf::Color::Black;
        reactor_button_shadow[2].color = sf::Color::Black;
        reactor_button_shadow[3].color = sf::Color::Black;

        if (reactor_buttons[i].getBounds().contains(mouse_position.x, mouse_position.y))
        {
            reactor_buttons[i][0].color = sf::Color(53, 53, 53, 255);
            reactor_buttons[i][1].color = sf::Color(53, 53, 53, 255);
            reactor_buttons[i][2].color = sf::Color(53, 53, 53, 255);
            reactor_buttons[i][3].color = sf::Color(53, 53, 53, 255);
        }
        else
        {
            reactor_buttons[i][0].color = sf::Color(35, 35, 35, 255);
            reactor_buttons[i][1].color = sf::Color(35, 35, 35, 255);
            reactor_buttons[i][2].color = sf::Color(35, 35, 35, 255);
            reactor_buttons[i][3].color = sf::Color(35, 35, 35, 255);
        }

        std::string desc = reactors[i].name + ": " + std::to_string(reactors[i].modifier) + " armor, $" + std::to_string(reactors[i].price);
        reactor_descriptions[i].setFont(market_font);
        reactor_descriptions[i].setCharacterSize(14);
        if (reactors[i].level == 3)
        {
            reactor_descriptions[i].setFillColor(sf::Color::Green);
        }
        else if (reactors[i].level == 2)
        {
            reactor_descriptions[i].setFillColor(sf::Color::Yellow);
        }
        else if (reactors[i].level == 1)
        {
            reactor_descriptions[i].setFillColor(sf::Color::Red);
        }
        reactor_descriptions[i].setPosition(x - 280, 502 + (i * 35 - 2));
        reactor_descriptions[i].setString(desc);

        reactor_button_labels[i].setFont(market_font);
        reactor_button_labels[i].setCharacterSize(16);
        reactor_button_labels[i].setFillColor(sf::Color::Black);
        reactor_button_labels[i].setPosition(x + 28, 502 + (i * 35 - 2));
        reactor_button_labels[i].setString("BUY");

        window.draw(reactor_descriptions[i]);
        window.draw(reactor_button_shadow);
        window.draw(reactor_buttons[i]);
        window.draw(reactor_button_labels[i]);
    }

    for (unsigned int i = 0; i < cockpit_buttons.size(); i++)
    {
        float x = window.getView().getSize().x / 2 + 500;

        cockpit_buttons[i] = sf::VertexArray(sf::Quads, 4);
        cockpit_buttons[i][0].position = sf::Vector2f(x, (80 + i * 35) - 4);
        cockpit_buttons[i][1].position = sf::Vector2f(x, (80 + i * 35) + 24);
        cockpit_buttons[i][2].position = sf::Vector2f(x + 70, (80 + i * 35) + 24);
        cockpit_buttons[i][3].position = sf::Vector2f(x + 70, (80 + i * 35) - 4);

        sf::VertexArray cockpit_button_shadow = sf::VertexArray(sf::Quads, 4);
        cockpit_button_shadow[0].position = sf::Vector2f(x, (80 + i * 35) - 4);
        cockpit_button_shadow[1].position = sf::Vector2f(x, (80 + i * 35) + 27);
        cockpit_button_shadow[2].position = sf::Vector2f(x + 73, (80 + i * 35) + 27);
        cockpit_button_shadow[3].position = sf::Vector2f(x + 73, (80 + i * 35) - 4);

        cockpit_button_shadow[0].color = sf::Color::Black;
        cockpit_button_shadow[1].color = sf::Color::Black;
        cockpit_button_shadow[2].color = sf::Color::Black;
        cockpit_button_shadow[3].color = sf::Color::Black;

        if (cockpit_buttons[i].getBounds().contains(mouse_position.x, mouse_position.y))
        {
            cockpit_buttons[i][0].color = sf::Color(53, 53, 53, 255);
            cockpit_buttons[i][1].color = sf::Color(53, 53, 53, 255);
            cockpit_buttons[i][2].color = sf::Color(53, 53, 53, 255);
            cockpit_buttons[i][3].color = sf::Color(53, 53, 53, 255);
        }
        else
        {
            cockpit_buttons[i][0].color = sf::Color(35, 35, 35, 255);
            cockpit_buttons[i][1].color = sf::Color(35, 35, 35, 255);
            cockpit_buttons[i][2].color = sf::Color(35, 35, 35, 255);
            cockpit_buttons[i][3].color = sf::Color(35, 35, 35, 255);
        }

        std::string desc = cockpits[i].name + ": " + std::to_string(cockpits[i].modifier) + " armor, $" + std::to_string(cockpits[i].price);
        cockpit_descriptions[i].setFont(market_font);
        cockpit_descriptions[i].setCharacterSize(14);
        if (cockpits[i].level == 3)
        {
            cockpit_descriptions[i].setFillColor(sf::Color::Green);
        }
        else if (cockpits[i].level == 2)
        {
            cockpit_descriptions[i].setFillColor(sf::Color::Yellow);
        }
        else if (cockpits[i].level == 1)
        {
            cockpit_descriptions[i].setFillColor(sf::Color::Red);
        }
        cockpit_descriptions[i].setPosition(x - 230, 82 + (i * 35 - 2));
        cockpit_descriptions[i].setString(desc);

        cockpit_button_labels[i].setFont(market_font);
        cockpit_button_labels[i].setCharacterSize(16);
        cockpit_button_labels[i].setFillColor(sf::Color::Black);
        cockpit_button_labels[i].setPosition(x + 18, 82 + (i * 35 - 2));
        cockpit_button_labels[i].setString("BUY");

        window.draw(cockpit_descriptions[i]);
        window.draw(cockpit_button_shadow);
        window.draw(cockpit_buttons[i]);
        window.draw(cockpit_button_labels[i]);
    }

    for (unsigned int i = 0; i < arm_buttons.size(); i++)
    {
        float x = window.getView().getSize().x / 2 + 500;

        arm_buttons[i] = sf::VertexArray(sf::Quads, 4);
        arm_buttons[i][0].position = sf::Vector2f(x, (220 + i * 35) - 4);
        arm_buttons[i][1].position = sf::Vector2f(x, (220 + i * 35) + 24);
        arm_buttons[i][2].position = sf::Vector2f(x + 70, (220 + i * 35) + 24);
        arm_buttons[i][3].position = sf::Vector2f(x + 70, (220 + i * 35) - 4);

        sf::VertexArray arm_button_shadow = sf::VertexArray(sf::Quads, 4);
        arm_button_shadow[0].position = sf::Vector2f(x, (220 + i * 35) - 4);
        arm_button_shadow[1].position = sf::Vector2f(x, (220 + i * 35) + 27);
        arm_button_shadow[2].position = sf::Vector2f(x + 73, (220 + i * 35) + 27);
        arm_button_shadow[3].position = sf::Vector2f(x + 73, (220 + i * 35) - 4);

        arm_button_shadow[0].color = sf::Color::Black;
        arm_button_shadow[1].color = sf::Color::Black;
        arm_button_shadow[2].color = sf::Color::Black;
        arm_button_shadow[3].color = sf::Color::Black;

        if (arm_buttons[i].getBounds().contains(mouse_position.x, mouse_position.y))
        {
            arm_buttons[i][0].color = sf::Color(53, 53, 53, 255);
            arm_buttons[i][1].color = sf::Color(53, 53, 53, 255);
            arm_buttons[i][2].color = sf::Color(53, 53, 53, 255);
            arm_buttons[i][3].color = sf::Color(53, 53, 53, 255);
        }
        else
        {
            arm_buttons[i][0].color = sf::Color(35, 35, 35, 255);
            arm_buttons[i][1].color = sf::Color(35, 35, 35, 255);
            arm_buttons[i][2].color = sf::Color(35, 35, 35, 255);
            arm_buttons[i][3].color = sf::Color(35, 35, 35, 255);
        }

        std::string desc = arms[i].name + ": " + std::to_string(arms[i].modifier) + " armor, $" + std::to_string(arms[i].price);
        arm_descriptions[i].setFont(market_font);
        arm_descriptions[i].setCharacterSize(14);
        if (arms[i].level == 3)
        {
            arm_descriptions[i].setFillColor(sf::Color::Green);
        }
        else if (arms[i].level == 2)
        {
            arm_descriptions[i].setFillColor(sf::Color::Yellow);
        }
        else if (arms[i].level == 1)
        {
            arm_descriptions[i].setFillColor(sf::Color::Red);
        }
        arm_descriptions[i].setPosition(x - 230, 222 + (i * 35 - 2));
        arm_descriptions[i].setString(desc);

        arm_button_labels[i].setFont(market_font);
        arm_button_labels[i].setCharacterSize(16);
        arm_button_labels[i].setFillColor(sf::Color::Black);
        arm_button_labels[i].setPosition(x + 18, 222 + (i * 35 - 2));
        arm_button_labels[i].setString("BUY");

        window.draw(arm_descriptions[i]);
        window.draw(arm_button_shadow);
        window.draw(arm_buttons[i]);
        window.draw(arm_button_labels[i]);
    }

    for (unsigned int i = 0; i < leg_buttons.size(); i++)
    {
        float x = window.getView().getSize().x / 2 + 500;

        leg_buttons[i] = sf::VertexArray(sf::Quads, 4);
        leg_buttons[i][0].position = sf::Vector2f(x, (360 + i * 35) - 4);
        leg_buttons[i][1].position = sf::Vector2f(x, (360 + i * 35) + 24);
        leg_buttons[i][2].position = sf::Vector2f(x + 70, (360 + i * 35) + 24);
        leg_buttons[i][3].position = sf::Vector2f(x + 70, (360 + i * 35) - 4);

        sf::VertexArray leg_button_shadow = sf::VertexArray(sf::Quads, 4);
        leg_button_shadow[0].position = sf::Vector2f(x, (360 + i * 35) - 4);
        leg_button_shadow[1].position = sf::Vector2f(x, (360 + i * 35) + 27);
        leg_button_shadow[2].position = sf::Vector2f(x + 73, (360 + i * 35) + 27);
        leg_button_shadow[3].position = sf::Vector2f(x + 73, (360 + i * 35) - 4);

        leg_button_shadow[0].color = sf::Color::Black;
        leg_button_shadow[1].color = sf::Color::Black;
        leg_button_shadow[2].color = sf::Color::Black;
        leg_button_shadow[3].color = sf::Color::Black;

        if (leg_buttons[i].getBounds().contains(mouse_position.x, mouse_position.y))
        {
            leg_buttons[i][0].color = sf::Color(53, 53, 53, 255);
            leg_buttons[i][1].color = sf::Color(53, 53, 53, 255);
            leg_buttons[i][2].color = sf::Color(53, 53, 53, 255);
            leg_buttons[i][3].color = sf::Color(53, 53, 53, 255);
        }
        else
        {
            leg_buttons[i][0].color = sf::Color(35, 35, 35, 255);
            leg_buttons[i][1].color = sf::Color(35, 35, 35, 255);
            leg_buttons[i][2].color = sf::Color(35, 35, 35, 255);
            leg_buttons[i][3].color = sf::Color(35, 35, 35, 255);
        }

        std::string desc = legs[i].name + ": " + std::to_string(legs[i].modifier) + " armor, $"+ std::to_string(legs[i].price);
        leg_descriptions[i].setFont(market_font);
        leg_descriptions[i].setCharacterSize(14);
        if (legs[i].level == 3)
        {
            leg_descriptions[i].setFillColor(sf::Color::Green);
        }
        else if (legs[i].level == 2)
        {
            leg_descriptions[i].setFillColor(sf::Color::Yellow);
        }
        else if (legs[i].level == 1)
        {
            leg_descriptions[i].setFillColor(sf::Color::Red);
        }
        leg_descriptions[i].setPosition(x - 230, 362 + (i * 35 - 2));
        leg_descriptions[i].setString(desc);

        leg_button_labels[i].setFont(market_font);
        leg_button_labels[i].setCharacterSize(16);
        leg_button_labels[i].setFillColor(sf::Color::Black);
        leg_button_labels[i].setPosition(x + 18, 362 + (i * 35 - 2));
        leg_button_labels[i].setString("BUY");

        window.draw(leg_descriptions[i]);
        window.draw(leg_button_shadow);
        window.draw(leg_buttons[i]);
        window.draw(leg_button_labels[i]);
    }

    item_worth[0] = pc.player_mech.guns_modifier * 5000;
    item_worth[1] = pc.player_mech.cannons_modifier * 5000;
    item_worth[2] = pc.player_mech.cooler_modifier * 7 + pc.player_mech.cooler_modifier * 2500;
    item_worth[3] = pc.player_mech.max_reactor_integrity * 3;
    item_worth[4] = pc.player_mech.max_cockpit_integrity * 3;
    item_worth[5] = pc.player_mech.max_left_arm_integrity * 3;
    item_worth[6] = pc.player_mech.max_left_leg_integrity * 3;

    sf::Text worth;
    worth.setString("");

    for (unsigned int i = 0; i < sell_categories.size(); i++)
    {
        float y_origin = window.getView().getSize().y * 0.725;
        float x = i <= 3 ? 10 : 180;
        float y = i <= 3 ? i : i - 4;

        sell_buttons[i] = sf::VertexArray(sf::Quads, 4);
        sell_buttons[i][0].position = sf::Vector2f(x, (y_origin + y * 35) - 4);
        sell_buttons[i][1].position = sf::Vector2f(x, (y_origin + y * 35) + 24);
        sell_buttons[i][2].position = sf::Vector2f(x + 140, (y_origin + y * 35) + 24);
        sell_buttons[i][3].position = sf::Vector2f(x + 140, (y_origin + y * 35) - 4);

        sf::VertexArray sell_button_shadow = sf::VertexArray(sf::Quads, 4);
        sell_button_shadow[0].position = sf::Vector2f(x, (y_origin + y * 35) - 4);
        sell_button_shadow[1].position = sf::Vector2f(x, (y_origin + y * 35) + 27);
        sell_button_shadow[2].position = sf::Vector2f(x + 143, (y_origin + y * 35) + 27);
        sell_button_shadow[3].position = sf::Vector2f(x + 143, (y_origin + y * 35) - 4);

        sell_button_shadow[0].color = sf::Color::Black;
        sell_button_shadow[1].color = sf::Color::Black;
        sell_button_shadow[2].color = sf::Color::Black;
        sell_button_shadow[3].color = sf::Color::Black;

        if (sell_buttons[i].getBounds().contains(mouse_position.x, mouse_position.y))
        {
            sell_buttons[i][0].color = sf::Color(53, 53, 53, 255);
            sell_buttons[i][1].color = sf::Color(53, 53, 53, 255);
            sell_buttons[i][2].color = sf::Color(53, 53, 53, 255);
            sell_buttons[i][3].color = sf::Color(53, 53, 53, 255);
        }
        else
        {
            sell_buttons[i][0].color = sf::Color(35, 35, 35, 255);
            sell_buttons[i][1].color = sf::Color(35, 35, 35, 255);
            sell_buttons[i][2].color = sf::Color(35, 35, 35, 255);
            sell_buttons[i][3].color = sf::Color(35, 35, 35, 255);
        }

        sell_button_labels[i].setFont(market_font);
        sell_button_labels[i].setCharacterSize(16);
        sell_button_labels[i].setFillColor(sf::Color::Black);
        sell_button_labels[i].setPosition(x + 18, (y_origin + 2) + (y * 35 - 2));
        sell_button_labels[i].setString("SELL " + sell_categories[i]);

        window.draw(sell_button_shadow);
        window.draw(sell_buttons[i]);
        window.draw(sell_button_labels[i]);

        if (sell_buttons[i].getBounds().contains(mouse_position.x, mouse_position.y))
        {
            worth.setString("$" + std::to_string(item_worth[i]));
            worth.setFont(market_font);
            worth.setCharacterSize(16);
            worth.setFillColor(sf::Color::White);
            worth.setPosition(mouse_position.x + 20, mouse_position.y);
        }
    }

    window.draw(worth);

    float x = window.getView().getSize().x / 2 + 500;

    exit_button = sf::VertexArray(sf::Quads, 4);
    exit_button[0].position = sf::Vector2f(x, 596);
    exit_button[1].position = sf::Vector2f(x, 624);
    exit_button[2].position = sf::Vector2f(x + 70, 624);
    exit_button[3].position = sf::Vector2f(x + 70, 596);

    sf::VertexArray exit_button_shadow = sf::VertexArray(sf::Quads, 4);
    exit_button_shadow[0].position = sf::Vector2f(x, 596);
    exit_button_shadow[1].position = sf::Vector2f(x, 627);
    exit_button_shadow[2].position = sf::Vector2f(x + 73, 627);
    exit_button_shadow[3].position = sf::Vector2f(x + 73, 596);

    exit_button_shadow[0].color = sf::Color::Black;
    exit_button_shadow[1].color = sf::Color::Black;
    exit_button_shadow[2].color = sf::Color::Black;
    exit_button_shadow[3].color = sf::Color::Black;

    if (exit_button.getBounds().contains(mouse_position.x, mouse_position.y))
    {
        exit_button[0].color = sf::Color(53, 53, 53, 255);
        exit_button[1].color = sf::Color(53, 53, 53, 255);
        exit_button[2].color = sf::Color(53, 53, 53, 255);
        exit_button[3].color = sf::Color(53, 53, 53, 255);
    }
    else
    {
        exit_button[0].color = sf::Color(35, 35, 35, 255);
        exit_button[1].color = sf::Color(35, 35, 35, 255);
        exit_button[2].color = sf::Color(35, 35, 35, 255);
        exit_button[3].color = sf::Color(35, 35, 35, 255);
    }

    sf::Text exit_button_label;
    exit_button_label.setFont(market_font);
    exit_button_label.setCharacterSize(18);
    exit_button_label.setFillColor(sf::Color::Black);
    exit_button_label.setPosition(x + 18, 598);
    exit_button_label.setString("EXIT");

    window.draw(exit_button_shadow);
    window.draw(exit_button);
    window.draw(exit_button_label);
}
