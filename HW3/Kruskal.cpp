/*
    File Name : Kruskal.cpp
    Description : 알고리즘 HW3 과제 중 2. Kruskal algorithm 구현 입니다. 

    Input : 수업에서 사용한 그래프 (Kruskal algorithm – 강의자료 15페이
    지에 있는 그래프)
    - Input 형태: vertex a 와 vertex b의 간선의 가중치가 c라고 하면 (a, b, 
    c)로 표현
    Output : Minimum spanning tree
    - Output 형태: Input 형태와 마찬가지로 vertex a 와 vertex b의 간선의 
    가중치가 c라고 하면 (a, b, c)로 표현
*/

// Heading Commnets
#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <set>
#include <chrono>

using namespace std;

// Struct 
struct Edge {
    int src, dest, weight;
};

// global vector for edge list
vector<Edge> edges;

// Find root 
int find(vector<int>& parent, int i) {
    if (parent[i] != i)
        parent[i] = find(parent, parent[i]);
    return parent[i];
}

// Using Union-Find for seek cycle
void Union(vector<int>& parent, vector<int>& rank, int a, int b) {
    int a_root = find(parent, a);
    int b_root = find(parent, b);

    if (rank[a_root] < rank[b_root]) {
        parent[a_root] = b_root;
    } else if (rank[a_root] > rank[b_root]) {
        parent[b_root] = a_root;
    } else {
        parent[b_root] = a_root;
        rank[a_root]++;
    }
}

// find MST using kruskal 
vector<Edge> kruskal(int vertex) {
    vector<Edge> result;  // Result MST vector

    // soring edges by weight, using lambda Func
    sort(edges.begin(), edges.end(), [](Edge a, Edge b) {
        return a.weight < b.weight;
    });

    // for find cycle
    vector<int> parent(vertex);
    vector<int> rank(vertex, 0);
    for (int v = 0; v < vertex; ++v)
        parent[v] = v;

    int e_count = 0;
    int idx = 0;
    while (e_count < vertex - 1 && idx < edges.size()) {
        Edge next_edge = edges[idx++];

        int x = find(parent, next_edge.src);
        int y = find(parent, next_edge.dest);

        // don't cycle
        if (x != y) {
            result.push_back(next_edge);
            Union(parent, rank, x, y);
            e_count++;
        }
    }

    return result;
}

int main() {

    auto start = chrono::high_resolution_clock::now();  

    // vertex amount
    int vertex = 6;

    // input Edges (a:0, b:1, c:2, d:3, e:4, f:5)
    edges.push_back({0, 1, 8});
    edges.push_back({0, 3, 2});
    edges.push_back({0, 4, 4});
    edges.push_back({1, 2, 1});
    edges.push_back({1, 3, 4});
    edges.push_back({1, 5, 2});
    edges.push_back({2, 5, 1});
    edges.push_back({3, 4, 3});
    edges.push_back({3, 5, 7});
    edges.push_back({4, 5, 9});
    
    


    // Use kruskal
    vector<Edge> mst = kruskal(vertex);

    // end clock
    auto end = chrono::high_resolution_clock::now();  // 끝 시간 측정

    // print result
    cout << "Minimum Spanning Tree:" << endl;
    for (auto& edge : mst) {
        cout << "(" << edge.src << ", " << edge.dest << ", " << edge.weight << ")" << endl;
    }

    // print Execution time 


    chrono::duration<double> duration = end - start;
    cout << "Execution time: " << duration.count() << " seconds" << endl;

    return 0;
}
