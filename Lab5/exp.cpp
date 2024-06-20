#include "algorithms.h"
#include <vector>
#include <random>
#include <algorithm>
#include <fstream>
#include <tuple>
#include <iomanip>
#include <iostream>
#include <string>


void test_prim(int size, int step, int reps, std::string out_path){
    std::ofstream outfile;
    outfile.open(out_path, std::ios_base::app);

    for(int i=1; i<=size/step; i++){
        long long comps_sum = 0;
        for(int j=0; j<reps; j++){
            Graph* graph = new Graph(i*step);
            graph->prim_mst();
            comps_sum += graph->comps;
        }
        outfile << i*step << " " << comps_sum/reps << std::endl;
    }
    outfile.close();
}


void test_kruskal(int size, int step, int reps, int offset, std::string out_path){
    std::ofstream outfile;
    outfile.open(out_path, std::ios_base::app);

    for(int i=1+offset; i<=size/step; i++){
        long long comps_sum = 0;
        for(int j=0; j<reps; j++){
            Graph* graph = new Graph(i*step);
            graph->kruskal_mst();
            comps_sum += graph->comps;
        }
        outfile << i*step << " " << comps_sum/reps << std::endl;
    }
    outfile.close();
}


void test_kruskal(int size, int reps, std::string out_path){
    
}

int main(){
    // test_prim(10000, 1000, 2, "data/prim_comps.txt");
    test_kruskal(10000, 1000, 2, 5, "data/kruskal_comps.txt");

}