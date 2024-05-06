#pragma once
#include <vector>
#include <string>

std::vector<int> random_v(int size);

std::vector<int> random_asc(int size);

std::vector<int> random_desc(int size);

void vec_to_file(std::vector<int> v, std::string output_path);

void print_vector(std::vector<int> v);

void median_k_test(int max_n, int step, int reps, int group_size, std::string output_path);

void select_random_test(int max_n, int step, int reps, std::string output_path);

void search_test(int max_n, int step, int reps, std::string output_path);

void search_test_beg(int max_n, int step, int reps, std::string output_path);

void search_test_mid(int max_n, int step, int reps, std::string output_path);

void search_test_end(int max_n, int step, int reps, std::string output_path);