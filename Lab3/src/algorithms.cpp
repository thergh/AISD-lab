#include <bits/stdc++.h>
#include <algorithm>
#include <vector>
#include <random>


int partition(std::vector<int> &v, int low, int high, int pivot){
    int i = low; 

    for(int j = low; j <= high - 1; j++){ 
        if(v[j] <= pivot){ 
            std::swap(v[i], v[j]); 
            i++; 
        } 
    } 
    std::swap(v[i], v[high]);

    return i; 
} 
  

int select_random(std::vector<int> &v, int low, int high, int position){

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distribution(low, high);

    if(position > 0 && position <= high - low + 1){ 
        int index = partition(v, low , high, v[distribution(gen)]); 
  
        if(index - low == position - 1){
            return v[index]; 
        }
  
        if(index - low  > position - 1){
            return select_random(v, low, index - 1, position); 
        }
  
        return select_random(v, index + 1, high, position - index + low - 1); 
    } 
  
    return INT_MAX; 
}


int median5(std::vector<int>& v){
    sort(v.begin(), v.end());
    return v[v.size() / 2];
}


int partition_median(std::vector<int>& v, int low, int high, int pivot){
    while(low <= high){
        while(v[low] < pivot){
            low++;
        }
        while(v[high] > pivot){
            high--;
        }
        if(low <= high){
            std::swap(v[low], v[high]);
            low++;
            high--;
        }
    }
    return low;
}


int select_median(std::vector<int>& v, int position, int k=5){
    const int n = v.size();
    std::vector<int> medians;

    for(int i = 0; i < n; i += k){
        std::vector<int> group;
        for(int j = i; j < std::min(i + k, n); ++j){
            group.push_back(v[j]);
        }
        medians.push_back(median5(group));
    }

    int pivot;
    if(medians.size() == 1){
        pivot = medians[0];
    }   
    else{
        pivot = select_median(medians, medians.size() / 2, k);
    }

    int index = partition_median(v, 0, n - 1, pivot);

    if(index == position){
        return v[index];
    }
    else if(index > position){
        return select_median(v, position, k);
    }
    else{
        return select_median(v, position - index, k);
    }
}


int binary_search(std::vector<int> v, int key){
    int low = 0;
    int high = v.size() - 1;
    int mid = -1;

    while(low <= high){
        mid = low + (high - low) / 2;

        if(v[mid] == key){
            // return mid;
            return 1;
        }
        else if(v[mid] < key){
            low = mid + 1;
        }
        else{
            high = mid - 1;
        }
    }
    return -1;
}