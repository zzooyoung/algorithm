# File Name : CoinChange.py
# Description : 알고리즘 HW3 과제 중 1. CoinChange algorithm 구현 입니다. 
# 2780원의 거스름돈을 최소 동전 수로 받는 CoinChange 알고리즘 구현
# 결과를 다음과 같이 출력 2780 Won – 500 Won: 5, 100 Won: 2, 50 Won: 1, 10 Won: 3

def coin_change(amount, coins):
    change = {} # dict key : coin, value : amount
    for coin in coins:
        count = amount // coin
        change[coin] = count
        amount -= coin * count
    return change # dictionary
    
amount = 2780
coins = [500, 100, 50, 10]
change = coin_change(amount, coins)

result = f"{amount} Won - "
tmp = []
for coin, count in change.items():
    tmp.append(f"{coin} Won: {count}")
result += ", ".join(tmp)
print(result)
