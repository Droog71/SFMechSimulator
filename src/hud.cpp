#include <hud.h>
#include <math.h>
#include <mech.h>

// Initializes reference to main assets class
void hud::init(assets &resources)
{
    this->resources = resources;
}

// Displays a notice with the given string
void hud::display_notice(sf::RenderWindow &window, std::string notice, float frame_time)
{
    sf::Vector2f notice_pos;
    notice_pos.x = (window.getView().getSize().x / 2) - (resources.notice.getGlobalBounds().width / 2);
    notice_pos.y = (window.getView().getSize().y / 2);
    resources.notice.setString(notice);
    resources.notice.setPosition(notice_pos);
    window.draw(resources.notice);

    notice_timer += 10 * frame_time;
    if (notice_timer >= 30)
    {
        notice_timer = 0;
        show_notice = false;
    }
}

// Draws mech status image with color based on damage
void hud::draw_mech(float x_pos, mech &mech_to_draw, sf::RenderWindow &window)
{
    // Right arm
    sf::VertexArray right_arm_quad(sf::Quads, 4);
    right_arm_quad[0].position = sf::Vector2f(window.getView().getSize().x * x_pos, window.getView().getSize().y * 0.8 + 65);
    right_arm_quad[1].position = sf::Vector2f(window.getView().getSize().x * x_pos + 40, window.getView().getSize().y * 0.8 + 65);
    right_arm_quad[2].position = sf::Vector2f(window.getView().getSize().x * x_pos + 40, window.getView().getSize().y * 0.8);
    right_arm_quad[3].position = sf::Vector2f(window.getView().getSize().x * x_pos, window.getView().getSize().y * 0.8);
    right_arm_quad[0].texCoords = sf::Vector2f(0.f, 130.f);
    right_arm_quad[1].texCoords = sf::Vector2f(76.f, 130.f);
    right_arm_quad[2].texCoords = sf::Vector2f(76.f, 0.f);
    right_arm_quad[3].texCoords = sf::Vector2f(0.f, 0.f);

    float right_arm_red = 255 - (255 * ((float)mech_to_draw.right_arm_integrity / (float)mech_to_draw.max_right_arm_integrity));
    float right_arm_green = 100 * ((float)mech_to_draw.right_arm_integrity / (float)mech_to_draw.max_right_arm_integrity);
    for (int i = 0; i < 4; i++)
    {
        right_arm_quad[i].color = sf::Color(right_arm_red, right_arm_green, 0, 255);
    }
    window.draw(right_arm_quad, &resources.mech_status_texture);

    // Cockpit
    sf::VertexArray cockpit_quad(sf::Quads, 4);
    cockpit_quad[0].position = sf::Vector2f(window.getView().getSize().x * x_pos + 40, window.getView().getSize().y * 0.8 + 30);
    cockpit_quad[1].position = sf::Vector2f(window.getView().getSize().x * x_pos + 92, window.getView().getSize().y * 0.8 + 30);
    cockpit_quad[2].position = sf::Vector2f(window.getView().getSize().x * x_pos + 92, window.getView().getSize().y * 0.8);
    cockpit_quad[3].position = sf::Vector2f(window.getView().getSize().x * x_pos + 40, window.getView().getSize().y * 0.8);
    cockpit_quad[0].texCoords = sf::Vector2f(76.f, 59.f);
    cockpit_quad[1].texCoords = sf::Vector2f(180.f, 59.f);
    cockpit_quad[2].texCoords = sf::Vector2f(180.f, 0.f);
    cockpit_quad[3].texCoords = sf::Vector2f(76.f, 0.f);

    float cockpit_red = 255 - (255 * ((float)mech_to_draw.cockpit_integrity / (float)mech_to_draw.max_cockpit_integrity));
    float cockpit_green = 100 * ((float)mech_to_draw.cockpit_integrity / (float)mech_to_draw.max_cockpit_integrity);
    for (int i = 0; i < 4; i++)
    {
        cockpit_quad[i].color = sf::Color(cockpit_red, cockpit_green, 0, 255);
    }
    window.draw(cockpit_quad, &resources.mech_status_texture);

    // Left arm
    sf::VertexArray left_arm_quad(sf::Quads, 4);
    left_arm_quad[0].position = sf::Vector2f(window.getView().getSize().x * x_pos + 92, window.getView().getSize().y * 0.8 + 65);
    left_arm_quad[1].position = sf::Vector2f(window.getView().getSize().x * x_pos + 132, window.getView().getSize().y * 0.8 + 65);
    left_arm_quad[2].position = sf::Vector2f(window.getView().getSize().x * x_pos + 132, window.getView().getSize().y * 0.8);
    left_arm_quad[3].position = sf::Vector2f(window.getView().getSize().x * x_pos + 92, window.getView().getSize().y * 0.8);
    left_arm_quad[0].texCoords = sf::Vector2f(178.f, 130.f);
    left_arm_quad[1].texCoords = sf::Vector2f(256.f, 130.f);
    left_arm_quad[2].texCoords = sf::Vector2f(256.f, 0.f);
    left_arm_quad[3].texCoords = sf::Vector2f(178.f, 0.f);

    float left_arm_red = 255 - (255 * ((float)mech_to_draw.left_arm_integrity / (float)mech_to_draw.max_left_arm_integrity));
    float left_arm_green = 100 * ((float)mech_to_draw.left_arm_integrity / (float)mech_to_draw.max_left_arm_integrity);
    for (int i = 0; i < 4; i++)
    {
        left_arm_quad[i].color = sf::Color(left_arm_red, left_arm_green, 0, 255);
    }
    window.draw(left_arm_quad, &resources.mech_status_texture);

    // Reactor
    sf::VertexArray reactor_quad(sf::Quads, 4);
    reactor_quad[0].position = sf::Vector2f(window.getView().getSize().x * x_pos + 45, window.getView().getSize().y * 0.8 + 50);
    reactor_quad[1].position = sf::Vector2f(window.getView().getSize().x * x_pos + 88, window.getView().getSize().y * 0.8 + 50);
    reactor_quad[2].position = sf::Vector2f(window.getView().getSize().x * x_pos + 88, window.getView().getSize().y * 0.8 + 30);
    reactor_quad[3].position = sf::Vector2f(window.getView().getSize().x * x_pos + 45, window.getView().getSize().y * 0.8 + 30);
    reactor_quad[0].texCoords = sf::Vector2f(85.f, 96.f);
    reactor_quad[1].texCoords = sf::Vector2f(170.f, 96.f);
    reactor_quad[2].texCoords = sf::Vector2f(170.f, 56.f);
    reactor_quad[3].texCoords = sf::Vector2f(85.f, 56.f);

    float reactor_red = 255 - (255 * ((float)mech_to_draw.reactor_integrity / (float)mech_to_draw.max_reactor_integrity));
    float reactor_green = 100 * ((float)mech_to_draw.reactor_integrity / (float)mech_to_draw.max_reactor_integrity);
    for (int i = 0; i < 4; i++)
    {
        reactor_quad[i].color = sf::Color(reactor_red, reactor_green, 0, 255);
    }
    window.draw(reactor_quad, &resources.mech_status_texture);

    // Cooler
    sf::VertexArray cooler_quad(sf::Quads, 4);
    cooler_quad[0].position = sf::Vector2f(window.getView().getSize().x * x_pos + 45, window.getView().getSize().y * 0.8 + 70);
    cooler_quad[1].position = sf::Vector2f(window.getView().getSize().x * x_pos + 88, window.getView().getSize().y * 0.8 + 70);
    cooler_quad[2].position = sf::Vector2f(window.getView().getSize().x * x_pos + 88, window.getView().getSize().y * 0.8 + 50);
    cooler_quad[3].position = sf::Vector2f(window.getView().getSize().x * x_pos + 45, window.getView().getSize().y * 0.8 + 50);
    cooler_quad[0].texCoords = sf::Vector2f(85.f, 134.f);
    cooler_quad[1].texCoords = sf::Vector2f(170.f, 134.f);
    cooler_quad[2].texCoords = sf::Vector2f(170.f, 96.f);
    cooler_quad[3].texCoords = sf::Vector2f(85.f, 96.f);

    float cooler_red = 255 - (255 * ((float)mech_to_draw.cooler_integrity / (float)mech_to_draw.max_cooler_integrity));
    float cooler_green = 100 * ((float)mech_to_draw.cooler_integrity / (float)mech_to_draw.max_cooler_integrity);
    for (int i = 0; i < 4; i++)
    {
        cooler_quad[i].color = sf::Color(cooler_red, cooler_green, 0, 255);
    }
    window.draw(cooler_quad, &resources.mech_status_texture);

    // Right leg
    sf::VertexArray right_leg_quad(sf::Quads, 4);
    right_leg_quad[0].position = sf::Vector2f(window.getView().getSize().x * x_pos + 3, window.getView().getSize().y * 0.8 + 133);
    right_leg_quad[1].position = sf::Vector2f(window.getView().getSize().x * x_pos + 67, window.getView().getSize().y * 0.8 + 133);
    right_leg_quad[2].position = sf::Vector2f(window.getView().getSize().x * x_pos + 67, window.getView().getSize().y * 0.8 + 69);
    right_leg_quad[3].position = sf::Vector2f(window.getView().getSize().x * x_pos + 3, window.getView().getSize().y * 0.8 + 69);
    right_leg_quad[0].texCoords = sf::Vector2f(0.f, 256.f);
    right_leg_quad[1].texCoords = sf::Vector2f(128.f, 256.f);
    right_leg_quad[2].texCoords = sf::Vector2f(128.f, 131.f);
    right_leg_quad[3].texCoords = sf::Vector2f(0.f, 131.f);

    float right_leg_red = 255 - (255 * ((float)mech_to_draw.right_leg_integrity / (float)mech_to_draw.max_right_leg_integrity));
    float right_leg_green = 100 * ((float)mech_to_draw.right_leg_integrity / (float)mech_to_draw.max_right_leg_integrity);
    for (int i = 0; i < 4; i++)
    {
        right_leg_quad[i].color = sf::Color(right_leg_red, right_leg_green, 0, 255);
    }
    window.draw(right_leg_quad, &resources.mech_status_texture);

    // Left leg
    sf::VertexArray left_leg_quad(sf::Quads, 4);
    left_leg_quad[0].position = sf::Vector2f(window.getView().getSize().x * x_pos + 67, window.getView().getSize().y * 0.8 + 133);
    left_leg_quad[1].position = sf::Vector2f(window.getView().getSize().x * x_pos + 131, window.getView().getSize().y * 0.8 + 133);
    left_leg_quad[2].position = sf::Vector2f(window.getView().getSize().x * x_pos + 131, window.getView().getSize().y * 0.8 + 69);
    left_leg_quad[3].position = sf::Vector2f(window.getView().getSize().x * x_pos + 67, window.getView().getSize().y * 0.8 + 69);
    left_leg_quad[0].texCoords = sf::Vector2f(128.f, 256.f);
    left_leg_quad[1].texCoords = sf::Vector2f(256.f, 256.f);
    left_leg_quad[2].texCoords = sf::Vector2f(256.f, 131.f);
    left_leg_quad[3].texCoords = sf::Vector2f(128.f, 131.f);

    float left_leg_red = 255 - (255 * ((float)mech_to_draw.left_leg_integrity / (float)mech_to_draw.max_left_leg_integrity));
    float left_leg_green = 100 * ((float)mech_to_draw.left_leg_integrity / (float)mech_to_draw.max_left_leg_integrity);
    for (int i = 0; i < 4; i++)
    {
        left_leg_quad[i].color = sf::Color(left_leg_red, left_leg_green, 0, 255);
    }
    window.draw(left_leg_quad, &resources.mech_status_texture);
}

