#ifndef NETWORK_HXX
#define NETWORK_HXX

#include <vector>

// A neural network with 1 hidden layer
// Output \in (-1,1)
class Network {
public:
    Network(int input_count, int middle_count, int output_count);

    ~Network();

    std::vector<double> evaluate(std::vector<double> const &inputs) const;

    Network random_alter();

    std::vector<std::vector<double>> weight_input_middle;
    std::vector<double> bias_middle;
    std::vector<std::vector<double>> weight_middle_output;
    std::vector<double> bias_output;
};

#endif
