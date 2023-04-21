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


struct NetworkInitializer {
    NetworkInitializer(const vector<std::uint_fast8_t> &layerSizes, const NeuronInitState &initState) : layerSizes(layerSizes),
                                                                                                        initState(initState) {};
    vector<std::uint_fast8_t> layerSizes;
    NeuronInitState initState;
};


class NeuralNetwork {
public:
    NeuralNetwork(std::vector<uint_fast8_t> layer_sizes, NeuronInitState initState);

    vector<float> forward_pass(const vector<float> &input);
    vector<float> forward(const vector<float> &input);

    float dot_product(const vector<float> &layerInput, const vector<vector<float>> &weight_matrix);

    double relu(double x) { return max(0.0, x); }

private:
    std::vector<Layer> layers;
    vector<vector<vector<float>>> weight_matrix;
};

#endif //CEEU_AI_NEURALNETWORK_HPP
