#include "trees.h"
#include <vector>
#include <random>
#include <algorithm>
#include <fstream>
#include <tuple>
#include <iomanip>
#include <iostream>


void print_vector(std::vector<int> v){
    std::string s = "[";
    for(int i=0; i<v.size()-1; i++){
        s.append(std::to_string(v[i]));
        s.append(", ");
    }
    s.append(std::to_string(v[v.size()-1]));
    s.append("]");
    std::cout << s << std::endl;
}


std::vector<int> random_v(int size){
    std::vector<int> arr;
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> distrib(0, size * 2);

    for(int i=0; i<size; i++){
        arr.push_back(distrib(rng));
    }

    return arr;
}


std::vector<int> random_asc(int size){
    std::vector arr = random_v(size);
    std::sort(arr.begin(), arr.end());
    return arr;
}


std::vector<int> random_desc(int size){
    std::vector arr = random_v(size);
    std::sort(arr.begin(), arr.end(), std::greater<>());
    return arr;
}


void vec_to_file(std::vector<int> v, std::string output_path){
    std::ofstream outfile;
    outfile.open(output_path, std::ios_base::app);
    if(v.size()>0){
        outfile << v[0];
    }
    if(v.size()>1){
        for(int i=1; i<v.size(); i++){
            outfile << " " << v[i];
        }
    }
    outfile << std::endl;
}


void test_BST(int max, int step, int reps, bool sorted, std::string output_path){
    std::vector<int> comps_insert_avg;
    std::vector<int> ptr_insert_avg;
    std::vector<int> comps_delete_avg;
    std::vector<int> ptr_delete_avg;

    for(int x=1; x<=max/step; x++){
        int n = x * step;
        std::cout << "calculating step " << n << std::endl;

        int comps_insert_sum = 0;
        int ptr_insert_sum = 0;
        int comps_delete_sum = 0;
        int ptr_delete_sum = 0;

        for(int y=0; y<reps; y++){
            BST* tree = new BST();
            std::vector<int> values_random = random_v(n);
            std::vector<int> values_sorted = values_random;
            std::sort(values_sorted.begin(), values_sorted.end());

            if(sorted == true){
                for(int i=0; i<n; i++){
                    tree->insert_value(values_sorted[i]);
                }
            }
            else{
                for(int i=0; i<n; i++){
                    tree->insert_value(values_random[i]);
                }
            }

            int comps_insert = tree->comps_count;
            int ptr_insert = tree->ptr_operations_count;

            tree->comps_count = 0;
            tree->ptr_operations_count = 0;

            // std::cout << "comps: " << comps_insert << std::endl;
            // std::cout << "ptr: " << ptr_insert << std::endl;

            for(int i=0; i<n; i++){
                tree->delete_value(values_random[i]);
            }
            
            int comps_delete = tree->comps_count;
            int ptr_delete = tree->ptr_operations_count;
            // std::cout << "comps: " << comps_delete << std::endl;
            // std::cout << "ptr: " << ptr_delete << std::endl;

            comps_insert_sum += comps_insert;
            ptr_insert_sum += ptr_insert;
            comps_delete_sum += comps_delete;
            ptr_delete_sum += ptr_delete;
        }

        comps_insert_avg.push_back(comps_insert_sum/reps);
        ptr_insert_avg.push_back(ptr_insert_sum/reps);
        comps_delete_avg.push_back(comps_delete_sum/reps);
        ptr_delete_avg.push_back(ptr_delete_sum/reps);

    }
    
    print_vector(comps_insert_avg);
    print_vector(ptr_insert_avg);
    print_vector(comps_delete_avg);
    print_vector(ptr_delete_avg);
}  


int main(){
    test_BST(1000, 100, 10, false, "out_t.txt");
}