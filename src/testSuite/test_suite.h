#pragma once

#include <random>
#include <concepts>
#include <algorithm>

#include <chrono>

#include <knapsack_solver.h>

template <std::uniform_random_bit_generator RNG, typename PDF>
    requires std::invocable<PDF, RNG &>
void test_iterative_stack(std::size_t nr_of_elements, RNG &rng, PDF &pdf)
{
    std::vector<Elements> elements(nr_of_elements);
    for (auto &e : elements)
    {
        e.weight = pdf(rng);
        e.value = pdf(rng);
    }
    const int target = std::accumulate(
                           elements.begin(), elements.end(), 0, [](int sum, const Elements &e)
                           { return sum + e.weight; }) /
                       nr_of_elements;

    const auto start = std::chrono::high_resolution_clock::now();

    const int result = knapsack_solver(elements, target, Mode::STACK);
    const auto end = std::chrono::high_resolution_clock::now();
    const std::chrono::duration<double, std::milli> duration = end - start;

    std::cout << "Iterative with stack expired time for " << nr_of_elements << " elements: " << duration.count() << " ms\n"
              << "Result: " << result << "\n\n";

    return;
}

template <std::uniform_random_bit_generator RNG, typename PDF>
    requires std::invocable<PDF, RNG &>\
void test_recursion(std::size_t nr_of_elements, RNG &rng, PDF &pdf)
{
    std::vector<Elements> elements(nr_of_elements);
    for (auto &e : elements)
    {
        e.weight = pdf(rng);
        e.value = pdf(rng);
    }
    const int target = std::accumulate(
                           elements.begin(), elements.end(), 0, [](int sum, const Elements &e)
                           { return sum + e.weight; }) /
                       nr_of_elements;

    const auto start = std::chrono::high_resolution_clock::now();

    const int result = knapsack_solver(elements, target, Mode::RECURSIVE);
    const auto end = std::chrono::high_resolution_clock::now();
    const std::chrono::duration<double, std::milli> duration = end - start;

    std::cout << "Recursion expired time for " << nr_of_elements << " elements: " << duration.count() << " ms\n"
              << "Result: " << result << "\n\n";

    return;
}
