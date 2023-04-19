//
// Created by Lukas on 19.04.2023.
//

#include "CeeU.hpp"
#include "../Util/MathCeeU.hpp"
#include <random>

namespace Cu {
    using namespace std;

    CeeU::CeeU(const string &movieCSV, const string &ratingCSV) {
        movies = csvImport.loadMoviesFromCSV(movieCSV);
        ratings = csvImport.loadRatingsFromCSV(ratingCSV);
    }

    int CeeU::getRandomInt(const int &bounds) {
        std::uniform_int_distribution<> distribution(0, bounds);
        return distribution(generator);
    }

    int CeeU::getRandomInt(const int &start, const int &end) {
        std::uniform_int_distribution<> distribution(start, end);
        return distribution(generator);
    }

    string CeeU::getBestMovieNameByMovieName(const string &inputMovieName) {
        Movie inputMovie = movies.getMovieByTitle(inputMovieName);
        std::vector<std::pair<uint_fast32_t, double>> movie_similarities;
        std::vector<std::pair<uint_fast32_t, double>> movie_average_ratings;
        double highestSimilarity = 0;
        for (const auto &movie: movies.movies) {
            double similarity = Math::getSimilarityOfStringVectors(inputMovie.genres, movie.genres);
            if (!(similarity < highestSimilarity)) {
                movie_similarities.emplace_back(movie.movieId, similarity);
                if (similarity > highestSimilarity) {
                    highestSimilarity = similarity;
                }
            }
        }
        if (highestSimilarity == 1) {
            uint_fast8_t size = (movie_similarities.size() < 25) ? movie_similarities.size() : 25;
            for (int i = 0; i < size; ++i) {
                auto &pair = movie_similarities[i];
                if (pair.second == highestSimilarity) {
                    movie_average_ratings.emplace_back(pair.first, ratings.getAverageRatingByMovieId(pair.first));
                }
            }
        } else {
            throw new std::runtime_error("unlucky!");
        }
        std::sort(movie_average_ratings.begin(), movie_average_ratings.end(),
                  [](const std::pair<uint_fast32_t, double> &a, const std::pair<uint_fast32_t, double> &b) {
                      return a.first > b.first;
                  });

        float highestRating = 0;
        uint_fast8_t maxIndex;
        for (int i = 0; i < 10; ++i) {
            if (movie_average_ratings[i].second > highestRating) {
                highestRating = movie_average_ratings[i].second;
            } else {
                maxIndex = i;
                break;
            }
        }

        return movies.getMovieById(movie_average_ratings[getRandomInt(maxIndex)].first).title;
    }
}