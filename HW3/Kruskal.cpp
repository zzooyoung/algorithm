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
#include <ctime>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

// Struct for Edge
struct Edge {
    int src, dest, weight;
};

vector<Edge> edges;

// Find Parent
int find(vector<int>& parent, int t) {
    if(parent[i] != i){
        parent[i] = find(parent, parent[i]);
    }
    return parent[i];
}

// Union
void Union(vector<int>& parent, vector<int>& rank, int x, int y) {
    int x_root = find(parent, x);
    int y_root = find(parent, y);

    if (rank[x_root] < rank[y_root]){
        parent[x_root] = y_root;
    } else if (rank[x_root] > rank[y_root]) {
        parent[y_root] = x_root;
    } else {
        parent[y_root] = x_root;
        rank[x_root]++;
    }
}

// Kruskal Function
vector<Edge> kruskal(int vertex) {
    vector<Edge> result;
    sort(edges.begin(), edges.end(), [](Edge a, Edge b) {
        return a.weight < b.weight;
    });

    //Union-Find
    vector<int> parent(vertex);
    vector<int> rank(vertex, 0);
    for (int v = 0; v < vertex; ++v){
        parent[v] = v;
    }
    int edge = 0;
    int idx = 0;
    while (edge < vertex - 1 && idx < edges.size()) {
        Edge next_edge = edges[i++];

        int x = find(parent, next_edge.src);
        int y = find(parent, next_edge.dest);

        if (x != y) {
            result.push_back(next_edge);
            Union(parent, rank, x, y);
            e++;
        }
    }
    return result;
}

int main(){
    // 실행 시간 시작 
    struct timespec begin, end;
    clock_gettime(CLOCK_MONOTONIC, &begin);

    // Vertex amount
    int vertex = 6;

    // 입력: (a:0, b:1, c:2, d:3, e:4, f:5)
    edges.push_back({0, 1, 8});
    edges.push_back({0, 3, 2});
    edges.push_back({0, 4, 4});
    edges.push_back({1, 2, 1});
    edges.push_back({1, 3, 4});
    edges.push_back({2, 5, 1});
    edges.push_back({3, 4, 3});
    edges.push_back({3, 5, 7});
    edges.push_back({4, 5, 9});
    edges.push_back({2, 3, 2});

    vector<Edge> mst = kruskal(vertex);


    // 결과 출력
    cout << "Minimum Spanning Tree:" << endl;
    for (auto& edge : mst) {
        cout << "(" << edge.src << ", " << edge.dest << ", " << edge.weight << ")" << endl;
    }
    
    // 실행 시간 출력
    clock_gettime(CLOCK_MONOTONIC, &end);
    cout << "Execution time : ";
    cout << (end.tv_sec - begin.tv_sec) + (end.tv_nsec - begin.tv_nsec) / 1000000000.0;
    cout << " seconds" << endl;

    return 0;
}