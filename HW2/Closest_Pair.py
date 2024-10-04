#############################################################
# File Name : Closest_Pair.py
# Description : 알고리즘 HW2 과제 중 4. Closest Pair Algorithm 구현입니다.
# input_closest_pair.txt 파일을 입력 데이터로 설정
# Closest Pair algorithm을 통해 가장 짧은 거리를 가진 좌표의 쌍을 찾고 그 최단 거리를 출력
# O(nlogn)의 복잡도로 구현
#############################################################

import math

# 두 점 사이의 유클리드 거리 계산
def calculate_distance(point1, point2):
    return math.sqrt((point1[0] - point2[0])**2 + (point1[1] - point2[1])**2)

# 점이 3개 이하일 때, 브루트포스 방식으로 가장 가까운 두 점을 찾는 함수
def find_closest_pair_bruteforce(points):
    min_distance = float('inf')
    closest_pair = (points[0], points[1])
    num_points = len(points)
    
    for i in range(num_points):
        for j in range(i + 1, num_points):
            distance = calculate_distance(points[i], points[j])
            if distance < min_distance:
                min_distance = distance
                closest_pair = (points[i], points[j])
    
    return min_distance, closest_pair

# 중간 영역에서 최단 거리를 찾는 함수
def find_closest_split_pair(Px, Py, delta, best_pair):
    midpoint_x = Px[len(Px) // 2][0]  # 중앙점 기준으로 분할
    Sy = [p for p in Py if midpoint_x - delta <= p[0] <= midpoint_x + delta]  # 중간 영역 필터링

    best_distance = delta
    best_pair_split = best_pair
    len_Sy = len(Sy)
    
    for i in range(len_Sy):
        for j in range(i + 1, min(i + 7, len_Sy)):  # 최대 7개의 점과 비교
            p, q = Sy[i], Sy[j]
            dist_pq = calculate_distance(p, q)
            if dist_pq < best_distance:
                best_distance = dist_pq
                best_pair_split = (p, q)

    return best_distance, best_pair_split

# 분할 정복 방식으로 가장 가까운 두 점을 찾는 재귀 함수
def closest_pair_recursive(Px, Py):
    num_points = len(Px)
    
    if num_points <= 3:
        return find_closest_pair_bruteforce(Px)

    # 좌우로 분할
    mid = num_points // 2
    Lx, Rx = Px[:mid], Px[mid:]
    midpoint_x = Px[mid][0]
    Ly = [p for p in Py if p[0] <= midpoint_x]
    Ry = [p for p in Py if p[0] > midpoint_x]

    # 좌우 각각에서 최근접 쌍을 찾음
    d_left, pair_left = closest_pair_recursive(Lx, Ly)
    d_right, pair_right = closest_pair_recursive(Rx, Ry)

    # 더 작은 거리를 선택
    if d_left < d_right:
        best_distance = d_left
        best_pair = pair_left
    else:
        best_distance = d_right
        best_pair = pair_right

    # 중간 영역에서의 최근접 쌍을 찾음
    d_split, split_pair = find_closest_split_pair(Px, Py, best_distance, best_pair)

    if d_split < best_distance:
        return d_split, split_pair
    else:
        return best_distance, best_pair

# 전체 점 집합에서 최근접 쌍을 찾는 함수 (메인 함수)
def find_closest_pair(points):
    Px = sorted(points, key=lambda x: x[0])  # x축 기준으로 정렬
    Py = sorted(points, key=lambda x: x[1])  # y축 기준으로 정렬
    return closest_pair_recursive(Px, Py)

# 입력 파일에서 좌표 데이터를 읽어오는 함수
def read_input(file_name):
    points = []
    with open(file_name, 'r') as file:
        for line in file:
            x, y = map(int, line.split())
            points.append((x, y))
    return points

if __name__ == "__main__":
    # 좌표 데이터 파일 읽기
    file_name = "input_closest_pair.txt"
    points = read_input(file_name)

    # 가장 가까운 두 점 찾기
    min_distance, closest_pair = find_closest_pair(points)

    # 결과 출력
    print(f"Closest points: {closest_pair}")
    print(f"Distance: {min_distance:.6f}")
