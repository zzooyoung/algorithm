/*
    File Name : MergeSort.cpp
    Description : 알고리즘 HW2 과제 중 1.Merge sort 구현 입니다. 

    input_sort.txt 파일을 입력 데이터로 설정
    Merge sort를 구현하여 올림차순으로 정렬 후 output_merge_sort.xlsx (or output_merge_sort.txt) 파일 출력
*/
#include <iostream>
#include <ctime>
using namespace std;

int main(){
    clock_t start, finish;
    double duration;
    start = clock();
    finish = clock();
    duration = (double)(finish - start) / CLOCKS_PER_SEC;
    cout << duration << "초" << endl;

    return 0;
}