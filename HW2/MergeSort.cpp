/*
    File Name : MergeSort.cpp
    Description : 알고리즘 HW2 과제 중 1.Merge sort 구현 입니다. 

    input_sort.txt 파일을 입력 데이터로 설정
    Merge sort를 구현하여 올림차순으로 정렬 후 output_merge_sort.xlsx (or output_merge_sort.txt) 파일 출력
*/
#include <iostream>
#include <ctime>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

void MERGESORT(int arr[], int left, int right) {
    
}

int main(){
    struct timespec begin, end ;
    clock_gettime(CLOCK_MONOTONIC, &begin);
    string line;
    ifstream file("input_sort.txt");

    vector<int> v;

    if(file.is_open()){
        while(getline(file, line)) {
            int intLine = stoi(line);
            v.emplace_back(intLine);
        }
    } else {  
        cout << "파일 열기를 실패 했습니다.";
        // 프로그램 종료 
    }

    int vSize = v.size();
    int* intInput = new int[vSize];

    for (int i = 0; i < vSize; ++i) {
        intInput[i] = v[i];
    }





    clock_gettime(CLOCK_MONOTONIC, &end);
    cout << "실행 시각 :";
    cout << (end.tv_sec - begin.tv_sec) + (end.tv_nsec - begin.tv_nsec) / 1000000000.0 << endl;
    }