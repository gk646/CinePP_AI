//
// Created by Lukas on 21.04.2023.
//

#ifndef CEEU_AI_NEURALNETWORK_HPP
#define CEEU_AI_NEURALNETWORK_HPP
#pragma  once

#include "Parts/NeuralBuildBlocks.hpp"

//std
#include <vector>
#include <cstdint>

enum class ActivationFunction {
    RELU, SIGMOID
};

struct NetworkInitializer {
    NetworkInitializer(const vector<std::uint_fast8_t> &layerSizes, const NeuronInitState &initState, ActivationFunction activationType) : layerSizes(layerSizes),
                                                                                                        initState(initState), activationType(activationType) {};
    vector<std::uint_fast8_t> layerSizes;
    NeuronInitState initState;
    ActivationFunction activationType;
};


class NeuralNetwork {
public:
    NeuralNetwork(std::vector<uint_fast8_t> layer_sizes, NeuronInitState initState, ActivationFunction activationType);

    vector<float> getOutput(const vector<float> &input);

    void backpropagation(const vector<vector<float>> &inputList, const vector<vector<float>> &outputList, double learnRate, int repeatsPerBatch);


private:
    double activationFunction_derivative(double x);
    double activationFunction(double x);
    static double relu(double x) { return max(0.0, x); }
    static double relu_derivative(double x) { return ((x > 0) ? 1 : 0); }
    static double sigmoid(double x) { return 1.0 / (1.0 + exp(-x)); }
    static double sigmoid_derivative(double x) {
        double sigmoid_value = sigmoid(x);
        return sigmoid_value * (1 - sigmoid_value);
    }

    float dot_product(const vector<float> &layerInput, const vector<vector<float>> &weight_matrix);

    vector<vector<float>> forward(const vector<float> &input);
    std::vector<Layer> layers;
    vector<vector<vector<float>>> weight_matrix;
    ActivationFunction activationType;
};

#endif //CEEU_AI_NEURALNETWORK_HPP
