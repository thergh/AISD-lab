#pragma once
#include <vector>
#include <string>

std::vector<int> random_v(int size);

std::vector<int> random_asc(int size);

std::vector<int> random_desc(int size);

void vec_to_file(std::vector<int> v, std::string output_path);

void print_vector(std::vector<int> v);
