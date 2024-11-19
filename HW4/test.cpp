#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <regex>
#include <vector>
#include <climits> // INT_MAX 사용
#include <iomanip> // std::setw 사용

// 전역 변수로 행렬 크기 저장
std::vector<std::pair<int, int>> matrixDimensions;

// 행렬 크기를 추출하여 배열에 저장
void calculateMatrixDimensions(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "파일을 열 수 없습니다: " << filePath << std::endl;
        return;
    }

    // 파일 전체를 하나의 문자열로 읽기
    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();

    // 정규식으로 각 행렬 추출
    std::regex matrixRegex(R"(\[\[([\s\S]*?)\]\])");
    std::smatch match;

    int matrixCount = 1;

    while (std::regex_search(content, match, matrixRegex)) {
        std::string matrixData = match[1].str();

        // 줄바꿈 및 불필요한 공백 제거
        matrixData.erase(remove(matrixData.begin(), matrixData.end(), '\n'), matrixData.end());
        matrixData.erase(remove(matrixData.begin(), matrixData.end(), '\r'), matrixData.end());

        std::stringstream ss(matrixData);
        std::string row;
        int rowCount = 0;
        int colCount = 0;

        // 행렬의 각 행을 `[`와 `]`로 구분
        std::regex rowRegex(R"(\[([^\]]+)\])");
        std::smatch rowMatch;

        while (std::regex_search(matrixData, rowMatch, rowRegex)) {
            std::string rowData = rowMatch[1].str();
            std::stringstream rowStream(rowData);
            std::string element;
            int currentColCount = 0;

            while (rowStream >> element) {
                currentColCount++;
            }

            if (currentColCount > 0) { // 빈 행 제외
                rowCount++;
                if (colCount == 0) {
                    colCount = currentColCount;
                } else if (colCount != currentColCount) {
                    std::cerr << "행렬 A" << matrixCount << "의 열 크기가 일치하지 않습니다." << std::endl;
                    return;
                }
            }

            matrixData = rowMatch.suffix().str(); // 다음 행으로 이동
        }
        rowCount = rowCount + 2;

        // 행렬의 크기를 배열에 저장
        matrixDimensions.emplace_back(rowCount, colCount);

        std::cout << "행렬 A" << matrixCount << ": " << rowCount << "행 " << colCount << "열" << std::endl;
        matrixCount++;

        content = match.suffix().str(); // 다음 행렬로 이동
    }
}



// Chained Matrix Multiplication 알고리즘
void matrixChainMultiplication() {
    int n = matrixDimensions.size(); // 행렬의 개수
    if (n == 0) {
        std::cerr << "행렬 데이터가 없습니다." << std::endl;
        return;
    }

    // 행렬 차원 배열 생성
    std::vector<int> dims;
    dims.push_back(matrixDimensions[0].first); // 첫 번째 행렬의 행 크기
    for (const auto& dim : matrixDimensions) {
        dims.push_back(dim.second); // 각 행렬의 열 크기
    }

    // 비용 테이블 초기화
    std::vector<std::vector<int>> cost(n, std::vector<int>(n, 0));
    std::vector<std::vector<int>> split(n, std::vector<int>(n, 0)); // 최적 분할 지점 저장

    // 알고리즘 수정
    for (int L = 1; L < n; ++L) { // L은 부분 문제 크기
        for (int i = 0; i < n - L; ++i) {
            int j = i + L;
            cost[i][j] = INT_MAX;

            for (int k = i; k < j; ++k) {
                // 곱셈 횟수 계산
                int q = cost[i][k] + cost[k + 1][j] + dims[i] * dims[k + 1] * dims[j + 1];
                if (q < cost[i][j]) {
                    cost[i][j] = q;
                    split[i][j] = k; // 최적 분할 지점 저장
                }
            }
        }
    }

    // 최소 곱셈 횟수 테이블 출력
    std::cout << "\n최소 곱셈 횟수 테이블:" << std::endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i > j) {
                std::cout << std::setw(5) << " "; // i > j인 경우 공백
            } else {
                std::cout << std::setw(5) << (cost[i][j] == INT_MAX ? 0 : cost[i][j]);
            }
        }
        std::cout << std::endl;
    }
}


// Main 함수
int main() {
    std::string filePath = "./matrix_input.txt"; // 파일 경로

    // 행렬 크기 추출
    calculateMatrixDimensions(filePath);

    // 저장된 행렬 크기 출력
    std::cout << "\n저장된 행렬 크기 출력:" << std::endl;
    for (size_t i = 0; i < matrixDimensions.size(); ++i) {
        std::cout << "행렬 A" << i + 1 << ": " << matrixDimensions[i].first
                  << "행 " << matrixDimensions[i].second << "열" << std::endl;
    }

    // Chained Matrix Multiplication 수행
    matrixChainMultiplication();

    return 0;
}
