/*
    File Name : Selection.c
    Description : 알고리즘 HW2 과제 중 3. Selection 구현입니다.
    input_sort.txt 파일을 입력 데이터로 설정
    Selection algorithm을 구현하여 50번째와 70번째 숫자를 출력
*/

#include <stdio.h>
#include <time.h>

#define SIZE 1000 // 배열 크기 설정 (파일에 들어 있는 데이터 수에 맞게 설정)

int PARTITION(int arr[], int left, int right) {
    int pivot = arr[right];
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

int SELECTION(int arr[], int left, int right, int k) {
    if(left == right) {
        return arr[left];
    }
    int p = PARTITION(arr, left, right);
    int S = p - left + 1;

    if(k == S) {
        return arr[p];
    } else if (k < S){
        return SELECTION(arr, left, p - 1, k); 
    } else {
        return SELECTION(arr, p + 1, right, k - S);
    }
}

int main() {
    // 시작 시간 측정
    clock_t start = clock();

    // 파일 열기
    FILE* fs = fopen("input_sort.txt", "r");
    if (fs == NULL) {
        printf("Failed to open input_sort.txt\n");
        return 0;
    }

    // 파일에서 숫자 읽어오기
    int intInput[SIZE];
    int count = 0;

    while (fscanf(fs, "%d", &intInput[count]) != EOF && count < SIZE) {
        count++;
    }
    fclose(fs); // 파일을 닫음

    // 정렬 전 데이터 개수 확인
    if (count < 70) {
        printf("There are not 70 numbers in the file.\n");
        return 0;
    }

    int result50 = SELECTION(intInput, 0, count - 1, 50);
    int result70 = SELECTION(intInput, 0, count - 1, 70);

    // 50번째와 70번째 숫자 출력 (인덱스는 0부터 시작하므로 49번째, 69번째)
    printf("the 50th number: %d\n", result50);
    printf("the 70th number: %d\n", result70);

    // 종료 시간 측정
    clock_t end = clock();

    // 경과 시간 계산
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;

    // 경과 시간 출력 (초 단위)
    printf("Execution time: %f seconds\n", time_spent);

    return 0;
}
