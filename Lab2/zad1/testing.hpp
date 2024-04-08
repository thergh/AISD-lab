#include "sorting.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <tuple>

std::tuple<double, double, double, double> avg_results(
    std::tuple<std::vector<int>, int, int, double, double> (*sorting_funct)(std::vector<int> input, bool verbose),
    std::vector<int> (*random_gen)(int size),
    int reps, std::string output_path);