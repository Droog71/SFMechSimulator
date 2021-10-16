#include <math.h>
#include <iostream>
#include <assets.h>
#include <entity.h>
#include <SFML/Graphics.hpp>
#include <world_generator.h>

// Constructor
world_generator::world_generator()
{
    wall_count = 0;
    mob_count = 0;
    mission = 1;
    theme = 1;
    maze = true;
    min_npc_spawned = false;
}

// Generates the playing area and npc mechs
void world_generator::generate_world(assets &resources, std::vector<entity> &entities, int entity_count)
{
    int e = 0;
    entities = std::vector<entity>(entity_count);

    // Border
    for (int i = 0; i < 153; i++)
    {
        entities[e].position.x = 60;
        entities[e].position.y = 40 + i * 4;
        entities[e].type = "wall";
        entities[e].icon.setTexture(resources.wall_icon_texture);
        e++;
    }

    for (int i = 0; i < 153; i++)
    {
        entities[e].position.x = 550;
        entities[e].position.y = 40 + i * 4;
        entities[e].type = "wall";
        entities[e].icon.setTexture(resources.wall_icon_texture);
        e++;
    }

    for (int i = 0; i < 122; i++)
    {
        entities[e].position.x = 60 + i * 4;
        entities[e].position.y = 40;
        entities[e].type = "wall";
        entities[e].icon.setTexture(resources.wall_icon_texture);
        e++;
    }

    for (int i = 0; i < 122; i++)
    {
        entities[e].position.x = 60 + i * 4;
        entities[e].position.y = 650;
        entities[e].type = "wall";
        entities[e].icon.setTexture(resources.wall_icon_texture);
        e++;
    }

    if (maze == true)
    {
        // Wall
        for (int i = 0; i < 60; i++)
        {
            entities[e].position.x = 180;
            entities[e].position.y = 40 + i * 4;
            entities[e].type = "wall";
            entities[e].icon.setTexture(resources.wall_icon_texture);
            e++;
        }

        // Wall
        for (int i = 0; i < 125; i++)
        {
            entities[e].position.x = 300;
            entities[e].position.y = 154 + i * 4;
            entities[e].type = "wall";
            entities[e].icon.setTexture(resources.wall_icon_texture);
            e++;
        }

        // Wall
        for (int i = 0; i < 120; i++)
        {
            entities[e].position.x = 420;
            entities[e].position.y = 40 + i * 4;
            entities[e].type = "wall";
            entities[e].icon.setTexture(resources.wall_icon_texture);
            e++;
        }

        // Wall
        for (int i = 0; i < 60; i++)
        {
            entities[e].position.x = 60 + i * 4;
            entities[e].position.y = 400;
            entities[e].type = "wall";
            entities[e].icon.setTexture(resources.wall_icon_texture);
            e++;
        }
    }

    wall_count = e;

    for (int i = wall_count; i < entity_count; i++)
    {
        int r = rand() % 1000;

        if (r < 1000 && r >= 950)
        {
            entities[e].type = "tree";
            if (maze == true)
            {
                entities[e].position.x = 75 + ( rand() % ( 165 - 75 + 1 ) );
                entities[e].position.y = 75 + ( rand() % ( 645 - 75 + 1 ) );
            }
            else
            {
                entities[e].position.x = 70 + ( rand() % ( 540 - 70 + 1 ) );
                entities[e].position.y = 50 + ( rand() % ( 640 - 50 + 1 ) );
            }

            if (theme == 1)
            {
                entities[e].sprite.setTexture(resources.tree_texture);
            }
            else
            {
                entities[e].sprite.setTexture(resources.tree_3_texture);
            }
        }
        else if (r < 950 && r >= 900)
        {
            entities[e].type = "tree";
            if (maze == true)
            {
                entities[e].position.x = 195 + ( rand() % ( 285 - 195 + 1 ) );
                entities[e].position.y = 75 + ( rand() % ( 645 - 75 + 1 ) );
            }
            else
            {
                entities[e].position.x = 70 + ( rand() % ( 540 - 70 + 1 ) );
                entities[e].position.y = 50 + ( rand() % ( 640 - 50 + 1 ) );
            }

            if (theme == 1)
            {
                entities[e].sprite.setTexture(resources.tree_texture);
            }
            else
            {
                entities[e].sprite.setTexture(resources.tree_3_texture);
            }
        }
        else if (r < 900 && r >= 850)
        {
            entities[e].type = "tree";
            if (maze == true)
            {
                entities[e].position.x = 315 + ( rand() % ( 405 - 315 + 1 ) );
                entities[e].position.y = 75 + ( rand() % ( 645 - 75 + 1 ) );
            }
            else
            {
                entities[e].position.x = 70 + ( rand() % ( 540 - 70 + 1 ) );
                entities[e].position.y = 50 + ( rand() % ( 640 - 50 + 1 ) );
            }

            if (theme == 1)
            {
                entities[e].sprite.setTexture(resources.tree_texture);
            }
            else
            {
                entities[e].sprite.setTexture(resources.tree_3_texture);
            }
        }
        else if (r < 850 && r >= 800)
        {
            entities[e].type = "tree";
            if (maze == true)
            {
                entities[e].position.x = 435 + ( rand() % ( 530 - 435 + 1 ) );
                entities[e].position.y = 75 + ( rand() % ( 645 - 75 + 1 ) );
            }
            else
            {
                entities[e].position.x = 70 + ( rand() % ( 540 - 70 + 1 ) );
                entities[e].position.y = 50 + ( rand() % ( 640 - 50 + 1 ) );
            }

            if (theme == 1)
            {
                entities[e].sprite.setTexture(resources.tree_texture);
            }
            else
            {
                entities[e].sprite.setTexture(resources.tree_3_texture);
            }
        }
        else if (r < 800 && r >= 750)
        {
            entities[e].type = "tree_2";
            if (maze == true)
            {
                entities[e].position.x = 75 + ( rand() % ( 175 - 75 + 1 ) );
                entities[e].position.y = 200 + ( rand() % ( 350 - 200 + 1 ) );
            }
            else
            {
                entities[e].position.x = 70 + ( rand() % ( 540 - 70 + 1 ) );
                entities[e].position.y = 50 + ( rand() % ( 640 - 50 + 1 ) );
            }

            if (theme == 1)
            {
                entities[e].sprite.setTexture(resources.tree_2_texture);
            }
            else
            {
                entities[e].sprite.setTexture(resources.tree_4_texture);
            }
        }
        else if (r < 750 && r >= 700)
        {
            entities[e].type = "tree_2";
            if (maze == true)
            {
                entities[e].position.x = 195 + ( rand() % ( 285 - 195 + 1 ) );
                entities[e].position.y = 200 + ( rand() % ( 350 - 200 + 1 ) );
            }
            else
            {
                entities[e].position.x = 70 + ( rand() % ( 540 - 70 + 1 ) );
                entities[e].position.y = 50 + ( rand() % ( 640 - 50 + 1 ) );
            }

            if (theme == 1)
            {
                entities[e].sprite.setTexture(resources.tree_2_texture);
            }
            else
            {
                entities[e].sprite.setTexture(resources.tree_4_texture);
            }
        }
        else if (r < 700 && r >= 650)
        {
            entities[e].type = "tree_2";
            if (maze == true)
            {
                entities[e].position.x = 435 + ( rand() % ( 530 - 435 + 1 ) );
                entities[e].position.y = 75 + ( rand() % ( 645 - 75 + 1 ) );
            }
            else
            {
                entities[e].position.x = 70 + ( rand() % ( 540 - 70 + 1 ) );
                entities[e].position.y = 50 + ( rand() % ( 640 - 50 + 1 ) );
            }

            if (theme == 1)
            {
                entities[e].sprite.setTexture(resources.tree_2_texture);
            }
            else
            {
                entities[e].sprite.setTexture(resources.tree_4_texture);
            }
        }
        else if (r < 650 && r >= 600)
        {
            entities[e].type = "tree_2";
            if (maze == true)
            {
                entities[e].position.x = 435 + ( rand() % ( 530 - 435 + 1 ) );
                entities[e].position.y = 75 + ( rand() % ( 645 - 75 + 1 ) );
            }
            else
            {
                entities[e].position.x = 70 + ( rand() % ( 540 - 70 + 1 ) );
                entities[e].position.y = 50 + ( rand() % ( 640 - 50 + 1 ) );
            }

            if (theme == 1)
            {
                entities[e].sprite.setTexture(resources.tree_2_texture);
            }
            else
            {
                entities[e].sprite.setTexture(resources.tree_4_texture);
            }
        }

        int weapons_modifier = mission < 3 ? 0 : mission > 5 ? 3 : mission - 2 ;
        int armor_modifier = mission < 3 ? 1000 : mission > 5 ? 3000 : (mission - 2) * 1000;

        r = std::rand() % 10000;

        if ((r < 10000 && r >= 10000 - mission * 2) || min_npc_spawned == false)
        {
            if (mob_count < mission)
            {
                entities[e].id = e;
                entities[e].type = "mob";
                entities[e].sub_type = "mech";
                entities[e].sprite.setTexture(resources.mech_texture, true);
                entities[e].icon.setTexture(resources.mob_icon_texture);

                int upgrade_chance = rand() % 100;
                if (upgrade_chance >= 75)
                {
                    int rand_upgrade = rand() % 100;
                    if (rand_upgrade >= 50)
                    {
                        entities[e].entity_mech.guns_modifier = weapons_modifier;
                        entities[e].entity_mech.cannons_modifier = weapons_modifier;
                        entities[e].entity_mech.cooler_modifier = weapons_modifier;
                        entities[e].entity_mech.cooler_integrity = armor_modifier;
                        entities[e].entity_mech.max_cooler_integrity = armor_modifier;
                        entities[e].entity_mech.reactor_integrity = armor_modifier;
                        entities[e].entity_mech.max_reactor_integrity = armor_modifier;
                    }
                    else
                    {
                        entities[e].entity_mech.reactor_integrity = armor_modifier;
                        entities[e].entity_mech.max_reactor_integrity = armor_modifier;
                        entities[e].entity_mech.cockpit_integrity = armor_modifier;
                        entities[e].entity_mech.max_cockpit_integrity = armor_modifier;
                        entities[e].entity_mech.left_arm_integrity = armor_modifier;
                        entities[e].entity_mech.max_left_arm_integrity = armor_modifier;
                        entities[e].entity_mech.right_arm_integrity = armor_modifier;
                        entities[e].entity_mech.max_right_arm_integrity = armor_modifier;
                        entities[e].entity_mech.left_leg_integrity = armor_modifier;
                        entities[e].entity_mech.max_left_leg_integrity = armor_modifier;
                        entities[e].entity_mech.right_leg_integrity = armor_modifier;
                        entities[e].entity_mech.max_right_leg_integrity = armor_modifier;
                    }
                }

                if (maze == true)
                {
                    entities[e].position.x = 75 + ( rand() % ( 175 - 75 + 1 ) );
                    entities[e].position.y = 200 + ( rand() % ( 350 - 200 + 1 ) );
                }
                else
                {
                    entities[e].position.x = 70 + ( rand() % ( 540 - 70 + 1 ) );
                    entities[e].position.y = 50 + ( rand() % ( 640 - 50 + 1 ) );
                }

                mob_count++;
                min_npc_spawned = true;
            }
        }
        else if (r < 10000 - mission * 2 && r >= 10000 - mission * 4 && mob_count < mission)
        {
            entities[e].id = e;
            entities[e].type = "mob";
            entities[e].sub_type = "mech";
            entities[e].sprite.setTexture(resources.mech_texture, true);
            entities[e].icon.setTexture(resources.mob_icon_texture);

            int upgrade_chance = rand() % 100;
            if (upgrade_chance >= 75)
            {
                int rand_upgrade = rand() % 100;
                if (rand_upgrade >= 50)
                {
                    entities[e].entity_mech.guns_modifier = weapons_modifier;
                    entities[e].entity_mech.cannons_modifier = weapons_modifier;
                    entities[e].entity_mech.cooler_modifier = weapons_modifier;
                    entities[e].entity_mech.cooler_integrity = armor_modifier;
                    entities[e].entity_mech.max_cooler_integrity = armor_modifier;
                    entities[e].entity_mech.reactor_integrity = armor_modifier;
                    entities[e].entity_mech.max_reactor_integrity = armor_modifier;
                }
                else
                {
                    entities[e].entity_mech.reactor_integrity = armor_modifier;
                    entities[e].entity_mech.max_reactor_integrity = armor_modifier;
                    entities[e].entity_mech.cockpit_integrity = armor_modifier;
                    entities[e].entity_mech.max_cockpit_integrity = armor_modifier;
                    entities[e].entity_mech.left_arm_integrity = armor_modifier;
                    entities[e].entity_mech.max_left_arm_integrity = armor_modifier;
                    entities[e].entity_mech.right_arm_integrity = armor_modifier;
                    entities[e].entity_mech.max_right_arm_integrity = armor_modifier;
                    entities[e].entity_mech.left_leg_integrity = armor_modifier;
                    entities[e].entity_mech.max_left_leg_integrity = armor_modifier;
                    entities[e].entity_mech.right_leg_integrity = armor_modifier;
                    entities[e].entity_mech.max_right_leg_integrity = armor_modifier;
                }
            }

            if (maze == true)
            {
                entities[e].position.x = 195 + ( rand() % ( 285 - 195 + 1 ) );
                entities[e].position.y = 200 + ( rand() % ( 350 - 200 + 1 ) );
            }
            else
            {
                entities[e].position.x = 70 + ( rand() % ( 540 - 70 + 1 ) );
                entities[e].position.y = 50 + ( rand() % ( 640 - 50 + 1 ) );
            }

            mob_count++;
        }
        else if (r < 10000 - mission * 4 && r >= 10000 - mission * 6 && mob_count < mission)
        {
            entities[e].id = e;
            entities[e].type = "mob";
            entities[e].sub_type = "mech";
            entities[e].sprite.setTexture(resources.mech_texture, true);
            entities[e].icon.setTexture(resources.mob_icon_texture);

            int upgrade_chance = rand() % 100;
            if (upgrade_chance >= 75)
            {
                int rand_upgrade = rand() % 100;
                if (rand_upgrade >= 50)
                {
                    entities[e].entity_mech.guns_modifier = weapons_modifier;
                    entities[e].entity_mech.cannons_modifier = weapons_modifier;
                    entities[e].entity_mech.cooler_modifier = weapons_modifier;
                    entities[e].entity_mech.cooler_integrity = armor_modifier;
                    entities[e].entity_mech.max_cooler_integrity = armor_modifier;
                    entities[e].entity_mech.reactor_integrity = armor_modifier;
                    entities[e].entity_mech.max_reactor_integrity = armor_modifier;
                }
                else
                {
                    entities[e].entity_mech.reactor_integrity = armor_modifier;
                    entities[e].entity_mech.max_reactor_integrity = armor_modifier;
                    entities[e].entity_mech.cockpit_integrity = armor_modifier;
                    entities[e].entity_mech.max_cockpit_integrity = armor_modifier;
                    entities[e].entity_mech.left_arm_integrity = armor_modifier;
                    entities[e].entity_mech.max_left_arm_integrity = armor_modifier;
                    entities[e].entity_mech.right_arm_integrity = armor_modifier;
                    entities[e].entity_mech.max_right_arm_integrity = armor_modifier;
                    entities[e].entity_mech.left_leg_integrity = armor_modifier;
                    entities[e].entity_mech.max_left_leg_integrity = armor_modifier;
                    entities[e].entity_mech.right_leg_integrity = armor_modifier;
                    entities[e].entity_mech.max_right_leg_integrity = armor_modifier;
                }
            }

            if (maze == true)
            {
                entities[e].position.x = 315 + ( rand() % ( 405 - 315 + 1 ) );
                entities[e].position.y = 75 + ( rand() % ( 645 - 75 + 1 ) );
            }
            else
            {
                entities[e].position.x = 70 + ( rand() % ( 540 - 70 + 1 ) );
                entities[e].position.y = 50 + ( rand() % ( 640 - 50 + 1 ) );
            }

            mob_count++;
        }
        else if (r < 10000 - mission * 6 && r >= 10000 - mission * 8 && mob_count < mission)
        {
            entities[e].id = e;
            entities[e].type = "mob";
            entities[e].sub_type = "mech";
            entities[e].sprite.setTexture(resources.mech_texture, true);
            entities[e].icon.setTexture(resources.mob_icon_texture);

            int upgrade_chance = rand() % 100;
            if (upgrade_chance >= 75)
            {
                int rand_upgrade = rand() % 100;
                if (rand_upgrade >= 50)
                {
                    entities[e].entity_mech.guns_modifier = weapons_modifier;
                    entities[e].entity_mech.cannons_modifier = weapons_modifier;
                    entities[e].entity_mech.cooler_modifier = weapons_modifier;
                    entities[e].entity_mech.cooler_integrity = armor_modifier;
                    entities[e].entity_mech.max_cooler_integrity = armor_modifier;
                    entities[e].entity_mech.reactor_integrity = armor_modifier;
                    entities[e].entity_mech.max_reactor_integrity = armor_modifier;
                }
                else
                {
                    entities[e].entity_mech.reactor_integrity = armor_modifier;
                    entities[e].entity_mech.max_reactor_integrity = armor_modifier;
                    entities[e].entity_mech.cockpit_integrity = armor_modifier;
                    entities[e].entity_mech.max_cockpit_integrity = armor_modifier;
                    entities[e].entity_mech.left_arm_integrity = armor_modifier;
                    entities[e].entity_mech.max_left_arm_integrity = armor_modifier;
                    entities[e].entity_mech.right_arm_integrity = armor_modifier;
                    entities[e].entity_mech.max_right_arm_integrity = armor_modifier;
                    entities[e].entity_mech.left_leg_integrity = armor_modifier;
                    entities[e].entity_mech.max_left_leg_integrity = armor_modifier;
                    entities[e].entity_mech.right_leg_integrity = armor_modifier;
                    entities[e].entity_mech.max_right_leg_integrity = armor_modifier;
                }
            }

            if (maze == true)
            {
                entities[e].position.x = 435 + ( rand() % ( 530 - 435 + 1 ) );
                entities[e].position.y = 75 + ( rand() % ( 645 - 75 + 1 ) );
            }
            else
            {
                entities[e].position.x = 70 + ( rand() % ( 540 - 70 + 1 ) );
                entities[e].position.y = 50 + ( rand() % ( 640 - 50 + 1 ) );
            }

            mob_count++;
        }

        e++;
    }

    mob_count = 0;
    min_npc_spawned = false;
}

