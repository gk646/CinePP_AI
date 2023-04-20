//
// Created by Lukas on 19.04.2023.
//

#ifndef CEEU_AI_CEEU_HPP
#define CEEU_AI_CEEU_HPP
#pragma  once

#include <string>
#include <random>
#include "../Util/DataTypes/DataTypes.hpp"
#include "../DataImport/DataImport.hpp"

namespace Cu {
    using namespace std;

    class CeeU {
    public:
        CeeU(const string &movieCSV, const string &ratingCSV);
        string getBestMovieNameByMovieName(const string &inputMovieName);

        vector_movie movies;
        vector_rating ratings;

    private:
        int getRandomInt(const int &bounds);
        int getRandomInt(const int &start, const int &end);
        std::mt19937 generator;
        CSVImport csvImport{};
        CSVImportRAW csvImportRaw{};

    };
}
#endif //CEEU_AI_CEEU_HPP
