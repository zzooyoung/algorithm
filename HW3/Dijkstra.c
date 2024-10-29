#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include <time.h>

#define V 9 // 정점의 개수 (도시 수)

// 각 도시에 대한 인덱스 정의
enum Cities { SEOUL, INCHEON, SUWON, DAEJEON, JEONJU, GWANGJU, DAEGU, ULSAN, BUSAN };

// 거리 행렬 (그래프의 인접 행렬 표현)
int graph[V][V] = {
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

// 최단 거리를 아직 찾지 못한 정점 중에서 최소 거리를 가지는 정점을 찾는 함수
int minDistance(int dist[], bool sptSet[]) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

// 주어진 시작 정점에서 모든 다른 정점으로의 최단 거리를 계산하는 Dijkstra 알고리즘
void dijkstra(int graph[V][V], int src, double distances[V]) {
    int dist[V];
    bool sptSet[V];

    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX, sptSet[i] = false;

    dist[src] = 0;

    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, sptSet);
        sptSet[u] = true;

        for (int v = 0; v < V; v++)
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
    }

    for (int i = 0; i < V; i++)
        distances[i] = (double)dist[i];
}

// 모든 도시 쌍 간 최단 거리를 구하고 결과를 출력하는 함수
void calculateAllPairsShortestPath() {
    double distances[V][V];
    clock_t start, end;

    start = clock();

    for (int i = 0; i < V; i++)
        dijkstra(graph, i, distances[i]);

    end = clock();
    double runtime = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("도시 간 거리 매트릭스:\n");
    printf("       서울 인천 수원 대전 전주 광주 대구 울산 부산\n");
    for (int i = 0; i < V; i++) {
        switch (i) {
            case SEOUL: printf("서울 "); break;
            case INCHEON: printf("인천 "); break;
            case SUWON: printf("수원 "); break;
            case DAEJEON: printf("대전 "); break;
            case JEONJU: printf("전주 "); break;
            case GWANGJU: printf("광주 "); break;
            case DAEGU: printf("대구 "); break;
            case ULSAN: printf("울산 "); break;
            case BUSAN: printf("부산 "); break;
        }
        for (int j = 0; j < V; j++) {
            if (distances[i][j] == INT_MAX)
                printf(" INF ");
            else
                printf(" %4.1f ", distances[i][j]);
        }
        printf("\n");
    }

    printf("\nRunning time: %f seconds\n", runtime);
}

int main() {
    calculateAllPairsShortestPath();
    return 0;
}
