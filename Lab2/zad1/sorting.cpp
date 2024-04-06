#include <vector>
#include <iostream>
#include <random>
#include <algorithm>


// global verboses for recursive functions so i don't have to deal with returning


void print_vector(std::vector<int> v){
    std::string s = "[";
    for(int i=0; i<v.size(); i++){
        s.append(std::to_string(v[i]));
        s.append(", ");
    }
    s.append("]");
    std::cout << s << std::endl;
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


std::vector<int> insert_sort(std::vector<int> v, bool verbose){
    int value = 0;
    int j = 0;
    int size = v.size();

    int comps = 0;
    int swaps = 0;

    for(int i = 1; i < size; i++){
        value = v[i];
        j = i - 1;

        while(j >= 0 && v[j] > value){
            comps += 1;
            v[j + 1] = v[j];
            swaps += 1;
            j = j - 1;
        }
        v[j + 1] = value;
        swaps += 1;
    }

    if(verbose){
        std::cout << comps << " " << swaps << " " <<\
         (double)comps / (double)v.size() <<\
          " " << (double)swaps / (double)v.size() << std::endl;
    }
    return v;
}


int partition(std::vector<int> &v, int low, int high, int &comps, int &swaps){
    int pivot = v[high];
    int i = (low - 1);
  
    for(int j=low; j<=high; j++){
        comps += 1;
        if(v[j] < pivot){
            i++;
            std::swap(v[i], v[j]);
            swaps += 1;
        }
    }
    std::swap(v[i + 1], v[high]);
    swaps += 1;
    return (i + 1);
}


void quick_(std::vector<int> &v, int low, int high, int &comps, int &swaps){
    comps += 1;
    if(low<high){
        int pi = partition(v, low, high, comps, swaps);
        quick_(v, low, pi-1, comps, swaps);
        quick_(v, pi+1, high, comps, swaps);
    }
}


std::vector<int> quick_sort(std::vector<int> v, bool verbose){
    int comps = 0;
    int swaps = 0;

    if(v.size() <= 1){
        return v;
    }
    quick_(v, 0, v.size() - 1, comps, swaps);

    if(verbose){
        std::cout << comps << " " << swaps << " " <<\
         (double)comps / (double)v.size() <<\
          " " << (double)swaps / (double)v.size() << std::endl;
    }
    return v;
}


void quick_hybrid(std::vector<int> &v, int low, int high, int &comps, int &swaps){
    if(high - low < 5){
        v = insert_sort(v, false);
    }

    comps += 1;
    if(low < high){
        int pi = partition(v, low, high, comps, swaps);
        quick_hybrid(v, low, pi-1, comps, swaps);
        quick_hybrid(v, pi+1, high, comps, swaps);
    }
}


std::vector<int> quick_hybrid_sort(std::vector<int> v, bool verbose){
    int comps = 0;
    int swaps = 0;

    if(v.size() <= 1){
        return v;
    }
    quick_hybrid(v, 0, v.size() - 1, comps, swaps);

    if(verbose){
        std::cout << comps << " " << swaps << " " <<\
         (double)comps / (double)v.size() <<\
          " " << (double)swaps / (double)v.size() << std::endl;
    }
    return v;    
}


std::vector<int> merge_sorted(std::vector<int> a, std::vector<int> b){
    std::vector<int> c(a.size() + b.size());
    merge(a.begin(), a.end(), b.begin(), b.end(), c.begin());
    return c;
}


std::vector<int> dac_sort(std::vector<int> a, bool verbose){
    if(a.size() <= 1){
        return a;
    }

    int comps = 0;
    int swaps = 0;

    std::vector<std::vector<int>> queue;
    int prev = a[0];
    std::vector<int> part;
    part.push_back(prev);

    for(int i = 1; i < a.size(); i++){
        comps += 1;
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

    while(queue.size() > 1){
        std::vector<int> x = queue[queue.size() - 1];
        queue.pop_back();
        std::vector<int> y = queue[queue.size() - 1];
        queue.pop_back();
        queue.push_back(merge_sorted(x, y));
        comps += std::max(x.size(), y.size());
        swaps += std::max(x.size(), y.size());
    }

    if(verbose){
        std::cout << comps << " " << swaps << " " <<\
        (double) comps / (double)a.size() <<\
         " " << (double)swaps / (double)a.size() << std::endl;
    }
    return queue[0];
}


std::vector<int> merge_sort_(std::vector<int> v, int &comps, int &swaps){
    if(v.size() <= 1){
        return v;
    }
    if(v.size() > 1){
        int mid = v.size() / 2;
        std::vector<int> left_half(v.begin(), v.begin() + mid);
        std::vector<int> right_half(v.begin() + mid, v.begin() + v.size());

        left_half = merge_sort_(left_half, comps, swaps);
        right_half = merge_sort_(right_half, comps, swaps);

        int i = 0;
        int j = 0;
        int k = 0;

        while(i < left_half.size() && j < right_half.size()){
    
            comps += 1;
            if(left_half[i] < right_half[j]){
                swaps += 1;
                v[k] = left_half[i];
                i++;
            }
            else{
                swaps += 1;
                v[k] = right_half[j];
                j++;
            }
            k++;
        }

        while(i < left_half.size()){
            swaps += 1;
            v[k] = left_half[i];
            i++;
            k++;
        }

        while(j < right_half.size()){
            swaps += 1;
            v[k] = right_half[j];
            j++;
            k++;
        }
    }

    return v;    
}


std::vector<int> merge_sort(std::vector<int> v, bool verbose){
    int comps = 0;
    int swaps = 0;

    std::vector<int> result = merge_sort_(v, comps, swaps);

    if(verbose){
        std::cout << comps << " " << swaps << " " <<\
         (double)comps / (double)v.size() <<\
          " " << (double)swaps / (double)v.size() << std::endl;
    }
    return v;
}