void hud::draw_hud(sf::RenderWindow &window, float frame_time, int target_id, float speed, float torso_angle, mech &player_mech, mech &target_mech)
{
    sf::Sprite status_bg = sf::Sprite(resources.gui_background_texture);
    status_bg.setPosition(0, window.getView().getSize().y * 0.786);
    status_bg.setScale(window.getView().getSize().x / 2977, window.getView().getSize().y / 1600);
    window.draw(status_bg);

    // Draw torso angle a the bottom right corner of the screen
    int torso_angle_int = floor(torso_angle);
    sf::String torso_string = "TORSO: " + std::to_string(torso_angle_int);
    resources.torso_display.setString(torso_string);
    resources.torso_display.setPosition(window.getView().getSize().x * 0.05, window.getView().getSize().y * 0.83);
    window.draw(resources.torso_display);

    // Draw throttle percentage a the bottom right corner of the screen
    int throttle = floor((speed) / 0.125 * 100);
    sf::String throttle_string = "THROTTLE: " + std::to_string(throttle);
    resources.throttle_display.setString(throttle_string);
    resources.throttle_display.setPosition(window.getView().getSize().x * 0.05, window.getView().getSize().y * 0.86);
    window.draw(resources.throttle_display);

    // Draw mech status at the bottom of the screen
    sf::String status =
    "MECH STATUS\n\nRIGHT LEG: " + std::to_string(player_mech.right_leg_integrity) + "\n" +
    "LEFT LEG: " + std::to_string(player_mech.left_leg_integrity) + "\n" +
    "RIGHT ARM: " + std::to_string(player_mech.right_arm_integrity) + "\n" +
    "LEFT ARM: " + std::to_string(player_mech.left_arm_integrity) + "\n" +
    "REACTOR: " + std::to_string(player_mech.reactor_integrity) + "\n" +
    "COOLER: " + std::to_string(player_mech.cooler_integrity) + "\n" +
    "COCKPIT: " + std::to_string(player_mech.cockpit_integrity) + "\n" +
    "HEAT: " + std::to_string((int)player_mech.heat);
    resources.mech_status.setString(status);
    resources.mech_status.setPosition(window.getView().getSize().x * 0.15, window.getView().getSize().y * 0.80);
    window.draw(resources.mech_status);
    draw_mech(0.265, player_mech, window);

    // Draw player heat meter
    sf::VertexArray heat_quad_bg(sf::Quads, 4);
    heat_quad_bg[0].position = sf::Vector2f(window.getView().getSize().x * 0.265 + 178, window.getView().getSize().y * 0.825 + 106);
    heat_quad_bg[1].position = sf::Vector2f(window.getView().getSize().x * 0.265 + 213, window.getView().getSize().y * 0.825 + 106);
    heat_quad_bg[2].position = sf::Vector2f(window.getView().getSize().x * 0.265 + 213, window.getView().getSize().y * 0.825);
    heat_quad_bg[3].position = sf::Vector2f(window.getView().getSize().x * 0.265 + 178, window.getView().getSize().y * 0.825);
    for (int i = 0; i < 4; i++)
    {
        heat_quad_bg[i].color = sf::Color::Black;
    }
    window.draw(heat_quad_bg);

    sf::VertexArray heat_quad(sf::Quads, 4);
    heat_quad[0].position = sf::Vector2f(window.getView().getSize().x * 0.265 + 180, window.getView().getSize().y * 0.83 + 100);
    heat_quad[1].position = sf::Vector2f(window.getView().getSize().x * 0.265 + 212, window.getView().getSize().y * 0.83 + 100);
    heat_quad[2].position = sf::Vector2f(window.getView().getSize().x * 0.265 + 212, window.getView().getSize().y * 0.83 + 100 - player_mech.heat);
    heat_quad[3].position = sf::Vector2f(window.getView().getSize().x * 0.265 + 180, window.getView().getSize().y * 0.83 + 100 - player_mech.heat);
    for (int i = 0; i < 4; i++)
    {
        heat_quad[i].color = sf::Color(200, 0, 0, 255);
    }
    window.draw(heat_quad);

    // Draw target status at the bottom of the screen
    if (target_id != 0)
    {
        sf::Sprite status_bg = sf::Sprite(resources.target_gui_background_texture);
        status_bg.setPosition(window.getView().getSize().x * 0.685, window.getView().getSize().y * 0.786);
        status_bg.setScale(window.getView().getSize().x / 2285, window.getView().getSize().y / 1600);
        window.draw(status_bg);

        sf::String status =
        "TARGET STATUS\n\nRIGHT LEG: " + std::to_string(target_mech.right_leg_integrity) + "\n" +
        "LEFT LEG: " + std::to_string(target_mech.left_leg_integrity) + "\n" +
        "RIGHT ARM: " + std::to_string(target_mech.right_arm_integrity) + "\n" +
        "LEFT ARM: " + std::to_string(target_mech.left_arm_integrity) + "\n" +
        "REACTOR: " + std::to_string(target_mech.reactor_integrity) + "\n" +
        "COOLER: " + std::to_string(target_mech.cooler_integrity) + "\n" +
        "COCKPIT: " + std::to_string(target_mech.cockpit_integrity) + "\n" +
        "HEAT: " + std::to_string((int)target_mech.heat);
        resources.target_status.setString(status);
        resources.target_status.setPosition(window.getView().getSize().x * 0.7, window.getView().getSize().y * 0.80);
        window.draw(resources.target_status);
        draw_mech(0.82, target_mech, window);

        // Draw target heat meter
        sf::VertexArray heat_quad_bg(sf::Quads, 4);
        heat_quad_bg[0].position = sf::Vector2f(window.getView().getSize().x * 0.82 + 178, window.getView().getSize().y * 0.825 + 106);
        heat_quad_bg[1].position = sf::Vector2f(window.getView().getSize().x * 0.82 + 214, window.getView().getSize().y * 0.825 + 106);
        heat_quad_bg[2].position = sf::Vector2f(window.getView().getSize().x * 0.82 + 214, window.getView().getSize().y * 0.825);
        heat_quad_bg[3].position = sf::Vector2f(window.getView().getSize().x * 0.82 + 178, window.getView().getSize().y * 0.825);
        for (int i = 0; i < 4; i++)
        {
            heat_quad_bg[i].color = sf::Color::Black;
        }
        window.draw(heat_quad_bg);

        sf::VertexArray heat_quad(sf::Quads, 4);
        heat_quad[0].position = sf::Vector2f(window.getView().getSize().x * 0.82 + 180, window.getView().getSize().y * 0.83 + 100);
        heat_quad[1].position = sf::Vector2f(window.getView().getSize().x * 0.82 + 212, window.getView().getSize().y * 0.83 + 100);
        heat_quad[2].position = sf::Vector2f(window.getView().getSize().x * 0.82 + 212, window.getView().getSize().y * 0.83 + 100 - target_mech.heat);
        heat_quad[3].position = sf::Vector2f(window.getView().getSize().x * 0.82 + 180, window.getView().getSize().y * 0.83 + 100 - target_mech.heat);
        for (int i = 0; i < 4; i++)
        {
            heat_quad[i].color = sf::Color(200, 0, 0, 255);
        }
        window.draw(heat_quad);
    }

    // Draw the crosshair
    if (player_mech.destroyed() == false)
    {
        float chx = (window.getView().getSize().x / 2) - (resources.crosshair_texture.getSize().x / 2);
        float chy = (window.getView().getSize().y / 2) - (resources.crosshair_texture.getSize().y / 2) * 3;
        sf::Vector2f chv(chx, chy);
        resources.crosshair_sprite.setPosition(chv);
        window.draw(resources.crosshair_sprite);
    }

    // Draw notices
    if (show_notice == true)
    {
        display_notice(window, notice, frame_time);
    }
}
