#pragma once
#include <vector>

std::tuple<std::vector<int>, int, int, double, double>\
 insert_sort(std::vector<int> input, bool verbose = false);

std::vector<int> quick_sort(std::vector<int> input, bool verbose = false);

std::vector<int> quick_hybrid_sort(std::vector<int> input, bool verbose = false);

std::vector<int> dac_sort(std::vector<int> a, bool verbose = false);

std::vector<int> merge_sort(std::vector<int>, bool verbose = false);

std::vector<int> random_v(int size);

std::vector<int> random_asc(int size);

std::vector<int> random_desc(int size);

void print_vector(std::vector<int> v);




