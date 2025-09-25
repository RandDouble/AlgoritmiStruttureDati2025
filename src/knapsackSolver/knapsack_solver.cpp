#include "knapsack_solver.h"

#include <cassert>
#include <stack>
#include <stdexcept>

int knapsack_solver(const std::vector<Elements> &values, int target, const Mode &mode)
{
    std::unordered_map<MapKey, int> memory;
    switch (mode)
    {
    case Mode::RECURSIVE:
        return knapsack_recursive(values, values.size(), target, memory);
    case Mode::STACK:
        return knapsack_with_stack(values, values.size(), target, memory);
    default:
        throw std::invalid_argument("Invalid mode");
        break;
    }
}

int knapsack_recursive(const std::vector<Elements> &values, int considered, int target,
                       std::unordered_map<MapKey, int> &memory)
{

    if (target <= 0 || considered <= 0)
    {
        memory.emplace(MapKey(considered, target), 0);
        return 0;
    }

    const int el_idx = considered - 1;

    if (memory.find({considered, target}) == memory.end())
    {
        // This should calculate memory[considered - 1, values ]
        knapsack_recursive(values, considered - 1, target, memory);
    }

    if (values[el_idx].weight > target)
    {
        memory.emplace(MapKey(considered, target), memory[{considered - 1, target}]);
    }
    else
    {
        memory.emplace(MapKey(considered, target),
                       std::max(memory[{considered - 1, target}],
                                values[el_idx].value + knapsack_recursive(values, considered - 1,
                                                                          target - values[el_idx].weight, memory)));
    }
    return memory[{considered, target}];
}

int knapsack_with_stack(const std::vector<Elements> &values, int considered, int target,
                        std::unordered_map<MapKey, int> &memory)
{
    if (considered <= 0 || target <= 0)
    {
        throw std::invalid_argument("Number of elements considered and target must be greater than 0");
    }
    std::stack<MapKey> stack;
    stack.emplace(considered, target);

    while (!stack.empty())
    {
        const auto considered_now = stack.top().considered;
        const auto target_now = stack.top().target;

        if (target_now <= 0 || considered_now <= 0)
        {
            memory.emplace(MapKey(considered_now, target_now), 0);
            stack.pop();
            continue;
        }

        const int el_idx = considered_now - 1;

        if (memory.find({considered_now, target_now}) == memory.end())
        {
            memory.emplace(MapKey(considered_now, target_now), -1);
            // Mark as being processed
            //  This should calculate memory[considered - 1, values ]
            stack.emplace(considered_now - 1, target_now);
            // Add dependency to stack, with higher priority
            continue;
        }

        if (values[el_idx].weight > target_now)
        {
            assert((memory.find({considered_now - 1, target_now}) != memory.end()) && "Dependency not resolved");
            memory[{considered_now, target_now}] = memory[{considered_now - 1, target_now}];
        }
        else
        {

            if (memory.find({considered_now - 1, target_now - values[el_idx].weight}) == memory.end())
            {
                stack.emplace(considered_now - 1, target_now - values[el_idx].weight);
                continue;
                // Add dependency to stack
            }

            assert((memory[{considered_now - 1, target_now}] != -1) && "Dependency not resolved");
            assert((memory[{considered_now - 1, target_now - values[el_idx].weight}] != -1) &&
                   "Dependency not resolved");

            memory[{considered_now, target_now}] =
                std::max(memory[{considered_now - 1, target_now}],
                         values[el_idx].value + memory[{considered_now - 1, target_now - values[el_idx].weight}]);
        }
        stack.pop();
        // Fine Loop
    }

    return memory[{considered, target}];
}
