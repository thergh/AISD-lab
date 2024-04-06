#include <iostream>
#include <vector>
#include "sorting.hpp"

int main(){

    std::cout << "random vector:" << std::endl;
    std::vector<int> z = random(10000);
    // print_vector(z);

    std::cout << "dac_sort:" << std::endl;
    // print_vector(dac_sort(z, true));
    dac_sort(z, true);

    std::cout << "merge_sort:" << std::endl;
    // print_vector(merge_sort(z, true));
    merge_sort(z, true);

    std::cout << "insert_sort:" << std::endl;
    // print_vector(insert_sort(z, true));
    insert_sort(z, true);

    std::cout << "quick_sort:" << std::endl;
    // print_vector(quick_sort(z, true));
    quick_sort(z, true);

    std::cout << "quick_hybrid_sort:" << std::endl;
    // print_vector(quick_hybrid_sort(z, true));
    quick_hybrid_sort(z, true);
    // printing queue

}