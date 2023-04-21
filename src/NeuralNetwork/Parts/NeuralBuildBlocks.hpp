//
// Created by Lukas on 21.04.2023.
//

#ifndef CEEU_AI_NEURALBUILDBLOCKS_HPP
#define CEEU_AI_NEURALBUILDBLOCKS_HPP
#pragma  once

#include <vector>
#include <cstdint>
#include <random>


enum class NeuronInitState {
    ZERO, RANDOM
};
using namespace std;

struct Neuron {
    Neuron() {};

    Neuron(float bias) : bias(bias) {};
    float bias;
};


class Layer {
public:
    Layer(uint_fast8_t size, NeuronInitState state);

    uint_fast8_t size() { return layerSize; }

    uint_fast8_t layerSize;
    vector<Neuron> neurons;
};


#endif //CEEU_AI_NEURALBUILDBLOCKS_HPP
