#include <iostream>
#include "Util/DataTypes/DataTypes.hpp"
#include "DataImport/DataImport.hpp"
#include "Util/MathCeeU.hpp"
#include "Query/CeeU.hpp"
using namespace Cu;

int main() {
    CeeU ceeUApp{};
    auto tags = new vector_csv<uint_fast16_t, uint_fast32_t, std::string, uint_fast32_t>();
    auto ratings = new vector_csv<uint_fast8_t, uint_fast32_t, float, uint_fast32_t>();
    auto movies = new vector_csv<uint_fast32_t, std::string, uint_fast16_t, std::vector<std::string>>();

    *tags = CSVImportRAW::importCSVByName<uint_fast16_t, uint_fast32_t, std::string, uint_fast32_t>("tags.csv");
    *ratings = CSVImportRAW::importCSVByName<uint_fast8_t, uint_fast32_t, float, uint_fast32_t>("ratings.csv");
    *movies = CSVImportRAW::importCSVByName<uint_fast32_t, std::string, uint_fast16_t, std::vector<std::string>>("movies.csv");

    const auto &column = movies->get_column<3>(3);
    const auto &column2 = movies->get_column<3>(4);

    std::cout << Math::getSimilarityOfStringVectors(column, column2);
}
