//
// Created by Lukas on 21.04.2023.
//

#ifndef CEEU_AI_NEURALBUILDBLOCKS_HPP
#define CEEU_AI_NEURALBUILDBLOCKS_HPP
#pragma  once

#include <vector>
#include <cstdint>


using namespace std;

struct Neuron {
    float bias;
    float activation;
};




class Layer {
public:
    Layer(int size) {
        for (int i = 0; i < size; ++i) {
            neurons.push_back(Neuron{});
        }
    }

    double relu(double x) { return std::max(0.0, x); }

    double dot_product(const std::vector<float>& a, const std::vector<float>& b);
    vector<Neuron> neurons;
};




#endif //CEEU_AI_NEURALBUILDBLOCKS_HPP
