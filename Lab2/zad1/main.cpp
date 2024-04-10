#include <iostream>
#include <vector>

#include "sorting.hpp"
#include "testing.hpp"


int main(){

    // test_algorithm(quick_sort, random_v, 50000, 1000, 10, "./results/quick_50k.txt");
    // test_algorithm(merge_sort, random_v, 50000, 1000, 10, "./results/merge_50k.txt");
    // test_algorithm(insert_sort, random_v, 50000, 1000, 10, "./results/quick_50k.txt");
    test_algorithm(quick_hybrid_sort, random_v, 50000, 1000, 10, "./results/quick_hybrid_50k.txt");
}