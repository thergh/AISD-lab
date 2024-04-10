#include "sorting.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <tuple>

std::tuple<double, double, double, double> calc_avg_results(
    std::tuple<std::vector<int>, int, int, double, double> (
        *sorting_funct)(std::vector<int> input, bool verbose),
    std::vector<int> (*random_gen)(int size),
    int n, int reps, std::string output_path);

void to_file(int n, std::tuple<double, double, double, double> result, 
    std::string output_path);

void test_algorithm(std::tuple<std::vector<int>, int, int, double, double> (
        *sorting_funct)(std::vector<int> input, bool verbose),  // algorithm
        std::vector<int> (*random_gen)(int size),   // generator
        int max_n, int step, int reps, std::string output_path);