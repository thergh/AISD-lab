#include "algorithms.h"
#include "util.h"
#include <iostream>
#include <vector>
#include <tuple>


int main(){
    int n = 8;
    Graph* graph = new Graph(n);
    std::cout << "\nGraf wejściowy:" << std::endl;
    Print2DVectorFloat(graph->weights);

    graph->prim_mst();

    std::cout << "\nMST algorytmem Prima:" << std::endl;
    graph->print_mst();
    std::cout << "\nliczba porównań: " << graph->comps << std::endl;

    std::cout << "\nMST algorytmem Kruskala:" << std::endl;
    graph->kruskal_mst();
    graph->print();
    std::cout << "\nliczba porównań: " << graph->comps << std::endl;
}



// g++ -o main main.cpp algorithms.cpp util.cpp