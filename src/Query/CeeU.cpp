//
// Created by Lukas on 19.04.2023.
//

#include "CeeU.hpp"
#include "../Util/MathCeeU.hpp"
#include <random>
#include <queue>

namespace Cu {
    using namespace std;

    CeeU::CeeU(const string &movieCSV, const string &ratingCSV, const NetworkInitializer &netInit) :
            generator(std::random_device{}()), neuralNetwork(NeuralNetwork{netInit.layerSizes, netInit.initState, netInit.activationType}) {

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
        std::unordered_map<uint_fast32_t, std::pair<float, uint_fast16_t>> movie_ratings;

        double highestSimilarity = 0;
        for (const auto &movie: movies.movies) {
            float similarity = Math::getSimilarityOfStringVectors(inputMovie.genres, movie.genres);
            if (similarity > 0 && similarity >= highestSimilarity) {
                movie_ratings[movie.movieId] = {0.0, 0};
                if (similarity > highestSimilarity) {
                    highestSimilarity = similarity;
                }
            }
        }
        for (auto &rating: ratings.ratings) {
            if (movie_ratings.count(rating.movieId)) {
                float old_average = movie_ratings[rating.movieId].first;
                int new_count = ++movie_ratings[rating.movieId].second;
                movie_ratings[rating.movieId] = {old_average + (rating.rating - old_average) / new_count, new_count};
            }
        }

        auto comp = [](const std::pair<uint_fast32_t, float> &a, const std::pair<uint_fast32_t, float> &b) {
            return a.second < b.second;
        };
        std::priority_queue<std::pair<uint_fast32_t, float>, std::vector<std::pair<uint_fast32_t, float>>, decltype(comp)> top_movies(comp);

        for (const auto &pair: movie_ratings) {
            top_movies.emplace(pair.first, pair.second.first);
            if (top_movies.size() > 25) {
                top_movies.pop();
            }
        }

        std::vector<std::pair<uint_fast32_t, float>> top_movies_vec;
        while (!top_movies.empty()) {
            top_movies_vec.push_back(top_movies.top());
            top_movies.pop();
        }

        float highestRating = 0;
        int maxIndex = 0;
        uint_fast8_t size = top_movies_vec.size();
        for (int i = 0; i < size; i++) {
            if (top_movies_vec[i].second >= highestRating) {
                highestRating = top_movies_vec[i].second;
                maxIndex = i;
            } else {
                break;
            }
        }
        return movies.getMovieById(top_movies_vec[getRandomInt(maxIndex)].first).title;
    }
}