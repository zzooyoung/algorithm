1. Traveling Salesman Problem (TSP) Algorithm 구현

○ Input: 강의 노트 Chapter 8-1, 11p의 점 A, B, C, D, E, F, G, H

- 시작 점은 A로 고정

- A=(0,3), B=(7,5), C=(6,0), D=(4,3), E=(1,0), F=(5,3), H=(4,1), G=(2,2)

○ Output: 이동 순서, 이동 거리

○ C++를 이용하여 구현

 

2. Vector Cover Problem Algorithm 구현
○ Input :

숙제그림-1.png

○ Output: maximal matching에 의한 Edge의 집합 (단, Edge는 A-B, G-H의 형태로 표시)

○ Java를 이용하여 구현 (AI학과 학생은 Java로 구현하면 100점 만점, C++로 구현하면 70점 만점)

 

3. Bin Packing Problem Algorithm 구현
○ Input : 강의 노트 Chapter 8-1, 32p에 정의된 C=10, 물건의 크기 = [7, 5, 6, 4, 2, 3, 7, 5]

○ Output1: First Fit에 의한 결과

○ Output2: Next Fit에 의한 결과

○ Output3: Best Fit에 의한 결과

○ Output4: Worst Fit에 의한 결과

○ C를 이용하여 구현

※ Output은 다음과 같은 형태로 출력

예) Output1 (First Fit): bin1 = [7, 2], bin2 = [5,4], bin3 = [6, 3], bin4 = [7], bin5 = [5]

 

4. Job Scheduling Problem Algorithm 구현
○ Input : 강의 노트 Chapter 8-2, 5p에 나와 있는 값

- m = 4, operation_time = [5, 2, 4, 3, 4, 7, 9, 2, 4, 1]

○ Output:

숙제그림2-1.png

○ Java를 이용하여 구현 (AI학부 학생은 Java로 구현하면 100점 만점, C++로 구현하면 70점 만점)

 

5. Clustering Problem Algorithm 구현
○ Input :clustering_input.txt문서 미리 보기 (100개의 (x, y) 좌표)

- 같은 좌표가 있으면 하나만 사용

- 초기 센터는 1번째 좌표로 정함

○ Output: 8개의 cluster에 해당하는 점의 좌표와 각 센터 좌표

○ C++를 이용하여 구현