#include <iostream>
#include <vector>
#include "sorting.hpp"

int main(){
    std::cout << "maain" << std::endl;

    std::vector<int> x = random_asc(10);
    std::vector<int> y = random_asc(10);
    std::vector<int> z = random(20);
    print_vector(x);
    print_vector(y);
    print_vector(merge_sorted(x, y));
    std::vector<int> sorted = dac_sort(z);
    std::cout << "sorted vector" << std::endl;
    print_vector(sorted);
    // printing queue

}