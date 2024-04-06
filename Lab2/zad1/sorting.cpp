#include <vector>
#include <iostream>
#include <random>
#include <algorithm>


std::vector<int> insert(std::vector<int> input){
    int value = 0;
    int j = 0;
    int size = input.size();

    for(int i = 1; i < size; i++){
        value = input[i];
        j = i - 1;

        while(j >= 0 && input[j] > value){
            input[j + 1] = input[j];
            j = j - 1;
        }
        input[j + 1] = value;
    }
    return input;
}


void print_vector(std::vector<int> v){
    std::string s = "[";
    for(int i=0; i<v.size(); i++){
        s.append(std::to_string(v[i]));
        s.append(", ");
    }
    s.append("]");
    std::cout << s << std::endl;
}


int partition(std::vector<int> &v, int low, int high){
    int pivot = v[high];
    int i = (low-1);
  
    for(int j=low;j<=high;j++){
        if(v[j]<pivot){
            i++;
            std::swap(v[i],v[j]);
        }
    }
    std::swap(v[i+1],v[high]);
    return (i+1);
}


void quick_(std::vector<int> &v, int low, int high){
    if(low<high){
        int pi = partition(v,low,high);
        quick_(v,low,pi-1);
        quick_(v,pi+1,high);
    }
}


std::vector<int> quick(std::vector<int> v){
    quick_(v, 0, v.size() - 1);
    return v;
}


std::vector<int> random(int size){
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
    std::vector arr = random(size);
    std::sort(arr.begin(), arr.end());
    return arr;
}


std::vector<int> random_desc(int size){
    std::vector arr = random(size);
    std::sort(arr.begin(), arr.end(), std::greater<>());
    return arr;
}


std::vector<int> merge_sorted(std::vector<int> a, std::vector<int> b){
    std::vector<int> c(a.size() + b.size());
    merge(a.begin(), a.end(), b.begin(), b.end(), c.begin());
    return c;
}

std::vector<int> dac_sort(std::vector<int> a){
    if(a.size() == 0 || a.size() == 1){
        return a;
    }


    std::vector<std::vector<int>> queue;
    int prev = a[0];
    std::vector<int> part;
    part.push_back(prev);

    for(int i=1; i<a.size(); i++){
        if(a[i] >= a[i - 1]){
            part.push_back(a[i]);
        }
        else{
            queue.push_back(part);
            part = {a[i]};
        }
    }
    
    if(part.size() > 0){
        queue.push_back(part);
    }

    // printing queue before sorting for debugging purposes
    std::cout << "queue" << std::endl;
    print_vector(a);
    for(int i=0; i<queue.size(); i++){
        print_vector(queue[i]);
    }

    while(queue.size() > 1){
        std::vector<int> x = queue[queue.size() - 1];
        queue.pop_back();
        std::vector<int> y = queue[queue.size() - 1];
        queue.pop_back();
        queue.push_back(merge_sorted(x, y));
    }

    return queue[0];
}