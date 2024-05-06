#pragma once
#include <vector>



std::tuple<int, int, double> binary_search(const std::vector<int>& v, int target);

std::tuple<int, int, int, double, double> select_random(
    std::vector<int>& v, int k);

std::tuple<int, int, int, double, double> select_median(
    std::vector<int>& v, int k, int group_size);