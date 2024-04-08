#include "sorting.hpp"


#include "sorting.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <tuple>
#include <vector>

void to_file(std::tuple<std::vector<int>, int, int, double, double>,
 std::string output_path) {
  std::ofstream outfile;
  outfile.open(output_path, std::ios_base::app); // append instead of overwrite
  outfile << "Data"; 
}


std::tuple<double, double, double, double> avg_results(
    std::tuple<std::vector<int>, int, int, double, double> (*sorting_funct)(std::vector<int> input, bool verbose),
    std::vector<int> (*random_gen)(int size),
    int reps, std::string output_path){
        
    int n = 1000;
    long comps_sum = 0;
    long swaps_sum = 0;
    long cn_sum = 0;
    long sn_sum = 0;

    double comps_avg = 0;
    double swaps_avg = 0;
    double cn_avg = 0;
    double sn_avg = 0;

    std::vector<int> v;
    std::tuple<std::vector<int>, int, int, double, double> result;

    for(int i=0; i<reps; i++){
        v = random_gen(n);
        result = insert_sort(v);
        comps_sum += std::get<1>(result);
        swaps_sum += std::get<2>(result);
        cn_sum += std::get<3>(result);
        sn_sum += std::get<4>(result);
    }

    comps_avg = (double)comps_sum / (double)reps;
    swaps_avg = (double)swaps_sum / (double)reps;
    cn_avg = (double)cn_sum / reps;
    sn_avg = (double)sn_sum / reps;

    return std::tuple<double, double, double, double>{comps_avg, swaps_avg, cn_avg, sn_avg};
}
// void insert_test(int n, std::vector<int)