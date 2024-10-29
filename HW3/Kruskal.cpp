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
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

struct Edge {
    int u, v, weight
}

int main(){
    // 실행 시간 시작 
    struct timespec begin, end ;
    clock_gettime(CLOCK_MONOTONIC, &begin);

    int vertex = 6; // number of vertex amount
    vector<Edge> edges;

    // 입력: (a:0, b:1, c:2, d:3, e:4, f:5)
    edges.push_back(Edge(0, 1, 8));
    edges.push_back(Edge(0, 3, 2));
    edges.push_back(Edge(0, 4, 4));
    edges.push_back(Edge(1, 2, 1));
    edges.push_back(Edge(1, 3, 4));
    edges.push_back(Edge(1, 5, 2));
    edges.push_back(Edge(2, 5, 1));
    edges.push_back(Edge(3, 4, 3));
    edges.push_back(Edge(3, 5, 7));
    edges.push_back(Edge(4, 5, 9));

    vector<Edge> mst = kruskal(vertex, edges);

    // 결과 출력
    clock_gettime(CLOCK_MONOTONIC, &end);
    cout << "Execution time : ";
    cout << (end.tv_sec - begin.tv_sec) + (end.tv_nsec - begin.tv_nsec) / 1000000000.0;
    cout << " seconds" << endl;
    }