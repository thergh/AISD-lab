#pragma once
#include <vector>

int select_random(std::vector<int> &v, int low, int high, int position);

int select_median(std::vector<int>& v, int position, int k=5);

int binary_search(std::vector<int> v, int key);