//
// Created by Lukas on 18.04.2023.
//

#ifndef CEEU_AI_DATATYPES_HPP
#define CEEU_AI_DATATYPES_HPP
#pragma once

#include <iostream>
#include <tuple>
#include <vector>
#include <string>
#include <unordered_map>
#include <variant>
#include <functional>

template<typename... ColumnTypes>
struct vector_csv {

    using row_types = std::tuple<std::vector<ColumnTypes>...>;

    template<std::size_t ColumnIndex>
    const auto &get_column() const {
        return std::get<ColumnIndex>(data);
    }

    template<std::size_t ColumnIndex>
    const auto &get_column(int index) const {
        return std::get<ColumnIndex>(data)[index];
    }



    std::unordered_map<std::string, std::size_t> columns{};
    row_types data;


};

#endif //CEEU_AI_DATATYPES_HPP
