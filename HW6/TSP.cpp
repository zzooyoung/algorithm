/*
    File Name : TSP.cpp
    Description : 알고리즘 HW6 과제 중 1. Traveling Salesman Problem (TSP) 구현

    Input : 강의 노트 Chapter 8-1, 11p의 점 A, B, C, D, E, F, G, H
    - 시작 점은 A로 고정
    - A=(0,3), B=(7,5), C=(6,0), D=(4,3), E=(1,0), F=(5,3), H=(4,1), G=(2,2)
    
    Output : 이동 순서, 이동 거리
*/

// include
#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <set>
#include <algorithm>

// namespace
using namespace std;

// Point struct
struct Point {
    char name;
    double x, y;
};

// Edge struct for Kruskal's Algorithm
struct Edge {
    int u, v;
    double weight;

    // Overload less-than operator for sorting edges by weight
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

// Calculate Distance of two points
double distance(double x1, double y1, double x2, double y2) {
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

// Find the parent (Union-Find)
int findParent(int node, vector<int>& parent) {
    if (parent[node] != node) {
        parent[node] = findParent(parent[node], parent);
    }
    return parent[node];
}

// Union of two sets
void unionSets(int u, int v, vector<int>& parent, vector<int>& rank) {
    int rootU = findParent(u, parent);
    int rootV = findParent(v, parent);
    
    if (rootU != rootV) {
        // Union by rank
        if (rank[rootU] > rank[rootV]) {
            parent[rootV] = rootU;
        } else if (rank[rootU] < rank[rootV]) {
            parent[rootU] = rootV;
        } else {
            parent[rootV] = rootU;
            rank[rootU]++;
        }
    }
}

// Kruskal's Algorithm to find MST
vector<pair<int, int>> kruskal(const vector<Edge>& edges, int n) {
    vector<int> parent(n), rank(n, 0);
    vector<pair<int, int>> mstEdges;

    // Initialize the disjoint-set
    for (int i = 0; i < n; ++i) {
        parent[i] = i;
    }

    // Sort edges by weight
    vector<Edge> sortedEdges = edges;
    sort(sortedEdges.begin(), sortedEdges.end());

    // Kruskal's algorithm: process edges in sorted order
    for (const Edge& e : sortedEdges) {
        int u = e.u, v = e.v;
        if (findParent(u, parent) != findParent(v, parent)) {
            unionSets(u, v, parent, rank);
            mstEdges.push_back({u, v});
        }
    }

    return mstEdges;
}

// DFS to traverse the MST and find the travel order
void dfs(int node, const vector<vector<int>>& tree, vector<int>& order, vector<bool>& visited) {
    visited[node] = true;
    order.push_back(node);

    // Visit all unvisited nodes
    for (int next : tree[node]) {
        if (!visited[next]) {
            dfs(next, tree, order, visited);
        }
    }
}

// Function to calculate the total distance of the travel order
double calculateDistance(const vector<int>& order, const vector<double>& graph, int n) {
    double totalDistance = 0.0;
    set<int> visited;
    int prev = -1;

    for (int node : order) {
        if (visited.find(node) == visited.end()) {
            if (prev != -1) {
                int idx = prev * n + node;
                totalDistance += graph[idx];  // Add the distance from previous node to current
            }
            prev = node;
            visited.insert(node);
        }
    }
    // Add the distance to return to the starting point (A)
    int idx = prev * n + order[0];
    totalDistance += graph[idx];
    return totalDistance;
}

int main() {
    // Input Points
    vector<Point> points = {
        {'A', 0, 3}, {'B', 7, 5}, {'C', 6, 0}, {'D', 4, 3},
        {'E', 1, 0}, {'F', 5, 3}, {'G', 2, 2}, {'H', 4, 1}
    };

    int n = points.size(); // n is number of city(Points)
    
    // Distance between two points
    vector<double> graph(n * n, 0);
    vector<Edge> edges;

    // Calculate the distance between each pair of points and create edges
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i != j) {
                double dist = distance(points[i].x, points[i].y, points[j].x, points[j].y);
                edges.push_back({i, j, dist});
                graph[i * n + j] = dist;
            }
        }
    }

    // Find MST using Kruskal Algorithm
    vector<pair<int, int>> mstEdges = kruskal(edges, n);

    // Convert MST edges into a tree
    vector<vector<int>> tree(n);
    for (const auto& edge : mstEdges) {
        tree[edge.first].push_back(edge.second); // first : start point of edge
        tree[edge.second].push_back(edge.first); // second : end point of edge
    }

    // DFS to determine the travel order
    vector<int> order;
    vector<bool> visited(n, false);
    dfs(0, tree, order, visited);

    // Calculate the total travel distance using "visited"
    double totalDistance = calculateDistance(order, graph, n);

    // Print Result
    cout << "Travel Order: ";
    for (int i : order) {
        cout << points[i].name << " ";
    }
    cout << points[order[0]].name << endl;  // Return to the starting point (A)

    cout << "Total Distance: " << totalDistance << endl;

    return 0;
}
