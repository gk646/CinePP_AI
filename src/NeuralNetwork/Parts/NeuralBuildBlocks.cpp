//
// Created by Lukas on 21.04.2023.
//

#include "NeuralBuildBlocks.hpp"


Layer::Layer(uint_fast8_t layerSize, NeuronInitState state) : layerSize(layerSize) {
    switch (state) {
        case NeuronInitState::ZERO:
            for (int i = 0; i < layerSize; ++i) {
                neurons.emplace_back();
            }
            break;
        case NeuronInitState::RANDOM:
            default_random_engine generator;
            normal_distribution<float> distribution(0.0, 0.1);

            for (int i = 0; i < layerSize; ++i) {
                neurons.emplace_back(distribution(generator));
            }
            break;
    }
}

