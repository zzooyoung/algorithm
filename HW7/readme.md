1. Genetic Algorithm 구현

○ Input: 강의자료 Chapter 8-1, 11p의 점 A, B, C, D, E, F, G, H

- 시작 점은 A로 고정

- A=(0,3), B=(7,5), C=(6,0), D=(4,3), E=(1,0), F=(5,3), H=(4,1), G=(2,2)

○ Output: 이동 순서, 이동 거리

○ C를 이용하여 구현

 

※ 알고리즘 파라미터

- 각 loop마다 8개의 후보해를 선정

- 사이클 교차 연산 사용

- crossover ratio = 1.0

- mutation ratio = 0.01

 

2. Backtracking Algorithm 구현
○ Input: 강의자료 Chapter 9-1, 38p의 그래프 (시작점 A 가정)

○ Output: [A, B, E, C, D, A], 거리 = 16

○ C++를 이용하여 구현

 

3. Branch and Bound Algorithm
○ Input: 강의자료 Chapter 9-2, 10p의 그래프 (시작점 A 가정)

○ Output: [A, B, E, C, D, A], 거리 = 16

○ Java를 이용하여 구현 (AI학부 학생은 Java로 구현하면 100점 만점, C++로 구현하면 70점 만점)