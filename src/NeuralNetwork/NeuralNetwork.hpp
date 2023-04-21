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

class Network {
public:
    Network(std::vector<uint_fast8_t> layer_sizes) {
        for (const auto &size: layer_sizes) {
            layers.push_back(Layer(size));
        }
    }

    std::vector<Layer> layers;
};

#endif //CEEU_AI_NEURALNETWORK_HPP
