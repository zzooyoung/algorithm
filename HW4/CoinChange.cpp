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
    vector<int> dp(n + 1, INT_MAX); // DP 배열 초기화
    dp[0] = 0; // 0원을 만들기 위한 동전 수는 0

    // DP 테이블 계산
    for (int i = 0; i < k; i++) {
        for (int j = coins[i]; j <= n; j++) {
            if (dp[j - coins[i]] != INT_MAX && dp[j - coins[i]] + 1 < dp[j]) {
                dp[j] = dp[j - coins[i]] + 1;
            }
        }
    }

    // DP 테이블 출력
    cout << "DP Table:\n";
    cout << "j: ";
    for (int j = 0; j <= n; j++) {
        cout << setw(3) << j;
    }
    cout << endl;

    cout << "C: ";
    for (int j = 0; j <= n; j++) {
        if (dp[j] == INT_MAX) {
            cout << setw(3) << "∞";
        } else {
            cout << setw(3) << dp[j];
        }
    }
    cout << endl;

    // 최소 동전 수 출력
    cout << "\nMinimum coins required to make " << n << " is: ";
    if (dp[n] == INT_MAX) {
        cout << "Not possible" << endl;
    } else {
        cout << dp[n] << endl;
    }
}

int main() {
    int n = 20; // 거스름돈 금액
    vector<int> coins = {16, 10, 5, 1}; // 동전 단위

    coinChange(n, coins);

    return 0;
}
