#include <network.hxx>

#include <util.hxx>
#include <constants.hxx>

const double INITIAL_RANDOM_RANGE = 0.05;

Network::Network(int input_count, int middle_count, int output_count) {
    this->weight_input_middle = std::vector<std::vector<double>>(input_count, std::vector<double>(middle_count));
    this->weight_middle_output = std::vector<std::vector<double>>(middle_count, std::vector<double>(output_count));
    this->bias_middle = std::vector<double>(middle_count);
    this->bias_output = std::vector<double>(output_count);

    for (int i = 0; i < input_count; i++) {
        for (int j = 0; j < middle_count; j++) {
            this->weight_input_middle[i][j] = random_double_range(-INITIAL_RANDOM_RANGE, INITIAL_RANDOM_RANGE);
        }
    }

    for (int i = 0; i < middle_count; i++) {
        for (int j = 0; j < output_count; j++) {
            this->weight_middle_output[i][j] = random_double_range(-INITIAL_RANDOM_RANGE, INITIAL_RANDOM_RANGE);
        }
    }

    for (int i = 0; i < middle_count; i++) {
        this->bias_middle[i] = random_double_range(-INITIAL_RANDOM_RANGE, INITIAL_RANDOM_RANGE);
    }

    for (int i = 0; i < output_count; i++) {
        this->bias_output[i] = random_double_range(-INITIAL_RANDOM_RANGE, INITIAL_RANDOM_RANGE);
    }
}

std::vector<double> Network::evaluate(std::vector<double> const &inputs) const {
    // Compute middle layer
    std::vector<double> middle(this->weight_input_middle[0].size());
    for (int i = 0; i < this->weight_input_middle[0].size(); i++) {
        middle[i] = 0;
        for (int j = 0; j < this->weight_input_middle.size(); j++) {
            middle[i] += inputs[j] * this->weight_input_middle[j][i];
        }
    }

    for (int i = 0; i < this->bias_middle.size(); i++) {
        middle[i] += this->bias_middle[i];
        middle[i] = sigmoid_extended(middle[i]);
    }

    // Compute output layer
    std::vector<double> output(this->weight_middle_output[0].size());
    for (int i = 0; i < this->weight_middle_output[0].size(); i++) {
        output[i] = 0;
        for (int j = 0; j < this->weight_middle_output.size(); j++) {
            output[i] += middle[j] * this->weight_middle_output[j][i];
        }
    }

    for (int i = 0; i < this->bias_output.size(); i++) {
        output[i] += this->bias_output[i];
        output[i] = sigmoid_extended(output[i]);
    }

    return output;
}

Network Network::random_alter() {
    Network altered = Network(this->weight_input_middle.size(), this->weight_input_middle[0].size(),
                              this->weight_middle_output[0].size());

    for (int i = 0; i < this->weight_input_middle.size(); i++) {
        for (int j = 0; j < this->weight_input_middle[0].size(); j++) {
            if (random_double() < MUTATION_THRESHOLD) {
                altered.weight_input_middle[i][j] =
                        this->weight_input_middle[i][j] + random_double_range(-MUTATION_RATE, MUTATION_RATE);
            } else {
                altered.weight_input_middle[i][j] = this->weight_input_middle[i][j];
            }
        }
    }

    for (int i = 0; i < this->weight_middle_output.size(); i++) {
        for (int j = 0; j < this->weight_middle_output[0].size(); j++) {
            if (random_double() < MUTATION_THRESHOLD) {
                altered.weight_middle_output[i][j] =
                        this->weight_middle_output[i][j] + random_double_range(-MUTATION_RATE, MUTATION_RATE);
            } else {
                altered.weight_middle_output[i][j] = this->weight_middle_output[i][j];
            }
        }
    }

    for (int i = 0; i < this->bias_middle.size(); i++) {
        if (random_double() < MUTATION_THRESHOLD) {
            altered.bias_middle[i] = this->bias_middle[i] + random_double_range(-MUTATION_RATE, MUTATION_RATE);
        } else {
            altered.bias_middle[i] = this->bias_middle[i];
        }
    }

    for (int i = 0; i < this->bias_output.size(); i++) {
        if (random_double() < MUTATION_THRESHOLD) {
            altered.bias_output[i] = this->bias_output[i] + random_double_range(-MUTATION_RATE, MUTATION_RATE);
        } else {
            altered.bias_output[i] = this->bias_output[i];
        }
    }

    return altered;
}

Network::~Network()
= default;
