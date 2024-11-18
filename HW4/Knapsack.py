# File Name : Knapsack.py
# Description : 알고리즘 HW4 과제 중 4. 0-1 Knapsack algorithm 구현 입니다. 
# input: Chapter 5-2, 24p에 나온 C 및 각 물건 무게, 가치
# output: Chapter 5-2, 36p에 나온 테이블

def knapsack(values, weights, capacity):
    n = len(values)
    # Table Initialize (n+1 x capacity+1)
    table = [[0] * (capacity + 1) for _ in range(n + 1)]

    # start
    for i in range(1, n + 1): # len(values)
        for w in range(1, capacity + 1):  # temp capacity
            if weights[i - 1] > w:  # weight > capacity
                table[i][w] = table[i - 1][w]
            else:  # Max Whether to put things in or not
                table[i][w] = max(table[i - 1][w], table[i - 1][w - weights[i - 1]] + values[i - 1])

    return table


def print_table(table, values, weights, capacity):
    print("           ", end="")
    for w in range(capacity + 1):
        print(f"{w:3}", end="")
    print()

    for i in range(len(table)):
        if i == 0:
            print("", end="")
        else:
            print(f"{i:3}({values[i - 1]:2} ,{weights[i - 1]:2})", end="")
            for w in range(len(table[i])):
                print(f"{table[i][w]:3}", end="")
            print()


# Input
values = [10, 40, 30, 50]  # values 
weights = [5, 4, 6, 3]  # weights 
capacity = 10  # Knapsack Capacity 10 C

# Run Knapsack
table_table = knapsack(values, weights, capacity)

# Print Result Table
print("Knapsack table Table:")
print_table(table_table, values, weights, capacity)
