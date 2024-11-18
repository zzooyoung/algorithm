/*
    File Name : CoinChange.cpp
    Description : 알고리즘 HW4 과제 중 5. Coin Change algorithm 구현 입니다. 

    input: Chapter 5-2, 42p에 나온, d1, d2, d3, d4, n 값
    output: Chapter 5-2, 48p에 나오는 테이블
*/

// Heading Commnets
#include <iostream>
#include <vector>
#include <iomanip> // For formatted output
#include <limits.h> // For INT_MAX

using namespace std;

void coinChange(int n, vector<int> &coins) {
    int k = coins.size();
    vector<int> table(n + 1, INT_MAX); // table initialize
    table[0] = 0; // for zero

    // calculate
    for (int i = 0; i < k; i++) {
        for (int j = coins[i]; j <= n; j++) {
            if (table[j - coins[i]] != INT_MAX && table[j - coins[i]] + 1 < table[j]) {
                table[j] = table[j - coins[i]] + 1;
            }
        }
    }

    // print result table
    cout << "DP Table:\n";
    cout << "j: ";
    for (int j = 0; j <= n; j++) {
        cout << setw(3) << j;
    }
    cout << endl;

    cout << "C: ";
    for (int j = 0; j <= n; j++) {
        if (table[j] == INT_MAX) {
            cout << setw(3) << "∞";
        } else {
            cout << setw(3) << table[j];
        }
    }
    cout << endl;
}

int main() {
    int n = 20; // n 
    vector<int> coins = {16, 10, 5, 1}; // coin {d1, d2, d3, d4}

    coinChange(n, coins);

    return 0;
}
