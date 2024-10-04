/*
    File Name : Selection.c
    Description : 알고리즘 HW2 과제 중 3. Selection 구현입니다.
    input_sort.txt 파일을 입력 데이터로 설정
    Selection algorithm을 구현하여 50번째와 70번째 숫자를 출력
*/

// Heading Commnets
#include <stdio.h>
#include <time.h>

#define SIZE 1000 // 배열 크기 설정 (기본 1000)

int SWAPPING(int arr[], int left, int right) {
    int pivot = arr[right]; // 배열 가장 오른쪽을 Pivot 으로 설정 
    int i = left - 1;

    for(int j = left; j < right; j++) {
        if (arr[j] < pivot) {
            i++;

            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    int temp = arr[i+1];
    arr[i + 1] = arr[right];
    arr[right] = temp;
    return i + 1;
}
// Selection 수행 함수 
int SELECTION(int arr[], int left, int right, int k) {
    if(left == right) {
        return arr[left];
    }
    int p = SWAPPING(arr, left, right);
    int S = p - left + 1;

    if(k == S) {
        return arr[p];
    } else if (k < S){
        return SELECTION(arr, left, p - 1, k); 
    } else {
        return SELECTION(arr, p + 1, right, k - S);
    }
}

// Main 함수 
int main() {
    // 시작 시간 측정
    clock_t start = clock();

    // 파일 열기
    FILE* fs = fopen("input_sort.txt", "r");
    if (fs == NULL) {
        printf("Failed to open input_sort.txt\n");
        return 0;
    }


    int intInput[SIZE];
    int count = 0;

    while (fscanf(fs, "%d", &intInput[count]) != EOF && count < SIZE) {
        count++;
    }
    fclose(fs);

    // 정렬 전 데이터 개수 확인
    if (count < 70) {
        printf("There are not 70 numbers in the file.\n");
        return 0;
    }

    int result50 = SELECTION(intInput, 0, count - 1, 50);
    int result70 = SELECTION(intInput, 0, count - 1, 70);

    // 50번째와 70번째 숫자 출력 
    printf("the 50th number: %d\n", result50);
    printf("the 70th number: %d\n", result70);

    // 종료 시간 측정
    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Execution time: %f seconds\n", time_spent);

    return 0;
}
