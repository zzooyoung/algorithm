    # File Name : Closest_Pair.py
    # Description : 알고리즘 HW2 과제 중 4. Closest Pair 구현 입니다. 
    # input_closest_pair.txt 파일을 입력 데이터로 설정
    # Closest Pair algorithm을 통해 가장 짧은 거리를 좌표의 쌍을 찾고 그 최단 거리를 출력

import math
import time


# 두 점 사이의 거리 계산 함수
def dist(p1, p2):
    return math.sqrt((p1[0] - p2[0])**2 + (p1[1] - p2[1])**2)

# 가장 가까운 쌍을 찾는 보조 함수 (점이 3개 이하일 때)
def find_under_3(points):
    min_distance = float('inf')
    num_points = len(points)
    closest_pair = None
    for i in range(num_points):
        for j in range(i + 1, num_points):
            distance = dist(points[i], points[j])
            if distance < min_distance:
                min_distance = distance
                closest_pair = (points[i], points[j])
    return closest_pair, min_distance

# 중앙 영역에서 가장 가까운 쌍을 찾는 함수
def closest_split_pair(points, min_dist, best_pair):
    mid_x = points[len(points) // 2][0]
    points_in_strip = []
    for point in points:
        if abs(point[0] - mid_x) < min_dist:
            points_in_strip.append(point)
    points_in_strip.sort(key=lambda p: p[1])
    
    n = len(points_in_strip)

    for i in range(n):
        for j in range(i + 1, n):
            distance = dist(points_in_strip[i], points_in_strip[j])
            if distance < min_dist:
                min_dist = distance
                best_pair = (points_in_strip[i], points_in_strip[j])
    return best_pair, min_dist


# 분할정복으로 가장 가까운 쌍을 찾는 메인 함수
def closest_pair(points):
    num_points = len(points)
    
    if num_points <= 3:
        return find_under_3(points)
    
    mid = num_points // 2
    left_half_points = points[:mid]
    right_half_points = points[mid:]

    closest_pair_left, min_distance_left = closest_pair(left_half_points)
    closest_pair_right, min_distance_right = closest_pair(right_half_points)

    min_distance = min(min_distance_left, min_distance_right)
    closest_pair_overall = closest_pair_left if min_distance_left <= min_distance_right else closest_pair_right

    closest_pair_split, min_distance_split = closest_split_pair(points, min_distance, closest_pair_overall)
    
    if min_distance_split < min_distance:
        return closest_pair_split, min_distance_split
    else:
        return closest_pair_overall, min_distance

# 중복된 좌표를 제거하는 함수
def RM_DUP(points):
    return list(set(points))  # 중복된 좌표를 제거하기 위해 set으로 변환 후 다시 리스트로 변환

# 실행 시간 측정을 위한 시작 함수
start_time = time.time()

# 입력 파일 설정 및 좌표 읽어오기
file_path = './input_closest_pair.txt'
points = []
with open(file_path, 'r') as file:
    for line in file:
        x, y = map(float, line.strip().split())
        points.append((x, y))
        

# 중복 좌표 제거
points = RM_DUP(points)

# X 좌표 기준으로 정렬
points.sort(key=lambda p: p[0])

# 가장 가까운 쌍과 그 거리 출력
closest_points, min_distance = closest_pair(points)
print("가장 가까운 두 점:", closest_points)
print("최단 거리:", min_distance)

end_time = time.time()

exec_time = end_time - start_time

print("Execution time: %.8f seconds." % exec_time) 