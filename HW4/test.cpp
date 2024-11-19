#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <regex>
#include <vector>
#include <climits> // INT_MAX 사용
#include <iomanip> // setw 사용

using namespace std;

// Global Vector Matrix Dimensions
vector<pair<int, int>> matrixSize;

// for matrix Size
void calculateMatrixSize(const string& filePath) {
    ifstream file(filePath); // file read
    if (!file.is_open()) {
        cerr << "파일을 열 수 없습니다: " << filePath << endl;
        return;
    }

    // read full txt 
    string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();

    // filtering matrix
    regex matrixRegex(R"(\[\[([\s\S]*?)\]\])");
    smatch match;

    int matrixCount = 1;

    while (regex_search(content, match, matrixRegex)) { // matix searching
        string matrixData = match[1].str();

        // Find "\n"
        matrixData.erase(remove(matrixData.begin(), matrixData.end(), '\n'), matrixData.end());
        matrixData.erase(remove(matrixData.begin(), matrixData.end(), '\r'), matrixData.end());

        stringstream ss(matrixData);
        string row;
        int rowCount = 0;
        int colCount = 0;

        // Each row of the matrix is '[', ']'
        regex rowRegex(R"(\[([^\]]+)\])");
        smatch rowMatch;

        while (regex_search(matrixData, rowMatch, rowRegex)) {
            string rowData = rowMatch[1].str();
            stringstream rowStream(rowData);
            string element;
            int currentColCount = 0;

            while (rowStream >> element) {
                currentColCount++;
            }

            if (currentColCount > 0) { // empty col
                rowCount++;
                if (colCount == 0) {
                    colCount = currentColCount;
                } else if (colCount != currentColCount) {
                    cerr << "행렬 A" << matrixCount << "의 열 크기가 일치하지 않습니다." << endl;
                    return;
                }
            }

            matrixData = rowMatch.suffix().str(); // next row
        }

        // Add matrixSize 
        matrixSize.emplace_back(rowCount, colCount);

        cout << "행렬 A" << matrixCount << ": " << rowCount << "행 " << colCount << "열" << endl;
        matrixCount++;

        content = match.suffix().str(); // next matrix
    }
}

// Chained Matrix Multiplication Func
void matrixChainMultiplication() {
    int n = matrixSize.size(); 
    if (n == 0) {
        cerr << "행렬 데이터가 없습니다." << endl;
        return;
    }

    // matrix vector
    vector<int> dims;
    dims.push_back(matrixSize[0].first); // 0 matrix row size
    for (auto dim : matrixSize) {
        dims.push_back(dim.second); // 각 행렬 열 크기 추가
    }


    // initialize table 
    vector<vector<int>> cost(n, vector<int>(n, 0));
    vector<vector<int>> split(n, vector<int>(n, 0));

    for (int L = 1; L < n; ++L) { 
        for (int i = 0; i < n - L; ++i) {
            int j = i + L;
            cost[i][j] = INT_MAX;

            for (int k = i; k < j; ++k) {
                // calculation
                int q = cost[i][k] + cost[k + 1][j] + dims[i] * dims[k + 1] * dims[j + 1];
                if (q < cost[i][j]) {
                    cost[i][j] = q;
                    split[i][j] = k; 
                }
            }
        }
    }

    // print result table
    cout << "\n최소 곱셈 횟수 테이블:" << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i > j) {
                cout << setw(5) << " "; // empty
            } else {
                cout << setw(5) << (cost[i][j] == INT_MAX ? 0 : cost[i][j]);
            }
        }
        cout << endl;
    }
}

// Main 
int main() {
    string filePath = "./matrix_input.txt"; // File Path

    // Matrix rows, cols size
    calculateMatrixSize(filePath);

    // for file read test
    cout << "\n저장된 행렬 크기 출력:" << endl;
    for (size_t i = 0; i < matrixSize.size(); ++i) {
        cout << "행렬 A" << i + 1 << ": " << matrixSize[i].first
             << "행 " << matrixSize[i].second << "열" << endl;
    }

    // Chained Matrix Multiplication Execute
    matrixChainMultiplication();

    return 0;
}
