#ifndef CONSTANTS_HXX
#define CONSTANTS_HXX

// TODO: Move some constants out of some classes and pass them as arguments

const int PREY_COUNT = 100;
const int PREDATOR_COUNT = 30;
const double MUTATION_THRESHOLD = 0.3;
const double MUTATION_RATE = 0.5;
const double ENERGY_CONSUMPTION_PREDATOR = 0.01;
const double ENERGY_CONSUMPTION_PREY = 0.001;
const double PREY_REPRODUCTION_RATE = 1.0 / 100;
const double PREDATOR_EAT_REPRODUCTION_RATE = 1.0 / 10;
const double RADIUS = 0.02;
const double PREDATOR_EAT_DISTANCE = RADIUS * 1.2;
const double MAX_MOVEMENT = 0.003;
const double SIGHT_DISTANCE = 0.1;

#endif
