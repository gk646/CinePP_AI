#include <iostream>
#include "Util/DataTypes/DataTypes.hpp"
#include "DataImport/DataImport.hpp"


using namespace Cu;

int main() {
    auto tags = new vector_csv<uint_fast16_t, uint_fast32_t, std::string, uint_fast32_t>();
    auto ratings = new vector_csv<uint_fast8_t, uint_fast32_t, float, uint_fast32_t>();
    auto movies = new vector_csv<uint_fast32_t, std::string, std::vector<std::string>>();

    *tags = CSVImport::importCSVByName<uint_fast16_t, uint_fast32_t, std::string, uint_fast32_t>("tags.csv");
    *ratings = CSVImport::importCSVByName<uint_fast8_t, uint_fast32_t, float, uint_fast32_t>("ratings.csv");
    *movies = CSVImport::importCSVByName<uint_fast32_t, std::string, std::vector<std::string>>("movies.csv");

    const auto &column = movies->get_column<1>();
    for (int i = 0;  i < column.size(); ++i) {
        std::cout << column[i] << std::endl;
    }
}
