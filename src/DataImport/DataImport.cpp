//
// Created by Lukas on 18.04.2023.
//

#include <vector>
#include <string>
#include "DataImport.hpp"

namespace Cu {
    vector_movie CSVImport::loadMoviesFromCSV(const string &fileName) {
        vector_movie result;
        std::ifstream file("resources/" + fileName);
        std::string line;
        if (std::getline(file, line)) {
            std::stringstream line_stream(line);
            std::string column_name;
            uint_fast8_t index = 0;
            while (std::getline(line_stream, column_name, ';')) {
                result.columns[column_name] = index++;
            }

        }
        // Process the remaining lines for data parsing
        while (std::getline(file, line)) {
            std::stringstream line_stream(line);
            std::string cell;
            std::vector<std::string> cells;

            while (std::getline(line_stream, cell, ';')) {
                cells.push_back(cell);
            }

            uint_fast32_t movieId = std::stoi(cells[0]);
            const std::string &title = cells[1];
            uint_fast16_t year = static_cast<uint_fast16_t>(std::stoi(cells[2]));
            vector<string> genres = parseGenres(cells[3]);

            Movie movie(movieId, title, year, genres);
            result.addMovie(movie);
        }

        return result;
    }

    vector<string> CSVImport::parseGenres(const string &string) {
        std::vector<std::string> result;
        std::istringstream iss(string);
        std::string token;

        while (std::getline(iss, token, '|')) {
            result.emplace_back(token);
        }
        return result;
    }

    vector_rating CSVImport::loadRatingsFromCSV(const string &fileName) {
        vector_rating result;
        std::ifstream file("resources/" + fileName);
        std::string line;
        if (std::getline(file, line)) {
            std::stringstream line_stream(line);
            std::string column_name;
            uint_fast8_t index = 0;
            while (std::getline(line_stream, column_name, ';')) {
                result.columns[column_name] = index++;
            }

        }
        while (std::getline(file, line)) {
            std::stringstream line_stream(line);
            std::string cell;
            std::vector<std::string> cells;

            while (std::getline(line_stream, cell, ';')) {
                cells.push_back(cell);
            }

            uint_fast16_t userId = static_cast<uint_fast16_t>(std::stoi(cells[0]));
            uint_fast32_t movieId = static_cast<uint_fast32_t>(std::stoi(cells[1]));
            float rating_rating = std::stof(cells[2]);
            uint_fast32_t timestamp = static_cast<uint_fast32_t>(std::stoi(cells[3]));

            Rating rating(userId, movieId, rating_rating, timestamp);
            result.addRating(rating);
        }

        return result;
    }
}