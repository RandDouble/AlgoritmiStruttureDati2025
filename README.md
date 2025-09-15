# AlgoritmiStruttureDati2025
---

Project made by [Stefano Pilosio](stefano.pilosio@studenti.unimi.it).

## Target

Pass the exam of Algorithm and Data Structure for Data Physics.

This project aims to create a solver for the [knapsack problem 0-1](https://en.wikipedia.org/wiki/Knapsack_problem).
The proposed solution uses dynamic programming combined with recursion to achieve pseudopolinomial complexity.

The first problem observed was that online solutions use a matrix to contain memoised results, this approach wastes a lot of space, because many entri.
The proposed solution uses dynamic programming combined with recursion to achieve pseudopolinomial complexity.

The first problem observed was that online solutions use a matrix to contain memoised results, this approach wastes a lot of space, because many entries of the matrix are never computed, but must be allocated.
So I replaced the matrix with an hash map. Even this approach is not optimal, because many entries of the hash map are redundant.

After that the second problem encountered was that the recursion was limited by Recursion Depth in Python, and stack overflow in C++, so i used a stack to simulate recursion.

