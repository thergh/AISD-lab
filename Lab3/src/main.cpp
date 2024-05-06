#include "algorithms.hpp"
#include "util.hpp"
#include <iostream>
#include <algorithm>
#include <vector>
#include <tuple>

int main(int argc, char* argv[]){
    // median_k_test(50000, 1000, 1000, 3, "median_3.txt");
    // std::cout << "3 ready" << std::endl;
    // median_k_test(50000, 1000, 1000, 5, "median_5.txt");
    // std::cout << "5 ready" << std::endl;
    // median_k_test(50000, 1000, 1000, 7, "median_7.txt");
    // std::cout << "7 ready" << std::endl;
    // median_k_test(50000, 1000, 1000, 9, "median_9.txt");
    // std::cout << "9 ready" << std::endl;
    // select_random_test(50000, 1000, 50, "random.txt");

    // search_test(100000, 1000, 10, "search_random.txt");
    // search_test_beg(100000, 1000, 10, "search_beg.txt");
    // search_test_mid(100000, 1000, 10, "search_mid.txt");
    // search_test_end(100000, 1000, 10, "search_end.txt");


    // arguments:
    // 1: algorithm
    // 2: generator
    // 3: size
    // 4: value (position or key)

    if(argc != 5){
        std::cout << "Wrong number of arguments." << std::endl;
        std::cout << "Argument format: 'algorithm' 'generator' 'size' 'value'" << std::endl;
        return 1;
    }

    std::string algorithm = argv[1];
    std::string generator = argv[2];
    int size = atoi(argv[3]);
    int value = atoi(argv[4]);

    std::vector<int> v;

    // generating vector of values
    if(generator == "asc"){
        v = random_asc(size);
    }
    else if(generator == "desc"){
        v = random_desc(size);
    }
    else if(generator == "random"){
        v = random_v(size);
    }
    else{
        std::cout << "Wrong generator. Available choices: 'asc', 'desc', 'random'" << std::endl;
        return 1;
    }

    std::vector<int> starting_vector = v;

    std::tuple<int, int, int, double, double> select_result;
    std::tuple<int, int, double> search_result;


    // activating a proper algorithm
    if(algorithm == "select"){
        select_result = select_random(v, value);
    }
    else if(algorithm == "median"){
        select_result = select_median(v, value, 5);
    }
    else if(algorithm == "search"){
        search_result = binary_search(v, value);
    }
    else{
        std::cout << "Wrong algorithm. Available choices: 'select', 'median', 'search'" << std::endl;
        return 1;
    }

    if(algorithm != "search" and value >= size){
        std::cout<<"Position out of range."<<std::endl;
        return 1;
    }

    if(algorithm == "search"){
        int found = std::get<0>(search_result);
        int comps = std::get<1>(search_result);
        std::cout<<"key found? "<<found<<" number of comparisons: "<<comps<<std::endl;
    }
    else{
        int found = std::get<0>(select_result);
        int comps = std::get<1>(select_result);
        int swaps = std::get<2>(select_result);
        std::cout<<"value on position "<<value<<": "<<found<<" comps: "<<comps<<" swaps: "<<swaps<<std::endl;
        
        if(size < 40){
            std::cout << "starting vector: " << std::endl;
            print_vector(starting_vector);

            std::cout << "end vector: " << std::endl;
            print_vector(v);
        }
    }
}

