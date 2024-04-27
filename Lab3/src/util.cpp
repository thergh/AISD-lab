#include <vector>
#include <iostream>
#include <random>
#include <algorithm>
#include <fstream>


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