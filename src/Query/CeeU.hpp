//
// Created by Lukas on 19.04.2023.
//

#ifndef CEEU_AI_CEEU_HPP
#define CEEU_AI_CEEU_HPP
#pragma  once

#include <string>
#include "../Util/DataTypes/DataTypes.hpp"
#include "../DataImport/DataImport.hpp"

namespace Cu {
    using namespace std;

    class CeeU {
    public:
        CeeU(string &movieCSV);
        string getMovieReccommendationByName(string &name);


    private:
        CSVImport csvImport{};
        CSVImportRAW csvImportRaw{};
        vector_movie movies;
    };
}
#endif //CEEU_AI_CEEU_HPP
