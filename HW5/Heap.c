/*
    File Name : Heap.c
    Description : 알고리즘 HW5 과제 중 5. Heap Sorting algorithm 구현 입니다. 
    input: input.txt
    Output: heap_output.txt
*/

// Heading File Import
#include <stdio.h>
#include <stdlib.h>

void DownHeap(int arr[], int n, int i) {
    int largest = i; // root (Max)
    int left = 2 * i + 1; // i left child
    int right = 2 * i + 2; // i right child

    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }

    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }


    if (largest != i) {
        // A[i] <-> A[bigger]
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;

        DownHeap(arr, n, largest);
    }
}

// Heap Sort
void heapSort(int arr[], int n) {
    // Max Heap 
    for (int i = n / 2 - 1; i >= 0; i--) {
        DownHeap(arr, n, i);
    }

    for (int i = n - 1; i >= 1; i--) {
        // Swap root(Max) <-> last node
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;


        DownHeap(arr, i, 0);
    }
}

// Read Numbers From Rile
int* readNumbersFromFile(const char* filename, int* size) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("File Open Error\n");
        return NULL;
    }

    int capacity = 10; // Capacity
    *size = 0;
    int* arr = (int*)malloc(capacity * sizeof(int));

    while (fscanf(file, "%d", &arr[*size]) == 1) {
        (*size)++;
        // Capacity x 2
        if (*size >= capacity) {
            capacity *= 2;
            arr = (int*)realloc(arr, capacity * sizeof(int));
        }
    }

    fclose(file);
    return arr;
}

// Write Numbers to File
void writeNumbersToFile(const char* filename, int* arr, int size) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("File IO Error \n");
        return;
    }

    for (int i = 0; i < size; i++) {
        fprintf(file, "%d\n", arr[i]);
    }
    fprintf(file, "\n");

    fclose(file);
}

int main() {
    int size = 0;
    // Read File
    int* arr = readNumbersFromFile("input.txt", &size);
    if (arr == NULL) {
        return 1;
    }

    // Heap Sort Execution
    heapSort(arr, size);

    // Write Numbers to Tile
    writeNumbersToFile("heap_output.txt", arr, size);

    printf("Save heap_output.txt\n");

    // Memory Free
    free(arr);

    return 0;
}
