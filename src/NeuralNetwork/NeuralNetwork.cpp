//
// Created by Lukas on 21.04.2023.
//

#include "NeuralNetwork.hpp"


#include <vector>
#include <cstdint>

using namespace std;

typedef uint_fast8_t u8bit;
typedef uint_fast16_t u16bit;
typedef uint_fast32_t u32bit;


#include <random>
#include <stdexcept>

NeuralNetwork::NeuralNetwork(vector<uint_fast8_t> layer_sizes, NeuronInitState initState) {
    default_random_engine generator;
    normal_distribution<float> distribution(0.0, 0.1);

    u8bit layerCount = layer_sizes.size();
    for (int i = 0; i < layerCount; i++) {
        layers.emplace_back(layer_sizes[i], initState);

        vector<vector<float>> layer_weights(layer_sizes[i], vector<float>(layer_sizes[i + 1]));

        for (int j = 0; j < layer_sizes[i]; j++) {
            for (int k = 0; k < layer_sizes[i + 1]; k++) {
                layer_weights[j][k] = distribution(generator);
            }
        }
        weight_matrix.push_back(layer_weights);
    }
}


float NeuralNetwork::dot_product(const vector<float> &a, const vector<vector<float>> &b) {
    float result = 0;
    for (std::uint_fast8_t i = 0; i < a.size(); i++) {
        for (std::uint_fast8_t j = 0; j < b.size(); j++) {
            result += a[i] * b[j][i];
        }
    }
    return result;
}


vector<float> NeuralNetwork::forward_pass(const vector<float> &input) {
    // Validate input size
    if (input.size() != layers[0].size()) {
        throw std::runtime_error("Input size mismatch.");
    }

    vector<float> layer_input = input;

    for (int i = 0; i < layers.size(); ++i) {
        vector<float> layer_output;

        for (Neuron &neuron: layers[i].neurons) {
            float weighted_sum = dot_product(layer_input, weight_matrix[i]) + neuron.bias;
            layer_output.push_back(relu(weighted_sum));
        }
        layer_input = layer_output;
    }

    return layer_input;
}

vector<float> NeuralNetwork::forward(const vector<float> &input) {
    // Validate input size
    if (input.size() != layers[0].size()) {
        throw std::runtime_error("Input size mismatch.");
    }

    vector<float> layer_input = input;

    // Forward pass through the network
    for (size_t i = 0; i < weight_matrix.size(); ++i) {
        vector<float> layer_output(layers[i + 1].size(), 0.0);

        for (size_t j = 0; j < weight_matrix[i].size(); ++j) {
            for (size_t k = 0; k < weight_matrix[i][j].size(); ++k) {
                layer_output[k] += layer_input[j] * weight_matrix[i][j][k];
            }
        }

        // Add biases and apply activation function
        for (size_t j = 0; j < layer_output.size(); ++j) {
            //layer_output[j] += bias_matrix[i][j];
            //layer_output[j] = activationFunction(layer_output[j]);
        }

        layer_input = layer_output;
    }

    return layer_input;
}


