#ifndef WORLD_GENERATOR_H
#define WORLD_GENERATOR_H

#include <entity.h>
#include <assets.h>

class world_generator
{
    public:
        int theme;
        int mission;
        bool maze;
        void generate_world(assets &resources, std::vector<entity> &entities, int entity_count);
        void flip_walls_vertical(std::vector<entity> &entities, int entity_count, bool inverse);
        void flip_walls_horizontal(std::vector<entity> &entities, int entity_count, bool inverse);
        world_generator();

    protected:

    private:
        int wall_count;
        int mob_count;
        bool min_npc_spawned;
};

#endif // WORLD_GENERATOR_H
