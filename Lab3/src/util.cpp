#include <vector>
#include <iostream>
#include <random>
#include <algorithm>
#include <fstream>
#include <tuple>
#include <iomanip>
#include "algorithms.hpp"


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


void to_file(int n, std::tuple<double, double, double, double> result, 
    std::string output_path){
        double comps_avg = std::get<0>(result);
        double swaps_avg = std::get<1>(result);
        double cn_avg = std::get<2>(result);
        double sn_avg = std::get<3>(result);

    std::ofstream outfile;
    outfile.open(output_path, std::ios_base::app); // append instead of overwrite
    outfile << std::fixed << std::setprecision(1) << n << " " << comps_avg << " " << swaps_avg
    << " " << cn_avg << " " << sn_avg << " " << std::endl; 
}


void to_file_search(int n, std::tuple<double, double> result, 
    std::string output_path){
        double comps_avg = std::get<0>(result);
        double cn_avg = std::get<1>(result);

    std::ofstream outfile;
    outfile.open(output_path, std::ios_base::app); // append instead of overwrite
    outfile  << n << " " << comps_avg <<
    " " << cn_avg <<std::endl; 
}


void median_k_test(int max_n, int step, int reps, int group_size, std::string output_path){
    for(int n=step; n<=max_n; n+= step){
        long comps_sum = 0;
        long swaps_sum = 0;
        double cn_sum = 0;
        double sn_sum = 0;

        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<std::mt19937::result_type> distrib(0, n - 1);

        for(int j=0; j<reps; j++){
            auto v = random_v(n);
            int k = distrib(rng);
            auto result = select_median(v, k, group_size);

            // appending results
            comps_sum += std::get<1>(result);
            swaps_sum += std::get<2>(result);
            cn_sum += std::get<3>(result);
            sn_sum += std::get<4>(result);
        }

        // now calculating averages
        double comps_avg = comps_sum / reps;
        double swaps_avg = swaps_sum / reps;
        double cn_avg = cn_sum / reps;
        double sn_avg = sn_sum / reps;

        auto to_save = std::tuple<double, double, double, double>{
        comps_avg, swaps_avg, cn_avg, sn_avg};

        to_file(n, to_save, output_path);
    }
}


void select_random_test(int max_n, int step, int reps, std::string output_path){
    for(int n=step; n<=max_n; n+= step){
        long comps_sum = 0;
        long swaps_sum = 0;
        double cn_sum = 0;
        double sn_sum = 0;

        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<std::mt19937::result_type> distrib(0, n - 1);

        for(int j=0; j<reps; j++){
            auto v = random_v(n);
            int k = distrib(rng);
            auto result = select_random(v, k);

            // appending results
            comps_sum += std::get<1>(result);
            swaps_sum += std::get<2>(result);
            cn_sum += std::get<3>(result);
            sn_sum += std::get<4>(result);
        }

        // now calculating averages
        double comps_avg = comps_sum / reps;
        double swaps_avg = swaps_sum / reps;
        double cn_avg = cn_sum / reps;
        double sn_avg = sn_sum / reps;

        auto to_save = std::tuple<double, double, double, double>{
        comps_avg, swaps_avg, cn_avg, sn_avg};

        to_file(n, to_save, output_path);
    }
}


void search_test(int max_n, int step, int reps, std::string output_path){
    for(int n=step; n<=max_n; n+= step){
        long comps_sum = 0;
        double cn_sum = 0;

        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<std::mt19937::result_type> distrib(0, n * 2);

        for(int j=0; j<reps; j++){
            auto v = random_asc(n);
            
            int key = distrib(rng);
            auto result = binary_search(v, key);

            // appending results
            comps_sum += std::get<1>(result);
            cn_sum += std::get<2>(result);
        }

        // now calculating averages
        double comps_avg = comps_sum / reps;
        double cn_avg = cn_sum / reps;

        auto to_save = std::tuple<double, double>{
        comps_avg, cn_avg};

        to_file_search(n, to_save, output_path);
    }
}


void search_test_beg(int max_n, int step, int reps, std::string output_path){
    for(int n=step; n<=max_n; n+= step){
        long comps_sum = 0;
        double cn_sum = 0;

        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<std::mt19937::result_type> distrib(0, n / 10);

        for(int j=0; j<reps; j++){
            auto v = random_asc(n);
            
            int key = v[distrib(rng)];
            auto result = binary_search(v, key);

            // appending results
            comps_sum += std::get<1>(result);
            cn_sum += std::get<2>(result);
        }

        // now calculating averages
        double comps_avg = comps_sum / reps;
        double cn_avg = cn_sum / reps;

        auto to_save = std::tuple<double, double>{
        comps_avg, cn_avg};

        to_file_search(n, to_save, output_path);
    }
}


void search_test_mid(int max_n, int step, int reps, std::string output_path){
    for(int n=step; n<=max_n; n+= step){
        long comps_sum = 0;
        double cn_sum = 0;

        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<std::mt19937::result_type> distrib(n/2 - (n/10), n/2 + (n/10) - 1);

        for(int j=0; j<reps; j++){
            auto v = random_asc(n);
            
            int key = v[distrib(rng)];
            auto result = binary_search(v, key);

            // appending results
            comps_sum += std::get<1>(result);
            cn_sum += std::get<2>(result);
        }

        // now calculating averages
        double comps_avg = comps_sum / reps;
        double cn_avg = cn_sum / reps;

        auto to_save = std::tuple<double, double>{
        comps_avg, cn_avg};

        to_file_search(n, to_save, output_path);
    }
}


void search_test_end(int max_n, int step, int reps, std::string output_path){
    for(int n=step; n<=max_n; n+= step){
        long comps_sum = 0;
        double cn_sum = 0;

        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<std::mt19937::result_type> distrib(n - (n/10), n - 1);

        for(int j=0; j<reps; j++){
            auto v = random_asc(n);
            
            int key = v[distrib(rng)];
            auto result = binary_search(v, key);

            // appending results
            comps_sum += std::get<1>(result);
            cn_sum += std::get<2>(result);
        }

        // now calculating averages
        double comps_avg = comps_sum / reps;
        double cn_avg = cn_sum / reps;

        auto to_save = std::tuple<double, double>{
        comps_avg, cn_avg};

        to_file_search(n, to_save, output_path);
    }
}