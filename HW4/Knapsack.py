# File Name : Knapsack.py
# Description : 알고리즘 HW4 과제 중 4. 0-1 Knapsack algorithm 구현 입니다. 
# input: Chapter 5-2, 24p에 나온 C 및 각 물건 무게, 가치
# output: Chapter 5-2, 36p에 나온 테이블

def knapsack(values, weights, capacity):
    n = len(values)
    # DP 테이블 초기화 (n+1 x capacity+1)
    dp = [[0] * (capacity + 1) for _ in range(n + 1)]

    # DP 테이블 채우기
    for i in range(1, n + 1):  # 물건
        for w in range(1, capacity + 1):  # 배낭 용량
            if weights[i - 1] > w:  # 현재 물건의 무게가 배낭 용량을 초과하면
                dp[i][w] = dp[i - 1][w]
            else:  # 물건을 넣거나 넣지 않는 경우 중 최댓값 선택
                dp[i][w] = max(dp[i - 1][w], dp[i - 1][w - weights[i - 1]] + values[i - 1])

    return dp


def print_table(dp, values, weights, capacity):
    print("    ", end="")
    for w in range(capacity + 1):
        print(f"{w:3}", end="")
    print()

    for i in range(len(dp)):
        if i == 0:
            print("  ", end="")
        else:
            print(f"{i:3}({values[i - 1]:2}/{weights[i - 1]:2})", end="")
        for w in range(len(dp[i])):
            print(f"{dp[i][w]:3}", end="")
        print()


# 입력 데이터
values = [10, 40, 30, 50]  # 물건의 가치
weights = [5, 4, 6, 3]  # 물건의 무게
capacity = 10  # 배낭 용량

# DP 테이블 계산
dp_table = knapsack(values, weights, capacity)

# DP 테이블 출력
print("Knapsack DP Table:")
print_table(dp_table, values, weights, capacity)
