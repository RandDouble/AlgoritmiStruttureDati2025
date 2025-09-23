#pragma once

#include <vector>
#include <string>
#include <unordered_map>

#include "map_key.h"

struct Elements{
    int weight{0}, value{0};
};

enum class Mode{
    RECURSIVE,
    STACK
};


int knapsack_solver(
    const std::vector<Elements> & values, int target, const Mode& mode = Mode::RECURSIVE
);

int knapsack_recursive(
    const std::vector<Elements> & values,
    int considered,
    int target,
    std::unordered_map<MapKey, int>& memory
);

int knapsack_with_stack(
    const std::vector<Elements> & values,
    int considered,
    int target,
    std::unordered_map<MapKey, int>& memory
);