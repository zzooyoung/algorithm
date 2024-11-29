/*
    File Name : Insertion.cpp
    Description : 알고리즘 HW5 과제 중 3. Insertion Sorting algorithm 구현

    Input : input.txt
    Output : insertion_output.txt
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

// Insertion Sort Function
void insertionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int CurrentElement = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > CurrentElement) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        // A[j+1] <- CurrentElement
        arr[j + 1] = CurrentElement;
    }
}

// 파일에서 숫자를 읽어오는 함수
bool readNumbersFromFile(const string& filename, vector<int>& arr) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "File Read Error: " << filename << endl;
        return false;
    }

    int num;
    while (file >> num) {
        arr.push_back(num); 
    }

    file.close();
    return true;
}

// Write Result to file
void writeNumbersToFile(const string& filename, const vector<int>& arr) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "File Open Error: " << filename << endl;
        return;
    }

    for (size_t i = 0; i < arr.size(); ++i) {
        file << arr[i] << endl;
    }

    file.close();
}

int main() {
    vector<int> arr;

    if (!readNumbersFromFile("input.txt", arr)) {
        return 1;  // File Read Error
    }

    // Insertion Sort Execution
    insertionSort(arr);

    // Write insertion_output.txt
    writeNumbersToFile("insertion_output.txt", arr);

    cout << "Save insertion_output.txt" << endl;

    return 0;
}
