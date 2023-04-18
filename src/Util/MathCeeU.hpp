//
// Created by Lukas on 18.04.2023.
//

#ifndef CEEU_AI_MATHCEEU_HPP
#define CEEU_AI_MATHCEEU_HPP
#pragma once


#include <string>
#include <vector>

class Math {
public:
    static float getSimilarityOfStringVectors(const std::vector<std::string> first_list, const std::vector<std::string> second_list) {
        float sameItemCount = 0;
        for (const auto &genre: first_list) {
            for (const auto &genre2: second_list) {
                if (genre == genre2) {
                    sameItemCount++;
                    break;
                }
            }
        }
        uint_fast8_t first_length = first_list.size();
        uint_fast8_t second_length = second_list.size();

        return (sameItemCount / ((first_length > second_length) ? first_length : second_length));
    }
};

#endif //CEEU_AI_MATHCEEU_HPP
