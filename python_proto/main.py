#!/usr/bin/python3

import function as fn

import time
import sys
import random

def mean(values : list[fn.Elements]) -> int:
    return sum(v.value for v in values) // len(values) if values else 0

def main():
    items = [
        fn.Elements(weight=2, value=3),
        fn.Elements(weight=3, value=4),
        fn.Elements(weight=4, value=5),
        fn.Elements(weight=5, value=6),
    ]
    max_value = fn.knapsack_solver(items, 5)
    print(f"Maximum value in knapsack: {max_value}")
    
    random.seed(42)
   
    nr_of_elements_prog = [1 << i for i in range(0, 10)]
   
    print('Starting timing')

    for nr_elements in nr_of_elements_prog:
        items = [fn.Elements(weight=random.randint(1, 10), value=random.randint(1, 10)) for _ in range(nr_elements)]
        start_time = time.perf_counter()
        rec_res : int = fn.knapsack_solver(items, mean(items))
        end_time = time.perf_counter()
        print(f"Elements: {nr_elements}, Time: {end_time - start_time:.6f} seconds")
        start_time = time.perf_counter()
        stack_res = fn.knapsack_solver(items, mean(items), mode='stack')
        end_time = time.perf_counter()
        print(f"Elements: {nr_elements}, Time with stack: {end_time - start_time:.6f} seconds")
        assert rec_res == stack_res, f"Results do not match: {rec_res} != {stack_res}"

    nr_of_elements_prog = [1 << i for i in range(10, 20)]
    
    for nr_elements in nr_of_elements_prog:
        start_time = time.perf_counter()
        stack_res = fn.knapsack_solver(items, mean(items), mode='stack')
        end_time = time.perf_counter()
        print(f"Elements: {nr_elements}, Time with stack: {end_time - start_time:.6f} seconds")


    return 0

if __name__ == "__main__":
    sys.exit(main())