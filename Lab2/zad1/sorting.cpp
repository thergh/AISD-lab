#include <vector>
#include <iostream>
#include <random>
#include <algorithm>
#include <tuple>
#include <queue>


void print_vector(std::vector<int> v){
    std::string s = "[";
    for(int i=0; i<v.size(); i++){
        s.append(std::to_string(v[i]));
        s.append(", ");
    }
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


/**
 * Insertion sort
*/
std::tuple<std::vector<int>, int, int, double, double>
    insert_sort(std::vector<int> v, bool verbose){

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

    int n = v.size();
    double cn = (double)comps / n;
    double sn = (double)swaps / n;

    if(verbose){
        std::cout << comps << " " << swaps << " " << cn << " " << sn << std::endl;
    }
    return std::make_tuple(v, comps, swaps, cn, sn);
}


/**
 * Insertion sort changed to be applied in the hubrid sort
*/
std::tuple<std::vector<int>, int, int, double, double>
    insert_hybrid_sort(std::vector<int> &v, int low, int high, bool verbose){

    int value = 0;
    int j = 0;
    int size = v.size();

    int comps = 0;
    int swaps = 0;

    for(int i = low; i < high; i++){
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

    int n = high - low;
    double cn = (double)comps / n;
    double sn = (double)swaps / n;

    if(verbose){
        std::cout << comps << " " << swaps << " " << cn << " " << sn << std::endl;
    }
    return std::make_tuple(v, comps, swaps, cn, sn);
}


/**
 * Partition used in quick sort
*/
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
    if(low < high){
        int pi = partition(v, low, high, comps, swaps);
        quick_(v, low, pi-1, comps, swaps);
        quick_(v, pi+1, high, comps, swaps);
    }
}


/**
 * Quick sort
*/
std::tuple<std::vector<int>, int, int, double, double> quick_sort(std::vector<int> v, bool verbose){
    int comps = 0;
    int swaps = 0;

    if(v.size() <= 1){
        return std::make_tuple(v, comps, swaps, 0, 0);
    }
    // todo: check off by one!!
    quick_(v, 0, v.size(), comps, swaps);

    int n = v.size();
    double cn = (double)comps / n;
    double sn = (double)swaps / n;

    if(verbose){
        std::cout << comps << " " << swaps << " " << cn << " " << sn << std::endl;
    }
    return std::make_tuple(v, comps, swaps, cn, sn);
}


void quick_hybrid(std::vector<int> &v, int low, int high, int &comps, int &swaps){
    if(low < high){
        if(high - low < 30){
            v = std::get<0>(insert_hybrid_sort(v, low, high, false));
        }
        else{
            int pi = partition(v, low, high, comps, swaps);
            quick_hybrid(v, low, pi-1, comps, swaps);
            quick_hybrid(v, pi+1, high, comps, swaps);
        }
    }
        comps += 1;
}


/**
 * Hybrid sort
*/
std::tuple<std::vector<int>, int, int, double, double> quick_hybrid_sort(std::vector<int> v, bool verbose){
    int comps = 0;
    int swaps = 0;

    if(v.size() <= 1){
        return std::make_tuple(v, comps, swaps, 0, 0); 
    }
    // todo -1
    quick_hybrid(v, 0, v.size(), comps, swaps);

    int n = v.size();
    double cn = (double)comps / n;
    double sn = (double)swaps / n;

    if(verbose){
        std::cout << comps << " " << swaps << " " << cn << " " << sn << std::endl;
    }
    return std::make_tuple(v, comps, swaps, cn, sn); 
}


/**
 * Partition used in dual quick sort
*/
void dual_pivot_partition(std::vector<int> &v, int low, int high, int &comps, int &swaps, int &pi1, int &pi2) {
    int pivot1 = v[low];
    int pivot2 = v[high];
    if (pivot1 > pivot2) {
        std::swap(pivot1, pivot2);
        swaps++;
    }

    int i = low + 1;
    int j = high - 1;
    int k = low + 1;
    while (k <= j) {
        comps++;
        if (v[k] < pivot1) {
            std::swap(v[k], v[i]);
            i++;
            swaps++;
        } else if (v[k] >= pivot2) {
            while (v[j] > pivot2 && k < j) {
                j--;
                comps++;
            }
            std::swap(v[k], v[j]);
            j--;
            swaps++;
            if (v[k] < pivot1) {
                std::swap(v[k], v[i]);
                i++;
                swaps++;
            }
        }
        k++;
    }
    i--;
    j++;
    std::swap(v[low], v[i]);
    std::swap(v[high], v[j]);
    swaps += 2;
    pi1 = i;
    pi2 = j;
}


/**
 * Quick sort with dual partition
*/
void dual_pivot_quick_sort(std::vector<int> &v, int low, int high, int &comps, int &swaps) {
    comps++;
    if (low < high) {
        int pi1, pi2;
        dual_pivot_partition(v, low, high, comps, swaps, pi1, pi2);
        dual_pivot_quick_sort(v, low, pi1 - 1, comps, swaps);
        dual_pivot_quick_sort(v, pi1 + 1, pi2 - 1, comps, swaps);
        dual_pivot_quick_sort(v, pi2 + 1, high, comps, swaps);
    }
}


/**
 * Quick sort with dual pivot
*/
std::tuple<std::vector<int>, int, int, double, double> dual_pivot_quick_sort(std::vector<int> v, bool verbose){
    int comps = 0;
    int swaps = 0;

    if (v.size() <= 1){
        return std::make_tuple(v, comps, swaps, 0, 0);
    }
    dual_pivot_quick_sort(v, 0, v.size(), comps, swaps);

    int n = v.size();
    double cn = (double) comps / n;
    double sn = (double) swaps / n;

    if (verbose){
        std::cout << comps << " " << swaps << " " << cn << " " << sn << std::endl;
    }
    return std::make_tuple(v, comps, swaps, cn, sn);
}


/**
 * Copying algorithm with implemented counters
*/
template<class InputIterator, class OutputIterator>
  OutputIterator copy_counter(InputIterator first, InputIterator last, OutputIterator result,
  int &comps, int &swaps){
  while(first!=last){
    comps ++;
    swaps++;
    *result = *first;
    ++result; ++first;
  }
  return result;
}


/**
 * Merging algorithm with implemented counters
*/
template <class InputIterator1, class InputIterator2, class OutputIterator>
  OutputIterator merge_counter(InputIterator1 first1, InputIterator1 last1,
                        InputIterator2 first2, InputIterator2 last2,
                        OutputIterator result,
                        int &comps, int &swaps){
  while(true){
    comps ++;
    if(first1==last1){
        return copy_counter(first2,last2,result, comps, swaps);
    }
    comps ++;
    if(first2==last2){
        return copy_counter(first1,last1,result, comps, swaps);
    }

    comps ++;
    *result++ = (*first2<*first1)? *first2++ : *first1++;
  }
}


/**
 * Algorithm for merging two sorted vectors into a sorted vector
*/
std::vector<int> merge_sorted(std::vector<int> a, std::vector<int> b, int &comps, int &swaps){
    std::vector<int> c(a.size() + b.size());
    merge_counter(a.begin(), a.end(), b.begin(), b.end(), c.begin(), comps, swaps);
    return c;
}


/**
 * Custom divide and conquer sort
*/
std::tuple<std::vector<int>, int, int, double, double> dac_sort(std::vector<int> v, bool verbose){
    if(v.size() <= 1){
        return std::make_tuple(v, 0, 0, 0, 0); 
    }

    int comps = 0;
    int swaps = 0;

    std::queue<std::vector<int>> queue;

    int prev = v[0];
    std::vector<int> part;
    part.push_back(prev);

    for(int i = 1; i < v.size(); i++){
        comps += 1;
        if(v[i] >= v[i - 1]){
            part.push_back(v[i]);
        }
        else{
            queue.push(part);
            part = {v[i]};
        }
    }
    
    if(part.size() > 0){
        queue.push(part);
    }

    while(queue.size() > 1){
        std::vector<int> x = queue.front();
        queue.pop();
        std::vector<int> y = queue.front();
        queue.pop();
        queue.push(merge_sorted(x, y, comps, swaps));
        comps += std::max(x.size(), y.size());
        swaps += std::max(x.size(), y.size());
    }

    int n = v.size();
    double cn = (double)comps / n;
    double sn = (double)swaps / n;

    if(verbose){
        std::cout << comps << " " << swaps << " " << cn << " " << sn << std::endl;
    }
    return std::make_tuple(queue.front(), comps, swaps, cn, sn); 
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


/**
 * Merge sort
*/
std::tuple<std::vector<int>, int, int, double, double> merge_sort(std::vector<int> v, bool verbose){
    int comps = 0;
    int swaps = 0;

    std::vector<int> result = merge_sort_(v, comps, swaps);

    int n = v.size();
    double cn = (double)comps / n;
    double sn = (double)swaps / n;

    if(verbose){
        std::cout << comps << " " << swaps << " " << cn << " " << sn << std::endl;
    }
    return std::make_tuple(result, comps, swaps, cn, sn); 
}



