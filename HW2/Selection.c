/*
    File Name : Selection.c
    Description : 알고리즘 HW2 과제 중 3. Selection 구현입니다.
    input_sort.txt 파일을 입력 데이터로 설정
    Selection algorithm을 구현하여 50번째와 70번째 숫자를 출력
*/

#include <stdio.h>
#include <time.h>

int main() {
    // 시작 시간 측정
    clock_t start = clock();

    // 실행할 코드 (예시로 간단한 for문)

    FILE* fs;
    fs = fopen("input_sort.txt", "r");    
    if (fs == NULL) {
        printf("Failed to open input_sort.txt\n");
        return 0;
    }

    while (fscanf(fs, "%d", &numbers))

    // 종료 시간 측정
    clock_t end = clock();

    // 경과 시간 계산
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;

    // 경과 시간 출력 (초 단위)
    printf("Execution time: %f seconds\n", time_spent);

    return 0;
}
