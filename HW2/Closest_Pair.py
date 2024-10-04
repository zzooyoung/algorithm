#############################################################
# File Name : Closest_Pair.py
# Description : 알고리즘 HW2 과제 중 4. Closest Pair Algorithm 구현입니다.
# input_closest_pair_under3ir.txt 파일을 입력 데이터로 설정
# Closest Pair algorithm을 통해 가장 짧은 거리를 가진 좌표의 쌍을 찾고 그 최단 거리를 출력
# O(nlogn)의 복잡도로 구현
############################################################

import math

# 두 점 사이의 거리 계산 함수
def dist(p1, p2):
    return math.sqrt((p1[0] - p2[0])**2 + (p1[1] - p2[1])**2)

# 가장 가까운 쌍을 찾는 보조 함수 (점이 3개 이하일 때)
def brute_force(S):
    min_dist = float('inf')
    n = len(S)
    pair = None
    for i in range(n):
        for j in range(i + 1, n):
            d = dist(S[i], S[j])
            if d < min_dist:
                min_dist = d
                pair = (S[i], S[j])
    return pair, min_dist

# 중앙 영역에서 가장 가까운 쌍을 찾는 함수
def closest_split_pair(S, d, best_pair):
    mid_x = S[len(S) // 2][0]
    in_strip = [p for p in S if abs(p[0] - mid_x) < d]
    in_strip.sort(key=lambda p: p[1])
    min_dist = d
    n = len(in_strip)

    for i in range(n):
        for j in range(i + 1, n):  
            d = dist(in_strip[i], in_strip[j])
            if d < min_dist:
                min_dist = d
                best_pair = (in_strip[i], in_strip[j])
    return best_pair, min_dist

# 분할정복으로 가장 가까운 쌍을 찾는 메인 함수
def closest_pair(S):
    n = len(S)
    
    if n <= 3:
        return brute_force(S)
    
    mid = n // 2
    S_L = S[:mid]
    S_R = S[mid:]

    pair_L, dist_L = closest_pair(S_L)
    pair_R, dist_R = closest_pair(S_R)

    d = min(dist_L, dist_R)
    best_pair = pair_L if dist_L <= dist_R else pair_R

    pair_C, dist_C = closest_split_pair(S, d, best_pair)
    
    return min([pair_L, pair_R, pair_C], key=lambda x: dist(x[0], x[1]))

# 파일로부터 좌표 읽어오기
def read_points_from_file(file_path):
    points = []
    with open(file_path, 'r') as file:
        for line in file:
            x, y = map(float, line.strip().split())
            points.append((x, y))
    return points

# 입력 파일 설정 및 좌표 읽어오기
file_path = './input_closest_pair.txt'
points = read_points_from_file(file_path)

# x-좌표 기준으로 정렬
points.sort(key=lambda p: p[0])

# 가장 가까운 쌍과 그 거리 출력
closest_points, min_distance = closest_pair(points)
print("가장 가까운 두 점:", closest_points)
print("최단 거리:", min_distance)
