#include <cockpit.h>

// Draws the cockpit, muzzle flashes and hit effects
void draw_cockpit(sf::RenderWindow &window, assets &resources, player_controller &pc, bool took_damage)
{
    float cockpit_x = window.getView().getSize().x / resources.cockpit_sprite.getLocalBounds().width;
    float cockpit_y = window.getView().getSize().y / resources.cockpit_sprite.getLocalBounds().height;
    resources.cockpit_sprite.setScale(cockpit_x, cockpit_y);
    resources.cockpit_sprite.setPosition(0, 0);
    window.draw(resources.cockpit_sprite);

    if (pc.player_mech.destroyed() == false)
    {
        if (pc.muzzle_flash == true)
        {
            sf::Sprite fire_sprite;

            if (pc.player_mech.left_arm_destroyed())
            {
                fire_sprite = sf::Sprite(resources.cockpit_fire_right_texture);
            }
            else if (pc.player_mech.right_arm_destroyed())
            {
                fire_sprite = sf::Sprite(resources.cockpit_fire_left_texture);
            }
            else
            {
                fire_sprite = sf::Sprite(resources.cockpit_fire_texture);
            }

            fire_sprite.setScale(cockpit_x, cockpit_y);
            fire_sprite.setPosition(0, 0);
            window.draw(fire_sprite);
        }

        if (pc.cannon_flash == true)
        {
            sf::Sprite fire_sprite;

            if (pc.player_mech.left_arm_destroyed())
            {
                fire_sprite = sf::Sprite(resources.cockpit_cannon_right_texture);
            }
            else if (pc.player_mech.right_arm_destroyed())
            {
                fire_sprite = sf::Sprite(resources.cockpit_cannon_left_texture);
            }
            else
            {
                fire_sprite = sf::Sprite(resources.cockpit_cannon_texture);
            }

            fire_sprite.setScale(cockpit_x, cockpit_y);
            fire_sprite.setPosition(0, 0);
            window.draw(fire_sprite);
        }

        if (took_damage == true)
        {
            sf::Sprite damage_sprite = sf::Sprite(resources.cockpit_impact_texture);
            damage_sprite.setScale(cockpit_x, cockpit_y);
            damage_sprite.setPosition(0, 0);
            window.draw(damage_sprite);
        }
    }
}