// Reverses placement direction of walls which don't render correctly when placed with ascending depth with respect to the camera
void world_generator::flip_walls_vertical(std::vector<entity> &entities, int entity_count, bool inverse)
{
    if (inverse == true)
    {
        int e = 0;

        // Border
        for (int i = 0; i < 153; i++)
        {
            entities[e].position.x = 60;
            entities[e].position.y = 648 - i * 4;
            e++;
        }

        for (int i = 0; i < 153; i++)
        {
            entities[e].position.x = 550;
            entities[e].position.y = 648 - i * 4;
            e++;
        }

        for (int i = 0; i < 122; i++)
        {
            e++;
        }

        for (int i = 0; i < 122; i++)
        {
            e++;
        }

        if (maze == true)
        {
            // Wall
            for (int i = 0; i < 60; i++)
            {
                entities[e].position.x = 180 ;
                entities[e].position.y = 275 - i * 4;
                e++;
            }

            // Wall
            for (int i = 0; i < 125; i++)
            {
                entities[e].position.x = 300;
                entities[e].position.y = 650 - i * 4;
                e++;
            }

            // Wall
            for (int i = 0; i < 120; i++)
            {
                entities[e].position.x = 420;
                entities[e].position.y = 515 - i * 4;
                e++;
            }

            // Wall
            for (int i = 0; i < 60; i++)
            {
                e++;
            }
        }
    }
    else
    {
        int e = 0;

        // Border
        for (int i = 0; i < 153; i++)
        {
            entities[e].position.x = 60;
            entities[e].position.y = 40 + i * 4;
            e++;
        }

        for (int i = 0; i < 153; i++)
        {
            entities[e].position.x = 550;
            entities[e].position.y = 40 + i * 4;
            e++;
        }

        for (int i = 0; i < 122; i++)
        {
            e++;
        }

        for (int i = 0; i < 122; i++)
        {
            e++;
        }

        if (maze == true)
        {
            // Wall
            for (int i = 0; i < 60; i++)
            {
                entities[e].position.x = 180;
                entities[e].position.y = 40 + i * 4;
                e++;
            }

            // Wall
            for (int i = 0; i < 125; i++)
            {
                entities[e].position.x = 300;
                entities[e].position.y = 154 + i * 4;
                e++;
            }

            // Wall
            for (int i = 0; i < 120; i++)
            {
                entities[e].position.x = 420;
                entities[e].position.y = 40 + i * 4;
                e++;
            }

            // Wall
            for (int i = 0; i < 60; i++)
            {
                e++;
            }
        }
    }
}

