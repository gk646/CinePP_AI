//
// Created by Lukas on 18.04.2023.
//
#pragma once
#ifndef CEEU_AI_DATAIMPORT_HPP
#define CEEU_AI_DATAIMPORT_HPP

#include "../Util/DataTypes/DataTypes.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

namespace Cu {
    class CSVImport {

    public:
        CSVImport();
        ~CSVImport();


        /**Import file with name / relative to /resources folder*/
        template<typename... ColumnTypes>
        static vector_csv<ColumnTypes...> importCSVByName(const std::string &filename) {
            vector_csv<ColumnTypes...> result;
            std::ifstream file("resources/" + filename);
            std::string line;

            // Read the first line to get column names
            if (std::getline(file, line)) {
                std::stringstream line_stream(line);
                std::string column_name;
                uint_fast8_t index = 0;
                while (std::getline(line_stream, column_name, ',')) {
                    result.columns[column_name] = index++;
                }

            }

            // Process the remaining lines for data parsing
            while (std::getline(file, line)) {
                std::stringstream line_stream(line);
                add_row(result, line_stream);
            }

            return result;
        }

        /** add a row to a existing vector_csv */
        template<typename... ColumnTypes>
        static void add_row(vector_csv<ColumnTypes...> &table, std::stringstream &line_stream) {
            add_row_impl(table, line_stream, std::index_sequence_for<ColumnTypes...>());
        }

        template<typename... ColumnTypes, std::size_t... ColumnIndices>
        static void add_row_impl(vector_csv<ColumnTypes...> &table, std::stringstream &line_stream, std::index_sequence<ColumnIndices...>) {
            std::string cell_str;
            std::tuple<ColumnTypes...> parsed_row;

            // Read and parse each cell
            ((std::getline(line_stream, cell_str, ','),
                    parse<ColumnTypes>(cell_str, std::get<ColumnIndices>(parsed_row))), ...);

            // Append parsed values to the appropriate columns
            ((std::get<ColumnIndices>(table.data).emplace_back(std::get<ColumnIndices>(parsed_row))), ...);
        }


        template<typename T>
        static void parse(const std::string &cell_str, T &output) {
            try {
                if constexpr (std::is_same_v<T, int>) {
                    output = std::stoi(cell_str);
                } else if constexpr (std::is_same_v<T, float>) {
                    output = std::stof(cell_str);
                } else if constexpr (std::is_same_v<T, std::string>) {
                    output = cell_str;
                } else if constexpr (std::is_same_v<T, uint_fast8_t> || std::is_same_v<T, uint_fast32_t> || std::is_same_v<T, uint_fast64_t> ||
                                     std::is_same_v<T, uint_fast16_t>) {
                    unsigned long value = std::stoul(cell_str);
                    output = static_cast<T>(value);
                } else if constexpr (std::is_same_v<T, std::vector<std::string>>) {
                    std::vector<std::string> result;
                    std::istringstream iss(cell_str);
                    std::string token;

                    while (std::getline(iss, token, '|')) {
                        result.emplace_back(token);
                    }
                    output = result;
                }
            } catch (const std::invalid_argument &) {
                std::cout << cell_str;
                output = static_cast<T>(0);
            }

        }

    };
}

#endif //CEEU_AI_DATAIMPORT_HPP
