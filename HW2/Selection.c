#include <stdio.h>
#include <time.h>

#define SIZE 1000 // 배열 크기 설정 (기본 1000)

// SWAPPING 함수 수정 (오름차순을 위한 비교 수정)
int SWAPPING(int arr[], int left, int right) {
    int pivot = arr[right]; // 배열 가장 오른쪽을 Pivot 으로 설정
    int i = left - 1;

    for (int j = left; j < right; j++) {
        if (arr[j] <= pivot) { // Pivot 기준으로 작거나 같은 경우 처리
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    // Pivot을 올바른 위치로 이동
    int temp = arr[i + 1];
    arr[i + 1] = arr[right];
    arr[right] = temp;
    return i + 1;
}

// Selection 수행 함수
int SELECTION(int arr[], int left, int right, int k) {
    if (left == right) {
        return arr[left];
    }
    int p = SWAPPING(arr, left, right);
    int S = p - left + 1;

    if (k == S) {
        return arr[p]; // Pivot 위치가 우리가 찾는 위치일 때
    } else if (k < S) {
        return SELECTION(arr, left, p - 1, k); // 왼쪽 부분 배열에서 찾기
    } else {
        return SELECTION(arr, p + 1, right, k - S); // 오른쪽 부분 배열에서 찾기
    }
}

// Main 함수
int main() {
    // 시작 시간 측정
    clock_t start = clock();

    // 파일 열기
    FILE *fs = fopen("input_sort.txt", "r");
    if (fs == NULL) {
        printf("Failed to open input_sort.txt\n");
        return 0;
    }

    int intInput[SIZE];
    int count = 0;

    // 파일에서 데이터 읽기
    while (fscanf(fs, "%d", &intInput[count]) != EOF && count < SIZE) {
        count++;
    }
    fclose(fs);

    // 정렬 전 데이터 개수 확인
    if (count < 70) {
        printf("There are not 70 numbers in the file.\n");
        return 0;
    }

    // SELECTION 알고리즘을 이용해 50번째와 70번째 숫자 찾기
    int result50 = SELECTION(intInput, 0, count - 1, 50);
    int result70 = SELECTION(intInput, 0, count - 1, 70);

    // 결과 출력
    printf("The 50th number: %d\n", result50);
    printf("The 70th number: %d\n", result70);

    // 종료 시간 측정
    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Execution time: %f seconds\n", time_spent);

    return 0;
}
