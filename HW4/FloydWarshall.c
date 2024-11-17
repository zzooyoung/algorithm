/*
    File Name : FloydWarshall.c
    Description : 알고리즘 HW4 과제 중 1. Floyd-Warshall algorithm 구현 입니다. 
    input: Chapter 4-1, 52p의 그래프
    Output: Chapter 5-1, 6p과 같은 형태의 테이블
*/

// Heading File Import
#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include <time.h>

#define VERTEX 9  // Vertex Amount

// Graph Matrix
int graph[VERTEX][VERTEX] = {
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

// City Names
const char *cityNames[VERTEX] = {"서울", "인천", "수원", "대전", "전주", "광주", "대구", "울산", "부산"};

// Run Floyd-Warshall Algorithm
void floydWarshall(int graph[VERTEX][VERTEX], double distances[VERTEX][VERTEX]) {
    for (int i = 0; i < VERTEX; i++)
        for (int j = 0; j < VERTEX; j++) // Set 0 to INF
            distances[i][j] = (graph[i][j] == 0 && i != j) ? INT_MAX : graph[i][j];

    for (int k = 0; k < VERTEX; k++) {
        for (int i = 0; i < VERTEX; i++) {
            for (int j = 0; j < VERTEX; j++) {
                if (distances[i][k] != INT_MAX && distances[k][j] != INT_MAX && // min change
                    distances[i][k] + distances[k][j] < distances[i][j]) {
                    distances[i][j] = distances[i][k] + distances[k][j];
                }
            }
        }
    } 
}

// Function to calculate Running Time
double getRunningTime(struct timespec start, struct timespec end) {
    double start_ms = (double)start.tv_sec * 1000.0 + (double)start.tv_nsec / 1e6;
    double end_ms = (double)end.tv_sec * 1000.0 + (double)end.tv_nsec / 1e6;
    return end_ms - start_ms;
}

int main() {
    double distances[VERTEX][VERTEX];
    struct timespec start, end;

    // Start time
    clock_gettime(CLOCK_MONOTONIC, &start);

    // Run Floyd-Warshall
    floydWarshall(graph, distances);

    

    // Print result
    printf("      서울  인천  수원  대전  전주  광주  대구  울산  부산\n");
    for (int i = 0; i < VERTEX; i++) {
        printf("%s ", cityNames[i]);
        for (int j = 0; j < VERTEX; j++) {
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

    // End time
    clock_gettime(CLOCK_MONOTONIC, &end);

    double runtime_ms = getRunningTime(start, end);

    printf("\nTotal Running Time: %.6f ms\n", runtime_ms);

    return 0;
}
