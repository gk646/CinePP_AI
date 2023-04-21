//
// Created by Lukas on 21.04.2023.
//

#include "NeuralBuildBlocks.hpp"


double Layer::dot_product(const std::vector<float> &a, const std::vector<float> &b) {
    float result = 0;
    for (std::uint_fast8_t i = a.size(); i >= 0; --i) {
        result += a[i] * b[i];
    }
    return result;
}