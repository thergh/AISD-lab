#include <vector>
#include <limits.h>
#include <iostream>
#include <random>
#include <tuple>
#include <algorithm>
#include <chrono>
#include "algorithms.h"
#include "util.h"


Graph::Graph(int size){
    this->weights = generate_graph(size);
    this->size = size;

    // kruskal
    parent = new int[size];

    for(int i = 0; i < size; i++){
        parent[i] = i;
    }
    G.clear();
    T.clear();
    weights_to_edges(this->weights);
}


float Graph::get_random_number(){
    static std::default_random_engine e(std::chrono::system_clock::now().time_since_epoch().count());
    static std::uniform_real_distribution<> dis(0, 1); // range [0, 1)
    return dis(e);
}


std::vector<std::vector<float>> Graph::generate_graph(int size){
    std::vector<std::vector<float>> weights(size, std::vector<float>(size));

    for(int i=0; i<size; i++){
        for(int j=i; j<size; j++){
            float number = get_random_number();
            weights[i][j] = number;
            weights[j][i] = number;
        }
    }

    // zeros on diagonal
    for(int i=0; i<size; i++){
        weights[i][i] = 0;
    }

    return weights;
}


float Graph::min_key(std::vector<float> keys, std::vector<bool> mst_set){
    float min_key = 1.0;
    int min_index = -1;
    int vector_size = keys.size();
    for(int i=0; i<vector_size; i++){
        if(mst_set[i] == false && keys[i] < min_key){
            min_key = keys[i];
            min_index = i;
        }
    }
    return min_index;
}


// Returns parents array of MST
std::vector<int> Graph::prim_mst(){
    this->comps = 0;
    int n = this->weights.size();
    std::vector<bool> mst_set(n, false);    // vertices included in MST
    std::vector<float> keys(n, INT_MAX);      // keys of vertices
    std::vector<int> parents(n);            // lets restore MST
    int root = 0;
    keys[root] = 0;
    parents[0] = -1;

    for(int i=0; i<n-1; i++){
        float u = min_key(keys, mst_set);
        mst_set[u] = true;
        for(int v=0; v<n; v++){
            this->comps += 2;
            if(this->weights[u][v] && mst_set[v] == false && this->weights[u][v] < keys[v]){
                parents[v] = u;
                keys[v] = this->weights[u][v];
                // std::cout << "edge: " << weights[u][v] << " ";
            }
        }
    }
    this->parents = parents;
    return parents;
}


void Graph::print_mst(){
    float tree_weight = 0;
    int n = this->weights.size();

    if(this->size <= 20){
        std::cout << "Edges\n";
    }
    
    for(int i = 1; i < n; i++){

        if(this->size <= 20){
            std::cout << this->parents[i] << " - " << i << " \n";
        }
        tree_weight += this->weights[i][this->parents[i]];
        // std::cout << "added edge: " << this->weights[i][this->parents[i]] << " ";
    }
    std::cout << "Tree weight: " << tree_weight << std::endl;
}


// **************** KRUSKAL ****************

#define edge std::pair<int, int>


void Graph::weights_to_edges(std::vector<std::vector<float>> weights){
    int size = weights.size();
    for(int i=0; i<size; i++){
        for(int j=i; j<size; j++){
            if(i != j){
                float weight = weights[i][j];
                AddWeightedEdge(i, j, weight);
            }

        }
    }    
}

void Graph::AddWeightedEdge(int u, int v, float w){
    this->G.push_back(std::make_pair(w, edge(u, v)));
}


int Graph::find_set(int i){
    this->comps ++;
    if(i == parent[i]){
        return i;
    }  
    else
        return find_set(parent[i]);
}

void Graph::union_set(int u, int v){
    parent[u] = parent[v];
}


void Graph::kruskal_mst(){
    std::vector<int> parents(this->size);
    this->comps = 0;
    
    int i, uRep, vRep;
    sort(G.begin(), G.end());  // increasing weight
    for(i = 0; i < G.size(); i++){
        uRep = find_set(G[i].second.first);
        vRep = find_set(G[i].second.second);

        this->comps ++;
        if(uRep != vRep){
            T.push_back(G[i]);  // add to tree
            parents[G[i].second.first] = G[i].second.second;
            union_set(uRep, vRep);
        }
    }
}


void Graph::print(){
    float sum = 0;
    std::cout << "Edges:" << std::endl;
    for(int i = 0; i < T.size(); i++){
        std::cout << T[i].second.second << " - " << T[i].second.first;
        std::cout << std::endl;
        sum += weights[T[i].second.second][T[i].second.first];
    }
    std::cout << "Tree weight: " << sum << std::endl;
}
