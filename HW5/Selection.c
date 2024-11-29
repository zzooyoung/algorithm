/*
    File Name : Selection.c
    Description : 알고리즘 HW5 과제 중 2. Selection Sorting Algorithm 구현 입니다. 
    input: input.txt
    Output: selection_output.txt
*/

// Heading File Import
#include <stdio.h>
#include <stdlib.h>

// Exection Selection Sort 
void selectionSort(int arr[], int n) {
    int i, j, minIdx, temp;
    for (i = 0; i < n - 1; i++) {
        minIdx = i;
        for (j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }
        // Swap arr[i] <-> min
        temp = arr[minIdx];
        arr[minIdx] = arr[i];
        arr[i] = temp;
    }
}

// 파일에서 숫자 읽기
int readNumbersFromFile(const char* filename, int* arr) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("File Read Error\n");
        return -1;  // File Read Error
    }

    int num, i = 0;
    while (fscanf(file, "%d", &num) == 1) {
        arr[i++] = num;  // Read File into arr
    }
    fclose(file);
    return i;  // arr Size return
}

// Write to File
void writeNumbersToFile(const char* filename, int* arr, int n) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("File Read Error\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        fprintf(file, "%d\n", arr[i]);
    }
    fclose(file);
}

int main() {
    int arr[1000];
    int n;

    // Read input.txt
    n = readNumbersFromFile("input.txt", arr);
    if (n == -1) {
        return 1;  // File Read Error
    }

    // Selection Sort Execution
    selectionSort(arr, n);

    // selection_output.txt
    writeNumbersToFile("selection_output.txt", arr, n);

    printf("Save selection_output.txt\n");

    return 0;
}
