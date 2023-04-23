# CinePP_AI

I did a small python project using tensorflow to make a neural network learn the snake game back at new years.
However, after learning (and liking!) C++ I wanted to revisit and do it from the ground up.

I am using the https://grouplens.org/datasets/movielens/ 100k database as sample data
**However I modified the data** with regex to fit my purpose:  
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
