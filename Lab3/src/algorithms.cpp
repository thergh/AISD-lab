#include <bits/stdc++.h>
#include <algorithm>
#include <vector>
#include <random>
#include <tuple>



int binary_search_rec(const std::vector<int>& v, int low, int high, int target, int& comps){
    comps ++;
    if(low <= high){
        int mid = low + (high - low) / 2;

        if(v[mid] == target){
            return 1;

        }

        if(v[mid] < target){
            return binary_search_rec(v, mid + 1, high, target, comps);

        }

        return binary_search_rec(v, low, mid - 1, target, comps);
    }

    return 0;
}


std::tuple<int, int, double> binary_search(const std::vector<int>& v, int target){
    int n = v.size();
    int low = 0;
    int high = v.size() - 1;
    int comps = 0;
    int result = binary_search_rec(v, low, high, target, comps);
    double cn = (double)comps / n;
    return std::make_tuple(result, comps, cn);
}


int partition(std::vector<int>& v, int low, int high, int pivot_index, int& comps, int& swaps){
    std::swap(v[pivot_index], v[high]);
    swaps ++;
    int pivot = v[high];
    int i = low - 1;
    
    for(int j = low; j < high; j++){
        comps ++;
        if(v[j] < pivot){
            i++;
            std::swap(v[i], v[j]);
            swaps ++;
        }
    }
    
    std::swap(v[i + 1], v[high]);
    swaps ++;
    
    return i + 1;
}


int select_random_rec(std::vector<int>& v, int low, int high, int position, int& comps, int& swaps){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distribution(low, high);

    comps ++;
    if(low <= high){
        int partition_index = partition(v, low, high, distribution(gen), swaps, comps);
        
        comps ++;
        if(partition_index == position){
            return v[position];
        }
        else if(partition_index > position){
            comps ++;
            return select_random_rec(v, low, partition_index - 1, position, swaps, comps);
        }
        else{
            comps ++;
            return select_random_rec(v, partition_index + 1, high, position, swaps, comps);
        }
    }
    return -1;
}


std::tuple<int, int, int, double, double> select_random(
    std::vector<int>& v, int k){
    int comps = 0;
    int swaps = 0;
    int n = v.size();
    int result = select_random_rec(v, 0, v.size() - 1, k, comps, swaps);
    double cn = comps / n;
    double sn = swaps / n;
    return std::make_tuple(result, comps, swaps, cn, sn);
}


int median_of_medians(std::vector<int>& v, int low, int high, int group_size, int& comps, int& swaps){
    int n = high - low + 1;
    if(n <= group_size){
        comps ++;
        std::sort(v.begin() + low, v.begin() + high + 1);
        swaps += 2;
        comps += 2;
        return low + n / 2;
    }

    std::vector<int> medians;
    for(int i = low; i <= high; i += group_size){
        int sub_high = std::min(i + group_size - 1, high);
        comps ++;
        int median_index = median_of_medians(v, i, sub_high, group_size, comps, swaps);
        medians.push_back(v[median_index]);
    }

    return median_of_medians(medians, 0, medians.size() - 1, group_size, comps, swaps);
}


int select_median_rec(std::vector<int>& v, int low, int high, int k, int group_size,
    int& comps, int& swaps){

    int pivot_index = median_of_medians(v, low, high, group_size, comps, swaps);

    comps ++;
    if(low <= high){
        int partition_index = partition(v, low, high, pivot_index, comps, swaps);
        
        comps ++;
        if(partition_index == k){
            
            return v[k];
        }
        else if(partition_index > k){
            comps ++;
            return select_median_rec(v, low, partition_index - 1, k, group_size, comps, swaps);
        }
        else{
            comps ++;
            return select_median_rec(v, partition_index + 1, high, k, group_size, comps, swaps);
        }
    }
    return -1;
}


std::tuple<int, int, int, double, double> select_median(
    std::vector<int>& v, int k, int group_size){
    int comps = 0;
    int swaps = 0;
    int n = v.size();
    int result = select_median_rec(v, 0, v.size() - 1, k, group_size, comps, swaps);
    double cn = comps / n;
    double sn = swaps / n;
    return std::make_tuple(result, comps, swaps, cn, sn);
}