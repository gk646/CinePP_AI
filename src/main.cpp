#include <iostream>
#include "Util/DataTypes/DataTypes.hpp"
#include "DataImport/DataImport.hpp"
#include "Util/MathCeeU.hpp"
#include "Query/CeeU.hpp"
#include <chrono>

using namespace Cu;

int main() {
    std::chrono::high_resolution_clock::time_point start_time = std::chrono::high_resolution_clock::now();

    NetworkInitializer netInit{{3, 3, 3, 3}, NeuronInitState::RANDOM, ActivationFunction::SIGMOID};
    NeuralNetwork neuralNetwork{netInit.layerSizes, netInit.initState, ActivationFunction::SIGMOID};
    CeeU *ceeUApp = new CeeU("movies.csv", "ratings.csv", netInit);

    auto tags = new vector_csv<uint_fast16_t, uint_fast32_t, std::string, uint_fast32_t>();
    auto ratings = new vector_csv<uint_fast16_t, uint_fast32_t, float, uint_fast32_t>();
    auto movies = new vector_csv<uint_fast32_t, std::string, uint_fast16_t, std::vector<std::string>>();

    *tags = CSVImportRAW::importCSVByName<uint_fast16_t, uint_fast32_t, std::string, uint_fast32_t>("tags.csv");
    *ratings = CSVImportRAW::importCSVByName<uint_fast16_t, uint_fast32_t, float, uint_fast32_t>("ratings.csv");
    *movies = CSVImportRAW::importCSVByName<uint_fast32_t, std::string, uint_fast16_t, std::vector<std::string>>("movies.csv");


    std::cout << ceeUApp->getBestMovieNameByMovieName("Dangerous Minds");

    Math::printStoppedTime(start_time);

    for (auto &num: neuralNetwork.getOutput({1, 1, 1})) {
        cout << num << "|";
    }
    vector<vector<float>> input = {{1, 1, 0},
                                   {1, 0, 0},
                                   {0, 1, 1},
                                   {1, 0, 0},
                                   {0, 1, 0},
                                   {1, 1, 0},
                                   {1, 0, 0},
                                   {0, 1, 1},
                                   {1, 0, 0},
                                   {0, 1, 0}};
    vector<vector<float>> targetOutput = {{0, 1, 0},
                                          {0, 1, 0},
                                          {0, 0, 0},
                                          {0, 1, 0},
                                          {0, 0, 0},
                                          {0, 1, 0},
                                          {0, 1, 0},
                                          {0, 0, 0},
                                          {0, 1, 0},
                                          {0, 0, 0}};

    for (int i = 0; i < 100; ++i) {
        neuralNetwork.backpropagation(input, targetOutput, 0.3, 100);

        cout << "\n";
        for (auto &num: neuralNetwork.getOutput({1, 1, 1})) {
            cout << num << "|";
        }
    }


    Math::printStoppedTime(start_time);

}
