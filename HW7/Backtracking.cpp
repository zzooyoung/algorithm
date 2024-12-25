/*
    File Name : Backtracking.cpp
    Description : 알고리즘 HW7 과제 중 2. Backtracking Algorithm 구현

    Input: 강의자료 Chapter 9-1, 38p의 그래프 (시작점 A 가정)

    Output: [A, B, E, C, D, A], 거리 = 16
*/
/* Heading Comments
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

// Edge Struct
struct Edge {
    char from;
    char to;
    int weight;
};

// Input Edges
vector<Edge> edges = {
    {'A', 'B', 2},
    {'A', 'D', 3},
    {'A', 'C', 7},
    {'B', 'C', 3},
    {'B', 'D', 5},
    {'B', 'E', 6},
    {'C', 'E', 1},
    {'D', 'E', 9},
    {'D', 'C', 4},
    {'E', 'A', 10}
};

int bestDistance = INT_MAX;
vector<char> bestSolution;

int getDistance(char from, char to) {
    for (const auto &edge : edges) {
        if ((edge.from == from && edge.to == to) || (edge.from == to && edge.to == from)) {
            return edge.weight;
        }
    }
    return INT_MAX; 
}

int calculateTourDistance(const vector<char> &tour) {
    int totalDistance = 0;
    for (size_t i = 0; i < tour.size() - 1; ++i) {
        int distance = getDistance(tour[i], tour[i + 1]);
        if (distance == INT_MAX) return INT_MAX;
        totalDistance += distance;
    }
    return totalDistance;
}

// Backtracking
void BackTracking(vector<char> &tour, vector<char> &remaining) {
    if (remaining.empty()) {
        tour.push_back(tour[0]);
        int currentDistance = calculateTourDistance(tour);
        if (currentDistance < bestDistance) {
            bestDistance = currentDistance;
            bestSolution = tour;
        }
        tour.pop_back();
        return;
    }

    for (size_t i = 0; i < remaining.size(); ++i) {
        char nextCity = remaining[i];
        tour.push_back(nextCity);
        remaining.erase(remaining.begin() + i);

        int currentDistance = calculateTourDistance(tour);
        if (currentDistance < bestDistance) {
            BackTracking(tour, remaining);
        }

        // Recovery
        remaining.insert(remaining.begin() + i, nextCity);
        tour.pop_back();
    }
}

int main() {
    // Start
    vector<char> tour = {'A'};
    vector<char> remaining = {'B', 'C', 'D', 'E'};

    BackTracking(tour, remaining);

    // Print Result
    cout << "Output: [";
    for (size_t i = 0; i < bestSolution.size(); ++i) {
        cout << bestSolution[i];
        if (i < bestSolution.size() - 1) cout << ", ";
    }
    cout << "], 거리 = " << bestDistance << endl;

    return 0;
}
