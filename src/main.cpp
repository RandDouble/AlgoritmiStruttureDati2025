#include <iostream>

#include <random>
#include <vector>

#include <knapsack_solver.h>
#include <test_suite.h>

constexpr int NUM_OF_TESTS = 20;

int main(int argc, char const *argv[])
{
    std::cout << "Knapsack Problem Solver v0.1\n"
              << "============================\n"
              << "Made by Stefano Pilosio\n\n";

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 10000);

    std::vector v_size(NUM_OF_TESTS, 1);
    { // Initialize values with different powers of two
        int count = 0; 
        for (auto &v : v_size)
            v <<= count++;
    }

    // for (const auto &size : v_size)
    // {
    //     test_recursion(size, gen, dis);
    // }
    
    for (const auto &size : v_size)
    {
        test_iterative_stack(size, gen, dis);
    }

    return 0;
}
