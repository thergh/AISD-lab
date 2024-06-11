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
    for(int i=0; i<v.size(); i++){
        outfile << v[i] << std::endl;
    }
    outfile.close();
}


void value_to_file(int value, std::string output_path){
    std::ofstream outfile;
    outfile.open(output_path, std::ios_base::app);
    outfile << value << std::endl;
    outfile.close();
}


void test_BST(int max, int step, int reps, bool sorted, std::string output_path){
    std::vector<long> comps_insert_avg;
    std::vector<long> ptr_insert_avg;
    std::vector<long> comps_delete_avg;
    std::vector<long> ptr_delete_avg;
    std::vector<float> height_avg;

    for(int x=1; x<=max/step; x++){
        int n = x * step;
        std::cout << "calculating step " << n << std::endl;

        long long comps_insert_sum = 0;
        long long ptr_insert_sum = 0;
        long long comps_delete_sum = 0;
        long long ptr_delete_sum = 0;
        long long height_sum = 0;

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
            height_sum += tree->height();

            tree->comps_count = 0;
            tree->ptr_operations_count = 0;

            for(int i=0; i<n; i++){
                tree->delete_value(values_random[i]);
            }
            
            int comps_delete = tree->comps_count;
            int ptr_delete = tree->ptr_operations_count;
            height_sum += tree->height();
            
            comps_insert_sum += comps_insert;
            ptr_insert_sum += ptr_insert;
            comps_delete_sum += comps_delete;
            ptr_delete_sum += ptr_delete;
            
        }

        comps_insert_avg.push_back(comps_insert_sum/reps);
        ptr_insert_avg.push_back(ptr_insert_sum/reps);
        comps_delete_avg.push_back(comps_delete_sum/reps);
        ptr_delete_avg.push_back(ptr_delete_sum/reps);
        float h_avg = (float)height_sum/(float)reps;
        height_avg.push_back(h_avg);


        std::string suffix;
        if(sorted == true){
            suffix = "asc";
        }
        else{
            suffix = "random";
        }

        value_to_file(comps_insert_sum/reps, "results/BST_comps_insert_" + suffix + ".txt");
        value_to_file(ptr_insert_sum/reps, "results/BST_ptr_insert_" + suffix + ".txt");
        value_to_file(comps_delete_sum/reps, "results/BST_comps_delete_" + suffix + ".txt");
        value_to_file(ptr_delete_sum/reps, "results/BST_ptr_delete_" + suffix + ".txt");
        value_to_file(height_sum/reps, "results/BST_height_" + suffix + ".txt");
    }
}


void test_RBT(int max, int step, int reps, bool sorted, std::string output_path){
    std::vector<int> comps_insert_avg;
    std::vector<int> ptr_insert_avg;
    std::vector<int> comps_delete_avg;
    std::vector<int> ptr_delete_avg;
    std::vector<float> height_avg;

    for(int x=1; x<=max/step; x++){
        int n = x * step;
        std::cout << "calculating step " << n << std::endl;

        long comps_insert_sum = 0;
        long ptr_insert_sum = 0;
        long comps_delete_sum = 0;
        long ptr_delete_sum = 0;
        long height_sum = 0;

        for(int y=0; y<reps; y++){
            RBT* tree = new RBT();
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
            height_sum += tree->height();

            tree->comps_count = 0;
            tree->ptr_operations_count = 0;

            for(int i=0; i<n; i++){
                tree->delete_value(values_random[i]);
            }
            
            int comps_delete = tree->comps_count;
            int ptr_delete = tree->ptr_operations_count;

            comps_insert_sum += comps_insert;
            ptr_insert_sum += ptr_insert;
            comps_delete_sum += comps_delete;
            ptr_delete_sum += ptr_delete;
            
        }

        comps_insert_avg.push_back(comps_insert_sum/reps);
        ptr_insert_avg.push_back(ptr_insert_sum/reps);
        comps_delete_avg.push_back(comps_delete_sum/reps);
        ptr_delete_avg.push_back(ptr_delete_sum/reps);
        float h_avg = (float)height_sum/(float)reps;
        height_avg.push_back(h_avg);


        std::string suffix;
        if(sorted == true){
            suffix = "asc";
        }
        else{
            suffix = "random";
        }

        value_to_file(comps_insert_sum/reps, "results/RBT_comps_insert_" + suffix + ".txt");
        value_to_file(ptr_insert_sum/reps, "results/RBT_ptr_insert_" + suffix + ".txt");
        value_to_file(comps_delete_sum/reps, "results/RBT_comps_delete_" + suffix + ".txt");
        value_to_file(ptr_delete_sum/reps, "results/RBT_ptr_delete_" + suffix + ".txt");
        value_to_file(height_sum/reps, "results/RBT_height_" + suffix + ".txt");
    }
}


void test_ST(int max, int step, int reps, bool sorted, std::string output_path){
    std::vector<int> comps_insert_avg;
    std::vector<int> ptr_insert_avg;
    std::vector<int> comps_delete_avg;
    std::vector<int> ptr_delete_avg;
    std::vector<float> height_avg;

    for(int x=1; x<=max/step; x++){
        int n = x * step;
        std::cout << "calculating step " << n << std::endl;

        long comps_insert_sum = 0;
        long ptr_insert_sum = 0;
        long comps_delete_sum = 0;
        long ptr_delete_sum = 0;
        long height_sum = 0;

        for(int y=0; y<reps; y++){
            ST* tree = new ST();
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
            height_sum += tree->height();

            tree->comps_count = 0;
            tree->ptr_operations_count = 0;

            for(int i=0; i<n; i++){
                tree->delete_value(values_random[i]);
            }
            
            int comps_delete = tree->comps_count;
            int ptr_delete = tree->ptr_operations_count;

            comps_insert_sum += comps_insert;
            ptr_insert_sum += ptr_insert;
            comps_delete_sum += comps_delete;
            ptr_delete_sum += ptr_delete;
            
            
        }

        comps_insert_avg.push_back(comps_insert_sum/reps);
        ptr_insert_avg.push_back(ptr_insert_sum/reps);
        comps_delete_avg.push_back(comps_delete_sum/reps);
        ptr_delete_avg.push_back(ptr_delete_sum/reps);
        float h_avg = (float)height_sum/(float)reps;
        height_avg.push_back(h_avg);


        std::string suffix;
        if(sorted == true){
            suffix = "asc";
        }
        else{
            suffix = "random";
        }

        value_to_file(comps_insert_sum/reps, "results/ST_comps_insert_" + suffix + ".txt");
        value_to_file(ptr_insert_sum/reps, "results/ST_ptr_insert_" + suffix + ".txt");
        value_to_file(comps_delete_sum/reps, "results/ST_comps_delete_" + suffix + ".txt");
        value_to_file(ptr_delete_sum/reps, "results/ST_ptr_delete_" + suffix + ".txt");
        value_to_file(height_sum/reps, "results/ST_height_" + suffix + ".txt");
    }
}

int main(){
    test_BST(100000, 10000, 5, true, "out_t.txt");
    // test_RBT(100000, 10000, 20, true, "out_t.txt");
    // test_ST(100000, 10000, 20, true, "out_t.txt");
}