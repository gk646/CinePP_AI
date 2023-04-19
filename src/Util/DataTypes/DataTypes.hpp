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
    Movie(const uint_fast32_t movieId, string title, const uint_fast16_t year, const vector<std::string> &genres) : movieId(movieId),
                                                                                                                    title(std::move(title)),
                                                                                                                    year(year), genres(genres) {};

    ~Movie() {};

    const uint_fast32_t movieId;
    const string title;
    const uint_fast16_t year;
    const vector<std::string> genres;
};

struct Rating {
public:
    Rating(const uint_fast16_t userId, const uint_fast32_t movieId, const float rating, const uint_fast32_t timestamp) : userId(userId),
                                                                                                                         movieId(movieId),
                                                                                                                         rating(rating),
                                                                                                                         timestamp(timestamp) {};

    ~Rating() {};

    const uint_fast16_t userId;
    const uint_fast16_t movieId;
    const float rating;
    const uint_fast32_t timestamp;
};


struct vector_movie {


    Movie getMovieById(const uint_fast32_t movieId) {
        if (movieId < 6000) {
            for (auto &movie: movies) {
                if (movie.movieId == movieId) {
                    return movie;
                }
            }
        } else {
            for (int i = movies.size(); i > 0; --i) {
                auto &movie = movies[i];
                if (movie.movieId == movieId) {
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
        throw std::runtime_error("Movie not found");
    }

    void addMovie(const int_fast32_t movieId, string title, const uint_fast16_t year, const vector<std::string> &genres) {
        movies.push_back(Movie(movieId, title, year, genres));
    }

    void addMovie(Movie movie) {
        movies.push_back(movie);
    }

    std::unordered_map<string, uint_fast8_t> columns{};
    vector<Movie> movies;
private:

};

struct vector_rating {
    float getAverageRatingByMovieId(const uint_fast32_t movieId) {
        float totalRating = 0;
        uint_fast16_t totalCount = 0;
        for (const auto &rating: ratings) {
            if (rating.movieId == movieId) {
                totalRating += rating.rating;
                totalCount++;
            }
        }
        return totalRating / totalCount;
    }

    vector<float> getRatingsByUserId(const uint_fast16_t &userId) {
        vector<float> result;
        bool isUserIdFound = false;
        if (userId < 307) {
            for (const auto &rating: ratings) {
                if (rating.userId == userId) {
                    result.push_back(rating.rating);
                }
            }
        }
        return result;
    }

    vector<float> getRatingsByMovieId(const uint_fast32_t &movieId) {
        vector<float> result;
        for (const auto &rating: ratings) {
            if (rating.movieId == movieId) {
                result.push_back(rating.rating);
            }
        }
        return result;
    }

    void addRating(const int_fast16_t userId, const uint_fast32_t year, const float rating, const uint_fast32_t timestamp) {
        ratings.push_back(Rating(userId, year, rating, timestamp));
    }

    void addRating(Rating rating) {
        ratings.push_back(rating);
    }

    std::unordered_map<string, uint_fast8_t> columns{};
    vector<Rating> ratings;
private:

};

struct matrix4x4 {

};
#endif //CEEU_AI_DATATYPES_HPP
