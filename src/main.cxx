#include <iostream>
#include <world.hxx>
#include <constants.hxx>

// TODO: LOTS OF REFACTORING
int main(int argc, char **argv) {
    auto world = World(PREY_COUNT, PREDATOR_COUNT);
    for (int i = 0; i < INFINITY; i++) {  // Loop forever
        world.tick();
        std::cout << world.serialize() << std::endl;
    }
    return 0;
}
