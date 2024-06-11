#include "trees.h"
#include <vector>
#include <iostream>
#include <random>
#include <algorithm>

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


int main(){
    int n = 50;
    std::vector<int> keys = random_v(n);
    std::vector<int> keys_asc = keys;
    std::sort(keys_asc.begin(), keys_asc.end());
    ST* tree = new ST();

    std::cout << "Drzewo ST" << std::endl;
    std::cout << "Rosnace klucze" << std::endl;
    std::cout << "Wstawianie:" << std::endl;
    for(int i=0; i<n; i++){
        std::cout << "wstawiono " << keys_asc[i] << std::endl;
        tree->insert_value(keys_asc[i]);
        print_tree(tree->root);
    }

    std::cout << "Usuwanie:" << std::endl;
    for(int i=0; i<n; i++){
                std::cout << "usunieto " << keys[i] << std::endl;
        tree->delete_value(keys[i]);
        print_tree(tree->root);
    }

    std::cout << "Losowe klucze" << std::endl;
    std::cout << "Wstawianie:" << std::endl;
    for(int i=0; i<n; i++){
        std::cout << "wstawiono " << keys[i] << std::endl;
        tree->insert_value(keys[i]);
        print_tree(tree->root);
    }

    std::cout << "Usuwanie:" << std::endl;
    for(int i=0; i<n; i++){
        std::cout << "usunieto " << keys[i] << std::endl;
        tree->delete_value(keys[i]);
        print_tree(tree->root);
    }
}

// g++ -o st st.cpp trees.cpp