// Reverses placement direction of walls which don't render correctly when placed with ascending depth with respect to the camera
void world_generator::flip_walls_horizontal(std::vector<entity> &entities, int entity_count, bool inverse)
{
    if (inverse == true)
    {
        int e = 0;

        // Border
        for (int i = 0; i < 153; i++)
        {
            e++;
        }

        for (int i = 0; i < 153; i++)
        {
            e++;
        }

        for (int i = 0; i < 122; i++)
        {
            entities[e].position.x = 550 - i * 4;
            entities[e].position.y = 40;
            e++;
        }

        for (int i = 0; i < 122; i++)
        {
            entities[e].position.x = 550 - i * 4;
            entities[e].position.y = 650;
            e++;
        }

        if (maze == true)
        {
            // Wall
            for (int i = 0; i < 60; i++)
            {
                e++;
            }

            // Wall
            for (int i = 0; i < 125; i++)
            {
                e++;
            }

            // Wall
            for (int i = 0; i < 120; i++)
            {
                e++;
            }

            // Wall
            for (int i = 0; i < 60; i++)
            {
                entities[e].position.x = 300 - i * 4;
                entities[e].position.y = 400;
                e++;
            }
        }
    }
    else
    {
        int e = 0;

        // Border
        for (int i = 0; i < 153; i++)
        {
            e++;
        }

        for (int i = 0; i < 153; i++)
        {
            e++;
        }

        for (int i = 0; i < 122; i++)
        {
            entities[e].position.x = 60 + i * 4;
            entities[e].position.y = 40;
            e++;
        }

        for (int i = 0; i < 122; i++)
        {
            entities[e].position.x = 60 + i * 4;
            entities[e].position.y = 650;
            e++;
        }

        if (maze == true)
        {
            // Wall
            for (int i = 0; i < 60; i++)
            {
                e++;
            }

            // Wall
            for (int i = 0; i < 125; i++)
            {
                e++;
            }

            // Wall
            for (int i = 0; i < 120; i++)
            {
                e++;
            }

            // Wall
            for (int i = 0; i < 60; i++)
            {
                entities[e].position.x = 60 + i * 4;
                entities[e].position.y = 400;
                e++;
            }
        }
    }
}
