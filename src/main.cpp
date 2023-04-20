#include <iostream>
#include "Util/DataTypes/DataTypes.hpp"
#include "DataImport/DataImport.hpp"
#include "Util/MathCeeU.hpp"
#include "Query/CeeU.hpp"
#include <chrono>

using namespace Cu;

int main() {
    std::chrono::high_resolution_clock::time_point start_time = std::chrono::high_resolution_clock::now();
    CeeU *ceeUApp = new CeeU("movies.csv", "ratings.csv");
    auto tags = new vector_csv<uint_fast16_t, uint_fast32_t, std::string, uint_fast32_t>();
    auto ratings = new vector_csv<uint_fast16_t, uint_fast32_t, float, uint_fast32_t>();
    auto movies = new vector_csv<uint_fast32_t, std::string, uint_fast16_t, std::vector<std::string>>();

    *tags = CSVImportRAW::importCSVByName<uint_fast16_t, uint_fast32_t, std::string, uint_fast32_t>("tags.csv");
    *ratings = CSVImportRAW::importCSVByName<uint_fast16_t, uint_fast32_t, float, uint_fast32_t>("ratings.csv");
    *movies = CSVImportRAW::importCSVByName<uint_fast32_t, std::string, uint_fast16_t, std::vector<std::string>>("movies.csv");

    Math::printStoppedTime(start_time);

    std::cout << ceeUApp->getBestMovieNameByMovieName("Dangerous Minds");

    Math::printStoppedTime(start_time);

}
