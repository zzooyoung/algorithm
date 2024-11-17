/*
    File Name : CMM.cpp
    Description : 알고리즘 HW4 과제 중 2. Chained Matrix Multiplications(CMM) algorithm 구현 입니다. 

    Input : matrix_input.txt 
    Output : Chapter 5-1, 48p와 같은 테이블 및 최소 곱셈 횟수 값
*/

// Heading Commnets
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <climits>

using namespace std;

// Function to parse input file and extract matrix dimensions
vector<int> parseInputFile(const string &filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file." << endl;
        exit(1);
    }

    vector<int> dimensions;
    string line;

    while (getline(file, line)) {
        if (line.find('=') != string::npos) { // Detect matrix declaration
            vector<vector<int>> matrix;
            while (getline(file, line) && !line.empty() && line[0] == '[') {
                stringstream ss(line.substr(1, line.size() - 2)); // Strip square brackets
                int val;
                vector<int> row;
                while (ss >> val) {
                    row.push_back(val);
                }
                matrix.push_back(row);
            }

            // Store matrix dimensions
            int rows = matrix.size();
            int cols = matrix[0].size();
            if (dimensions.empty()) {
                dimensions.push_back(rows); // First matrix's rows
            }
            dimensions.push_back(cols); // Current matrix's columns
        }
    }

    file.close();

    if (dimensions.size() < 2) {
        cerr << "Error: No valid matrix dimensions found in the input file." << endl;
        exit(1);
    }

    return dimensions;
}

// Chained Matrix Multiplication Algorithm
int matrixChainOrder(const vector<int> &dims, vector<vector<int>> &dp) {
    int n = dims.size() - 1;
    dp.resize(n + 1, vector<int>(n + 1, 0));

    for (int i = 1; i <= n; i++) {
        dp[i][i] = 0; // No cost to multiply one matrix
    }

    for (int L = 1; L < n; L++) { // L is chain length
        for (int i = 1; i <= n - L; i++) {
            int j = i + L;
            dp[i][j] = INT_MAX;

            for (int k = i; k < j; k++) {
                int cost = dp[i][k] + dp[k + 1][j] + dims[i - 1] * dims[k] * dims[j];
                if (cost < dp[i][j]) {
                    dp[i][j] = cost;
                }
            }
        }
    }

    return dp[1][n];
}

// Print DP Table as a formatted table
void printTable(const vector<vector<int>> &dp, int n) {
    cout << "C ";
    for (int j = 1; j <= n; j++) {
        cout << setw(8) << j;
    }
    cout << endl;

    for (int i = 1; i <= n; i++) {
        cout << i << " ";
        for (int j = 1; j <= n; j++) {
            if (i > j) {
                cout << setw(8) << " ";
            } else {
                cout << setw(8) << dp[i][j];
            }
        }
        cout << endl;
    }
}

int main() {
    string filename = "matrix_input.txt";

    // Parse input file to get dimensions
    vector<int> dims = parseInputFile(filename);

    if (dims.size() < 2) {
        cerr << "Error: Invalid matrix dimensions in input file." << endl;
        return 1;
    }

    int n = dims.size() - 1; // Number of matrices
    vector<vector<int>> dp;

    // Solve Chained Matrix Multiplication
    int minCost = matrixChainOrder(dims, dp);

    // Output the DP table as a formatted table
    cout << "Optimal Parenthesization Cost Table (C):" << endl;
    printTable(dp, n);

    // Output the minimum cost
    cout << "\nMinimum number of scalar multiplications: " << minCost << endl;

    return 0;
}
