#include <iostream>
#include <vector>

#include "sorting.hpp"
#include "testing.hpp"

enum Algorithm{quick, merge, dac, hybrid, insert, dual};

int main(int argc, char* argv[]){

    // test_algorithm(insert_sort, random_v, 10000, 1000, 10, "./results/insert_10k.txt");
    // test_algorithm(quick_sort, random_v, 50000, 1000, 10, "./results/quick_50k.txt");
    // test_algorithm(quick_hybrid_sort, random_v, 50000, 1000, 10, "./results/hybrid_50k.txt");
    // test_algorithm(merge_sort, random_v, 50000, 1000, 10, "./results/merge_50k.txt");
    // test_algorithm(dac_sort, random_v, 50000, 1000, 10, "./results/dac_50k.txt");
    // test_algorithm(dual_pivot_quick_sort, random_v, 50000, 1000, 10, "./results/dual_50k.txt");

    std::vector<int> v;
    std::string name;
    std::string algorithm = argv[1];
    std::string generator = argv[2];

    int size = atoi(argv[3]);
    int comps;
    int swaps;

    std::tuple<std::vector<int>, int, int, double, double> t;


    if(generator ==  "asc"){
        v = random_asc(size);
    }
    else if(generator ==  "desc"){
        v = random_desc(size);
    }
    else{
        v = random_v(size);
    }

    std::vector<int> starting_vector = v;

    if(algorithm == "merge"){
        name = "merge sort";
        t = merge_sort(v);
    }
    else if(algorithm == "insert"){
        name = "insert sort";
        t = insert_sort(v);
    }    
    else if(algorithm == "dual"){
        name = "dual pivot quick sort";
        t = quick_sort(v);
    }
    else if(algorithm == "hybrid"){
        name = "hybrid quick sort";
        t = quick_hybrid_sort(v);
    }
    else if(algorithm == "dac"){
        name = "custom divide and conquer sort";
        t = dac_sort(v);
    }
    else{
        name = "quick sort";
        t = quick_sort(v);
    }

    comps = std::get<1>(t);
    swaps = std::get<2>(t);
    v = std::get<0>(t);

    // printing results
    std::cout << "vector sorted using " << name << std::endl;

    if(size < 40){
        std::cout << "starting vector: " << std::endl;
        print_vector(starting_vector);

        std::cout << "sorted vector: " << std::endl;
        print_vector(v);
    }
    
    std::cout << "comparisons: " << comps << "\tswaps: " << swaps << "\n" << std:: endl;
}