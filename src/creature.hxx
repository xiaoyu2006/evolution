#ifndef CREATURE_HXX
#define CREATURE_HXX

class Creature;

class TickResult;

#include <vector>
#include <string>

#include <vec2.hxx>
#include <world.hxx>
#include <network.hxx>
#include <ray.hxx>
#include <constants.hxx>

class TickResult {
public:
    TickResult();

    TickResult(std::vector<Creature *> new_creatures, std::vector<Creature *> dead_creatures);

    void combine(TickResult r);

    void free();

    std::vector<Creature *> new_creatures;
    std::vector<Creature *> dead_creatures;
};

class Creature {
public:
    // Check if the creature is dead or reproduces
    // Calculate the new position of the creature
    virtual TickResult tick(World const &world);

    virtual ~Creature() = 0;

    virtual std::string serialize() const = 0;

    virtual Creature *reproduce() = 0;

    virtual std::vector<Ray> get_rays() const = 0;

    inline void move(Vec2 delta) {
        Vec2 new_position = this->position + delta;
        // Wrap around the edges of the world
        if (new_position.x < 0) {
            new_position.x = 1;
        } else if (new_position.x > 1) {
            new_position.x = 0;
        }
        if (new_position.y < 0) {
            new_position.y = 1;
        } else if (new_position.y > 1) {
            new_position.y = 0;
        }
        this->position = new_position;
    }

    Vec2 position = Vec2::random();
    double energy = 1;
    int age = 0;
    double reproduction = 0;
    const double radius = 0.01;
    Network network = Network(0, 0, 0);  // NOTE: Child classes should set this
};

class Prey : public Creature {
public:
    Prey();

    ~Prey() override;

    TickResult tick(World const &world) override;

    Creature *reproduce() override;

    std::string serialize() const override;

    std::vector<Ray> get_rays() const override;
};

class Predator : public Creature {
public:
    Predator();

    ~Predator() override;

    TickResult tick(World const &world) override;

    Creature *reproduce() override;

    std::string serialize() const override;

    std::vector<Ray> get_rays() const override;
};

#endif
