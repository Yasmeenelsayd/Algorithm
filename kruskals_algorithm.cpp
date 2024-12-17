#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge 
{
    int src, dest, weight;
};

//  subset for union-find
struct Subset 
{
    int parent;
    int rank;
};

// Compare function for sorting edges by weight
bool compareEdges(Edge a, Edge b) 
{
    return a.weight < b.weight;
}

// Find the root of a set with path compression
int find(Subset subsets[], int i) 
{
    if (subsets[i].parent != i)
    {
        subsets[i].parent = find(subsets, subsets[i].parent);
    }
    return subsets[i].parent;
}

// Union of two sets based on rank
void unionSets(Subset subsets[], int x, int y) 
{
    int rootX = find(subsets, x);
    int rootY = find(subsets, y);

    if (subsets[rootX].rank < subsets[rootY].rank) 
    {
        subsets[rootX].parent = rootY;
    }
    else if (subsets[rootX].rank > subsets[rootY].rank) 
    {
        subsets[rootY].parent = rootX;
    }
    else {
        subsets[rootY].parent = rootX;
        subsets[rootX].rank++;
    }
}

// Kruskal's algorithm to find the MST
void kruskalMST(vector<Edge>& edges, int V) 
{
    // Step 1: Sort all edges in ascending order of weight
    sort(edges.begin(), edges.end(), compareEdges);

    vector<Edge> result; // To store the edges in MST
    Subset* subsets = new Subset[V];

    // Initialize subsets for each vertex
    for (int v = 0; v < V; v++) 
    {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    int e = 0; // Count of edges included in MST
    int i = 0; // Index for sorted edges

    // Process edges in sorted order
    while (e < V - 1 && i < edges.size()) 
    {
        Edge nextEdge = edges[i++];
        int x = find(subsets, nextEdge.src);
        int y = find(subsets, nextEdge.dest);

        // If including this edge does not cause a cycle, include it in MST
        if (x != y) 
        {
            result.push_back(nextEdge);
            unionSets(subsets, x, y);
            e++;
        }
    }

    // Print the resulting MST
    cout << "Edges in the Minimum Spanning Tree:\n";
    int totalWeight = 0;
    for (Edge edge : result) 
    {
        cout << edge.src << " -- " << edge.dest << " == " << edge.weight << endl;
        totalWeight += edge.weight;
    }
    cout << "Total Weight of MST: " << totalWeight << endl;

    delete[] subsets;
}


int main() 
{
    int V = 4; 
    vector<Edge> edges = {
        {0, 1, 10}, {0, 2, 6}, {0, 3, 5},
        {1, 3, 15}, {2, 3, 4}
    };

    kruskalMST(edges, V);
    return 0;
}
