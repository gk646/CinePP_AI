cmake_minimum_required(VERSION 3.24)
project(CeeU_AI)

set(CMAKE_CXX_STANDARD 23)

add_executable(CeeU_AI src/main.cpp src/DataImport/DataImport.cpp src/DataImport/DataImport.hpp src/Util/MathCeeU.hpp src/Util/DataTypes/DataTypes.hpp src/Query/CeeU.cpp src/Query/CeeU.hpp src/NeuralNetwork/NeuralBuildBlocks.hpp src/NeuralNetwork/NeuralNetwork.cpp src/NeuralNetwork/NeuralNetwork.hpp src/NeuralNetwork/NeuralBuildBlocks.cpp)
