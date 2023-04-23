# CinePP_AI

CinePP_AI is a C++ based project where i try to apply machine learning to the [MovieLens 100k database](https://grouplens.org/datasets/movielens/). I try to code them from scratch to get a deeper understanding of the algorithms used.

**I modified orignal data** with regex to fit my purpose:  
- changed the delimiter to ";" semicolon (this eliminates the need to parse for "," inside movie titles)
- separated the year in "movies.csv" into its own column (to use it more efficiently)
- filled in some data gaps


#### Goals:
Making a entry level implementation of some machine learning algorithms and principles in C++

- [X] I/O of database files (both raw and in object arrays)
- [X] use normal math to parse the database and find reccommendations (Jaccard Index, Rating sorting)
- [X] basic framework for a neural network
- [X] implement learning methods for the network (back propagation)
- [ ] use the model to give movie reccommendations
- [ ] make a filetype to save and import models
