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
#include <iostream>

NeuralNetwork::NeuralNetwork(vector<uint_fast8_t> layer_sizes, NeuronInitState initState, ActivationFunction activationType) : activationType(
        activationType) {
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
double NeuralNetwork::activationFunction(double x) {
    switch (activationType) {
        case ActivationFunction::RELU:
            return relu(x);
        case ActivationFunction::SIGMOID:
            return sigmoid(x);
    }
}
double NeuralNetwork::activationFunction_derivative(double x) {
    switch (activationType) {
        case ActivationFunction::RELU:
            return relu_derivative(x);
        case ActivationFunction::SIGMOID:
            return sigmoid_derivative(x);
    }
}

vector<float> NeuralNetwork::getOutput(const vector<float> &input) {
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

vector<vector<float>> NeuralNetwork::forward(const vector<float> &input) {
    // Validate input size
    if (input.size() != layers[0].size()) {
        throw std::runtime_error("Input size mismatch.");
    }
    vector<vector<float>> activations;
    vector<float> layer_input = input;

    for (int i = 0; i < layers.size(); ++i) {
        vector<float> layer_output;

        for (Neuron &neuron: layers[i].neurons) {
            float weighted_sum = dot_product(layer_input, weight_matrix[i]) + neuron.bias;
            layer_output.push_back(activationFunction(weighted_sum));
        }
        layer_input = layer_output;
        activations.push_back(layer_input);
    }

    return activations;
}


void NeuralNetwork::backpropagation(const vector<vector<float>> &inputList, const vector<vector<float>> &outputList, double learnRate,
                                    int repeatsPerBatch) {

    for (int i = 0; i < repeatsPerBatch; ++i) {

        for (u8bit inputListIterator = 0; inputListIterator < inputList.size(); inputListIterator++) {
            auto &inputVec = inputList[inputListIterator];


            vector<vector<float>> activations = forward(inputVec);
            vector<float> output = activations.back(); // Get the final output
            vector<float> error{};

            for (u8bit j = 0; j < output.size(); j++) {
                error.push_back(output[j] - outputList.at(inputListIterator).at(j));
            }

            // Iterate over the layers in reverse order
            for (int layerIndex = layers.size() - 1; layerIndex >= 0; layerIndex--) {
                Layer &currentLayer = layers[layerIndex];

                // Calculate the gradient for each neuron in the layer
                for (int neuronIndex = 0; neuronIndex < currentLayer.neurons.size(); neuronIndex++) {
                    Neuron &neuron = currentLayer.neurons[neuronIndex];

                    // Compute the gradient of the loss function with respect to neuron's output

                    double outputGradient = 2 * error[neuronIndex] * activationFunction_derivative(activations[layerIndex][neuronIndex]);

                    // Update the weights and biases of the neuron
                    for (int weightIndex = 0; weightIndex < weight_matrix[layerIndex][neuronIndex].size(); weightIndex++) {
                        double inputForWeight = (layerIndex == 0) ? inputVec[weightIndex] : activations[layerIndex - 1][weightIndex];

                        // Compute the gradient of the loss function with respect to the weight
                        double weightGradient = outputGradient * inputForWeight;

                        // Update the weight using the computed gradient and learning rate
                        weight_matrix[layerIndex][neuronIndex][weightIndex] -= learnRate * weightGradient;
                    }

                    // Update the bias using the computed gradient and learning rate
                    neuron.bias -= learnRate * outputGradient;
                }

                // Update the error for the next layer
                if (layerIndex > 0) {
                    vector<float> new_error(currentLayer.neurons.size(), 0.0);
                    for (int neuronIndex = 0; neuronIndex < currentLayer.neurons.size(); neuronIndex++) {
                        for (int nextNeuronIndex = 0; nextNeuronIndex < layers[layerIndex - 1].neurons.size(); nextNeuronIndex++) {
                            new_error[nextNeuronIndex] += error[neuronIndex] * weight_matrix[layerIndex - 1][nextNeuronIndex][neuronIndex];
                        }
                    }
                    error = new_error;
                }
            }
        }
    }
}



