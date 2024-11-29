#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

// MSD 방식의 카운팅 정렬 (자릿수 기준으로 정렬)
void countingSortMSD(vector<int>& arr, int exp, int base) {
    int n = arr.size();
    vector<int> output(n);  // 출력 배열
    vector<int> count(base, 0);  // 자릿수 0~base-1까지의 카운트 배열

    // 현재 자릿수에 대해 카운트
    for (int i = 0; i < n; i++) {
        count[(arr[i] / exp) % base]++;
    }

    // 카운트 배열을 누적합으로 변환
    for (int i = 1; i < base; i++) {
        count[i] += count[i - 1];
    }

    // 출력 배열에 자릿수에 맞는 값들 배치
    for (int i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % base] - 1] = arr[i];
        count[(arr[i] / exp) % base]--;
    }

    // 정렬된 배열을 arr에 저장
    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }
}

// MSD 방식의 Radix Sort
void radixSortMSD(vector<int>& arr, int base = 10) {
    int maxVal = *max_element(arr.begin(), arr.end());  // 최대값 찾기
    int maxDigits = to_string(maxVal).length();  // 최대 자릿수 계산

    // exp는 10^k (최상위 자릿수)로 시작
    for (int exp = pow(base, maxDigits - 1); exp > 0; exp /= base) {
        countingSortMSD(arr, exp, base);  // 각 자릿수에 대해 counting sort 수행
    }
}

// LSD 방식의 카운팅 정렬
void countingSortLSD(vector<int>& arr, int exp) {
    int n = arr.size();
    vector<int> output(n);  // 출력 배열
    vector<int> count(10, 0);  // 자릿수 0~9까지의 카운트 배열

    // 현재 자릿수에 대해 카운트
    for (int i = 0; i < n; i++) {
        count[(arr[i] / exp) % 10]++;
    }

    // 카운트 배열을 누적합으로 변환
    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }

    // 출력 배열에 자릿수에 맞는 값들 배치
    for (int i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

    // 정렬된 배열을 arr에 저장
    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }
}

// LSD 방식의 Radix Sort
void radixSortLSD(vector<int>& arr) {
    int maxVal = *max_element(arr.begin(), arr.end());  // 최대값 찾기
    for (int exp = 1; maxVal / exp > 0; exp *= 10) {
        countingSortLSD(arr, exp);  // 각 자릿수에 대해 counting sort 수행
    }
}

// 파일에서 숫자들을 읽어 배열로 반환
vector<int> readNumbersFromFile(const string& filename) {
    ifstream file(filename);
    vector<int> arr;
    int num;

    if (!file.is_open()) {
        cerr << "파일을 열 수 없습니다." << endl;
        return arr;
    }

    while (file >> num) {
        arr.push_back(num);
    }

    file.close();
    return arr;
}

// 배열을 파일에 저장
void writeNumbersToFile(const string& filename, const vector<int>& arr) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "파일을 열 수 없습니다." << endl;
        return;
    }

    for (const int& num : arr) {
        file << num << " ";
    }
    file << endl;

    file.close();
}

int main() {
    // input.txt에서 숫자 읽기
    vector<int> arr = readNumbersFromFile("input.txt");

    if (arr.empty()) {
        return 1;  // 파일이 비어 있으면 종료
    }

    // LSD 방식으로 정렬
    vector<int> arrLSD = arr;
    radixSortLSD(arrLSD);
    writeNumbersToFile("radix_lsd_output.txt", arrLSD);

    // MSD 방식으로 정렬
    vector<int> arrMSD = arr;
    radixSortMSD(arrMSD);
    writeNumbersToFile("radix_msd_output.txt", arrMSD);

    cout << "정렬 완료! 결과는 radix_lsd_output.txt와 radix_msd_output.txt에 저장되었습니다." << endl;

    return 0;
}
