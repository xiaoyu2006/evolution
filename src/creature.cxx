#include <creature.hxx>
#include <constants.hxx>
#include <util.hxx>

using std::vector;

const int PREY_RAYS = 10;
const double PREY_RAY_ANGLE = 2 * M_PI / PREY_RAYS;
const int PREDATOR_RAYS = 20;
const double PREDATOR_RAY_ANGLE = 2 * M_PI / PREDATOR_RAYS;

TickResult Creature::tick(World const &world) {
    this->age += 1;
    if (this->energy <= 0) {
        return TickResult(vector<Creature *>(), vector<Creature *>{this});
    }
    if (this->reproduction >= 1.0) {
        this->reproduction -= 1.0;
        Creature *child = this->reproduce();
        return TickResult(vector<Creature *>{child}, vector<Creature *>());
    }
    return {};
}

TickResult::TickResult() {
    this->new_creatures = vector<Creature *>();
    this->dead_creatures = vector<Creature *>();
}

TickResult::TickResult(vector<Creature *> new_creatures, vector<Creature *> dead_creatures)
        : new_creatures(std::move(new_creatures)), dead_creatures(std::move(dead_creatures)) {
}

void TickResult::combine(TickResult r) {
    new_creatures.insert(new_creatures.end(), r.new_creatures.begin(), r.new_creatures.end());
    for (Creature *c: r.dead_creatures) {
        // Only add the creature if it's not already in the list in case of double-free
        if (std::find(dead_creatures.begin(), dead_creatures.end(), c) == dead_creatures.end()) {
            dead_creatures.push_back(c);
        }
    }
}

void TickResult::free() {
    for (Creature *c: dead_creatures) {
        delete c;
    }
}

Creature::~Creature() {
    this->position = Vec2(0, 0);
}

Prey::Prey() {
    this->network = Network(PREY_RAYS, 3, 2);
}

Prey::~Prey()
= default;

TickResult Prey::tick(World const &world) {
    this->energy -= ENERGY_CONSUMPTION_PREY;
    this->reproduction += random_double_range(0, PREY_REPRODUCTION_RATE);
    auto result = Creature::tick(world);
    auto rays = this->get_rays();
    vector<double> inputs;
    for (auto &r: rays) {
        auto nearest_creature = world.get_nearest_creature(r);
        if (nearest_creature != nullptr) {
            double distance = this->position.dist(nearest_creature->position);
            if (distance > SIGHT_DISTANCE) {
                distance = SIGHT_DISTANCE;
            }
            inputs.push_back(distance);
        } else {
            inputs.push_back(SIGHT_DISTANCE);
        }
    }
    auto network_output = this->network.evaluate(inputs);
    Vec2 movement = {network_output[0], network_output[1]};
    movement = movement * MAX_MOVEMENT;
    this->move(movement);
    result.combine(TickResult(vector<Creature *>(), vector<Creature *>()));
    return result;
}

Creature *Prey::reproduce() {
    auto result = new Prey();
    result->position = this->position + Vec2::random() * 0.03;
    result->network = this->network.random_alter();
    return result;
}

std::string Prey::serialize() const {
    return "Prey," + this->position.serialize();
}

std::vector<Ray> Prey::get_rays() const {
    std::vector<Ray> rays;
    for (int i = 0; i < PREY_RAYS; i++) {
        double angle = i * PREY_RAY_ANGLE;
        Vec2 direction = Vec2::from_angle(angle);
        Ray ray = Ray(this, this->position, direction);
        rays.push_back(ray);
    }
    return rays;
}

Predator::Predator() {
    this->energy = 3.0;
    this->network = Network(PREDATOR_RAYS, 4, 2);
    for (int i = 0; i < 20; i++) {
        this->network = this->network.random_alter(); // More randomization
    }
}

Predator::~Predator()
= default;

TickResult Predator::tick(World const &world) {
    this->energy -= ENERGY_CONSUMPTION_PREDATOR;
    auto result = Creature::tick(world);
    auto rays = this->get_rays();
    vector<double> inputs;
    for (auto &r: rays) {
        auto nearest_creature = world.get_nearest_creature(r);
        if (nearest_creature != nullptr) {
            double distance = this->position.dist(nearest_creature->position);
            if (distance > SIGHT_DISTANCE) {
                distance = SIGHT_DISTANCE;
            }
            inputs.push_back(distance);
        } else {
            inputs.push_back(SIGHT_DISTANCE);
        }
    }
    auto network_output = this->network.evaluate(inputs);
    Vec2 movement = {network_output[0], network_output[1]};
    movement = movement * MAX_MOVEMENT;
    this->move(movement);
    result.combine(TickResult(vector<Creature *>(), vector<Creature *>()));
    for (Creature *c: world.creatures) {
        Prey *p = dynamic_cast<Prey *>(c);
        if (p != nullptr) {
            if (this->position.dist(p->position) < PREDATOR_EAT_DISTANCE) {
                this->energy += p->energy;
                result.dead_creatures.push_back(p);
                this->reproduction += random_double_range(0, PREDATOR_EAT_REPRODUCTION_RATE);
            }
        }
    }
    return result;
}

Creature *Predator::reproduce() {
    auto result = new Predator();
    result->position = this->position + Vec2::random() * 0.03;
    result->network = this->network.random_alter();
    result->energy = this->energy / 2.0;
    this->energy /= 2.0;
    return result;
}

std::string Predator::serialize() const {
    return "Predator," + this->position.serialize();
}

std::vector<Ray> Predator::get_rays() const {
    std::vector<Ray> rays;
    for (int i = 0; i < PREDATOR_RAYS; i++) {
        double angle = i * PREDATOR_RAY_ANGLE;
        Vec2 direction = Vec2::from_angle(angle);
        Ray ray = Ray(this, this->position, direction);
        rays.push_back(ray);
    }
    return rays;
}
