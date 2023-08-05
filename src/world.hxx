#ifndef WORLD_HXX
#define WORLD_HXX

class World;

#include <vector>
#include <ray.hxx>
#include <creature.hxx>

class World {
public:
    World(int prey_count, int predator_count);

    ~World();

    void tick();

    Creature *get_nearest_creature(Ray const &ray) const;

    std::string serialize();

    std::vector<Creature *> creatures;

    int tick_count = 0;
};

#endif
