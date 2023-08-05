#include <world.hxx>
#include <string>

using std::optional;
using std::nullopt;
using std::string;

World::World(int prey_count, int predator_count) {
    for (int i = 0; i < prey_count; i++) {
        creatures.push_back(new Prey());
    }
    for (int i = 0; i < predator_count; i++) {
        creatures.push_back(new Predator());
    }
}

World::~World() {
    for (auto c: creatures) {
        delete c;
    }
}

void World::tick() {
    TickResult result = TickResult();
    for (auto c: creatures) {
        TickResult r = c->tick(*this);
        result.combine(r);
    }
    for (auto c: result.dead_creatures) {
        creatures.erase(std::remove(creatures.begin(), creatures.end(), c), creatures.end());
    }
    for (auto c: result.new_creatures) {
        creatures.push_back(c);
    }
    result.free();
    this->tick_count++;
}

string World::serialize() {
    string result = std::to_string(this->tick_count) + "\n";
    for (auto c: creatures) {
        result += c->serialize() + "\n";
    }
    return result;
}

Creature *World::get_nearest_creature(const Ray &ray) const {
    Creature *result = nullptr;
    double min_t = INFINITY;
    for (auto c: creatures) {
        if (c == ray.creature) {
            continue;
        }
        double t = ray.collide_with_circle(c->position, c->radius);
        if (t != Ray::NO_COLLISION && t < min_t) {
            min_t = t;
            result = c;
        }
    }
    return result;
}
