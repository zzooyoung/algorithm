/*
    File Name : CMM.cpp
    Description : 알고리즘 HW4 과제 중 2. Chained Matrix Multiplications(CMM) algorithm 구현

    Input : matrix_input.txt 
    Output : 읽어온 행렬 데이터, 정확한 차원 정보 및 최소 곱셈 횟수 출력
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <climits>
using namespace std;

// 행렬 크기 추출 함수
vector<int> readMatrixDimensions(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("파일을 열 수 없습니다: " + filename);
    }

    vector<int> dimensions;
    string line;
    bool inMatrix = false; // 현재 행렬을 읽는 중인지 확인

    // 파일에서 행렬 데이터 추출
    while (getline(file, line)) {
        // 행렬 정의 시작
        if (line.find("A") != string::npos && line.find("=") != string::npos) {
            inMatrix = true; // 행렬 데이터 읽기 시작
            int rowCount = 0; // 행 수
            int colCount = 0; // 열 수
            bool firstRow = true;

            // 행렬 이름 출력
            cout << line << endl;

            // 행렬 데이터를 읽음
            while (getline(file, line) && inMatrix) {
                // 먼저 `[[`와 `]]`를 처리
                if (line.find("[[") != string::npos) {
                    line = line.substr(line.find("[[") + 2); // '[[ 이후'
                    rowCount++; // 첫 줄도 행으로 반영
                }

                if (line.find("]]") != string::npos) {
                    line = line.substr(0, line.find("]]")); // ']] 이전'
                    inMatrix = false; // 행렬 데이터 끝
                }

                // 그런 다음 `[`, `]` 처리
                line.erase(remove(line.begin(), line.end(), '['), line.end());
                line.erase(remove(line.begin(), line.end(), ']'), line.end());

                // 데이터가 비어있지 않은 경우 처리
                if (!line.empty()) {
                    if (line.find("[[") == string::npos) {
                        rowCount++; // 첫 줄 외 나머지 줄의 행 증가
                    }
                    if (firstRow) {
                        // 첫 번째 줄에서 열 크기 계산
                        istringstream iss(line);
                        int temp;
                        int count = 0;
                        while (iss >> temp) {
                            count++;
                        }
                        colCount = count;
                        firstRow = false;
                    }
                    cout << "  " << line << endl; // 각 행 출력
                }
            }

            // 차원 추가
            if (dimensions.empty()) {
                dimensions.push_back(rowCount); // 첫 번째 행렬의 행 수
            } else {
                // 이전 행렬의 열 크기와 현재 행렬의 행 크기가 일치하는지 확인
                if (dimensions.back() != rowCount) {
                    cerr << "오류: 이전 행렬의 열 크기와 현재 행렬의 행 크기가 일치하지 않습니다." << endl;
                    throw runtime_error("행렬 크기 불일치");
                }
            }
            dimensions.push_back(colCount); // 현재 행렬의 열 수

            // 행렬 차원 출력
            cout << "  행렬 크기: " << rowCount << " x " << colCount << endl;
        }
    }

    file.close();
    return dimensions;
}


// 행렬 체인 곱셈 알고리즘
void matrixChainMultiplication(const vector<int>& dims) {
    int n = dims.size() - 1;
    vector<vector<int>> dp(n, vector<int>(n, 0));

    // DP 계산
    for (int L = 2; L <= n; ++L) { // L은 체인의 길이
        for (int i = 0; i < n - L + 1; ++i) {
            int j = i + L - 1;
            dp[i][j] = INT_MAX;
            for (int k = i; k < j; ++k) {
                int cost = dp[i][k] + dp[k + 1][j] + dims[i] * dims[k + 1] * dims[j + 1];
                if (cost < dp[i][j]) {
                    dp[i][j] = cost;
                }
            }
        }
    }

    // 결과 출력
    cout << "\n최소 곱셈 횟수: " << dp[0][n - 1] << endl;
    cout << "DP 테이블:" << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i <= j)
                cout << dp[i][j] << "\t";
            else
                cout << "\t";
        }
        cout << endl;
    }
}

int main() {
    string filename = "matrix_input.txt";

    try {
        // 파일에서 차원 읽기
        vector<int> dimensions = readMatrixDimensions(filename);

        // 읽은 차원 출력
        cout << "\n행렬 차원: ";
        for (size_t i = 0; i < dimensions.size(); ++i) {
            cout << dimensions[i] << " ";
        }
        cout << endl;

        // 결과 계산 및 출력
        matrixChainMultiplication(dimensions);
    } catch (const exception& e) {
        cerr << "오류: " << e.what() << endl;
    }

    return 0;
}
