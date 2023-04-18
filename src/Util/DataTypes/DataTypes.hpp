//
// Created by Lukas on 18.04.2023.
//

#ifndef CEEU_AI_DATATYPES_HPP
#define CEEU_AI_DATATYPES_HPP
#pragma once

#include <iostream>
#include <tuple>
#include <utility>
#include <vector>
#include <string>
#include <unordered_map>
#include <variant>
#include <functional>

using namespace std;

/** DEPRECATED / realized too late its smarter to just load the data into movie structs
 * but its an interesting approach*/
template<typename... ColumnTypes>
struct vector_csv {

    using row_types = std::tuple<std::vector<ColumnTypes>...>;

    template<std::size_t ColumnIndex>
    const auto &get_column() const {
        return std::get<ColumnIndex>(data);
    }

    template<std::size_t ColumnIndex>
    const auto &get_column(int index) const {
        return std::get<ColumnIndex>(data)[index - 1];
    }

    std::unordered_map<std::string, std::size_t> columns{};
    row_types data;
};


struct Movie {
public:
    Movie(const int_fast32_t movieId, string title, const uint_fast16_t year, const vector<std::string> &genres) : moveId(movieId),
                                                                                                                   title(std::move(title)),
                                                                                                                   year(year), genres(genres) {};

    ~Movie() {};

    const int_fast32_t moveId;
    const string title;
    const uint_fast16_t year;
    const vector<std::string> genres;
};


struct vector_movie {

    Movie getMovieById(const uint_fast32_t movieId) {
        if (movieId < 6000) {
            for (auto &movie: movies) {
                if (movie.moveId == movieId) {
                    return movie;
                }
            }
        } else {
            uint_fast16_t moviesLength = movies.size();
            for (int i = movies.size(); i > 0; --i) {
                auto &movie = movies[i];
                if (movie.moveId == movieId) {
                    return movie;
                }
            }
        }
    }

    Movie getMovieByTitle(const string &movieName) {
        for (auto &movie: movies) {
            if (movie.title == movieName) {
                return movie;
            }
        }
    }

    void addMovie(const int_fast32_t movieId, string title, const uint_fast16_t year, const vector<std::string> &genres) {
        movies.push_back(Movie(movieId, title, year, genres));
    }

    void addMovie(Movie movie) {
        movies.push_back(movie);
    }

    std::unordered_map<string, uint_fast8_t> columns{};
private:
    vector<Movie> movies;
};

struct matrix4x4 {

};
#endif //CEEU_AI_DATATYPES_HPP
