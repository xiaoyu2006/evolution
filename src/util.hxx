#ifndef UTIL_HXX
#define UTIL_HXX

#include <random>

// (0,1)
inline double random_double() {
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}

inline double random_double_range(double min, double max) {
    return min + (max - min) * random_double();
}

inline double sigmoid(double x) {
    // R |-> (0,1)
    return 1.0 / (1.0 + exp(-x));
}

inline double sigmoid_extended(double x) {
    // R |-> (-1,1)
    return 2.0 * sigmoid(x / 2.0) - 1.0;
}

#endif
