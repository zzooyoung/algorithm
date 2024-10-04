/*
    File Name : MergeSort.cpp
    Description : 알고리즘 HW2 과제 중 1.Merge sort 구현 입니다. 

    input_sort.txt 파일을 입력 데이터로 설정
    Merge sort를 구현하여 올림차순으로 정렬 후 output_merge_sort.xlsx (or output_merge_sort.txt) 파일 출력
*/

// Heading Commnets
#include <iostream>
#include <ctime>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

void MERGE(int arr[], int left, int mid, int right) {
    int tmpLSize = mid - left + 1;
    int tmpRSize = right - mid;

    int* tmpLeft = new int[tmpLSize];
    int* tmpRight = new int[tmpRSize];

    for(int i = 0; i < tmpLSize; i++) {
        tmpLeft[i] = arr[left + i];
    }
    for(int j = 0; j < tmpRSize; j++) {
        tmpRight[j] = arr[mid+1+j];
    }

    int leftCount = 0, rightCount = 0, count = left;
    while (leftCount < tmpLSize && rightCount < tmpRSize) {
        if (tmpLeft[leftCount] <= tmpRight[rightCount]){
            arr[count] = tmpLeft[leftCount];
            leftCount++;
        }
        else {
            arr[count] = tmpRight[rightCount];
            rightCount++;
        }
        count++;
    }

    while(leftCount < tmpLSize) {
        arr[count] = tmpLeft[leftCount];
        leftCount++;
        count++;
    }
    while(rightCount < tmpRSize) {
        arr[count] = tmpRight[rightCount];
        rightCount++;
        count++;
    }

    delete[] tmpLeft;
    delete[] tmpRight;
}

void MERGESORT(int arr[], int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2; 

        MERGESORT(arr, left, mid);
        MERGESORT(arr, mid + 1, right);

        MERGE(arr, left, mid, right);
    }
}

int main(){
    // 실행 시간 시작 
    struct timespec begin, end ;
    clock_gettime(CLOCK_MONOTONIC, &begin);

    
    string line;
    ifstream file("input_sort.txt");

    vector<int> v;

    // 파일 읽기 
    if(file.is_open()){
        while(getline(file, line)) {
            int intLine = stoi(line);
            v.emplace_back(intLine);
        }
        file.close();
    } else {  
        cout << "Failed to open the file.";
        // 프로그램 종료 
    }

    int vSize = v.size();
    int* intInput = new int[vSize];

    for (int i = 0; i < vSize; ++i) {
        intInput[i] = v[i];
    }

    MERGESORT(intInput, 0, vSize - 1);


    // 파일 쓰기 
    ofstream outFile("output_merge_sort.txt");
    if (outFile.is_open()) {
        for (int i = 0; i <vSize; i++) {
            outFile << intInput[i] <<endl;
        }
        outFile.close();
    } else {
        cout << "Failed to write the file" << endl;
    }

    // 메모리 반환 
    delete[] intInput;

    // 결과 출력
    clock_gettime(CLOCK_MONOTONIC, &end);
    cout << "Execution time : ";
    cout << (end.tv_sec - begin.tv_sec) + (end.tv_nsec - begin.tv_nsec) / 1000000000.0;
    cout << " seconds" << endl;
    }