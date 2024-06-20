#include <vector>
#include <iostream>


// /**
//  * Disjoint union set class
//  */
// class DSU{ 
// 	int* parent; 
// 	int* rank; 

// public: 
//     int comps = 0;
// 	DSU(int n);
// 	int find(int i);
// 	void unite(int x, int y);
// }; 


#define edge std::pair<int, int>

/**
 * Representing graph and MST algorithms
 */
class Graph{
public:
    int size;
    int comps = 0;
    std::vector<std::vector<float>> weights;
    std::vector<int> parents;

    Graph(int size);
    std::vector<int> prim_mst();
    void print_mst();

    void kruskal_mst();
    void print();

// private:
    // Prim's
    float min_key(std::vector<float> keys, std::vector<bool> mst_set);
    float get_random_number();
    std::vector<std::vector<float>> generate_graph(int size);

    // kruskal's
    void AddWeightedEdge(int u, int v, float w);
    int find_set(int i);
    void union_set(int u, int v);
    void weights_to_edges(std::vector<std::vector<float>> weights);
    std::vector<std::pair<float, edge> > G;  // graph
    std::vector<std::pair<float, edge> > T;  // mst
    int *parent;
};


