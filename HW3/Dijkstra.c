/*
    File Name : Dijkstra.c
    Description : 알고리즘 HW3 과제 중 4. Dijkstra Shortest Path algorithm 구현 입니다. 
    input: Chapter 4-1, 52p의 그래프
    output: 아래의 형태로 각 도시 간 거리 출력 (안에 거리는 실제와 다를
수 있음)
*/

// Heading File Import
#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include <time.h>

#define vertex 9  // Vertex Amount

// Graph Matrix
int graph[vertex][vertex] = {
    {0, 12, 0, 0, 0, 0, 0, 0, 0},
    {12, 0, 15, 0, 0, 0, 0, 0, 0},
    {0, 15, 0, 10, 0, 0, 0, 0, 0},
    {0, 0, 10, 0, 3, 0, 0, 0, 0},
    {0, 0, 0, 3, 0, 13, 0, 0, 0},
    {0, 0, 0, 0, 13, 0, 15, 0, 0},
    {0, 0, 0, 0, 0, 15, 0, 19, 9},
    {0, 0, 0, 0, 0, 0, 19, 0, 5},
    {0, 0, 0, 0, 0, 0, 9, 5, 0}
};

// city Names
const char *cityNames[vertex] = {"서울", "인천", "수원", "대전", "전주", "광주", "대구", "울산", "부산"};

// return min distance index
int minDistance(int dist[], bool sptSet[]) {
    int min = INT_MAX, min_index; 

    // find min distance
    for (int v = 0; v < vertex; v++) 
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

// calculate distance
void dijkstra(int graph[vertex][vertex], int src, double distances[vertex]) {
    int dist[vertex];
    bool sptSet[vertex];

    for (int i = 0; i < vertex; i++)
        dist[i] = INT_MAX, sptSet[i] = false; // initializing inf

    dist[src] = 0;

    for (int count = 0; count < vertex - 1; count++) {
        int u = minDistance(dist, sptSet);
        sptSet[u] = true;

        for (int v = 0; v < vertex; v++) // renew dist[v]
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
    }

    for (int i = 0; i < vertex; i++)
        distances[i] = (double)dist[i];
}

int main() {
    double distances[vertex][vertex];
    clock_t start, end;

    // start time 
    start = clock();



    for (int i = 0; i < vertex; i++)
        dijkstra(graph, i, distances[i]);

    end = clock();
    double runtime = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("      서울  인천  수원  대전  전주  광주  대구  울산  부산\n");
    for (int i = 0; i < vertex; i++) {
        printf("%s ", cityNames[i]); 
        for (int j = 0; j < vertex; j++) {
            if (j < i) {
                printf("      ");
            } else if (distances[i][j] == INT_MAX) {
                printf(" INF ");
            } else {
                printf(" %4.1f ", distances[i][j]);
            }
        }
        printf("\n");
    }

    printf("\nRunning time: %f seconds\n", runtime);
    
    return 0;
}
