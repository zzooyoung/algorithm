# File Name : Job_Scheduling.py
# Description : 알고리즘 HW3 과제 중 7. Job Scheduling algorithm 구현 입니다. 
# input: Chapter 4-2, 27p에 있는 t1-t7


# Job List t1~t7
jobs = [
    (7, 8), (3, 7), (1, 5), (5, 9), (0, 2), (6, 8), (1, 6)
]

# sorting by starting time, jobs = (job_id, (start, end))
jobs = sorted(enumerate(jobs, start=1), key=lambda x: x[1][0])

# list for machine's job Schedule
machines = []

# 작업을 각 기계에 배정
for job_id, (start, end) in jobs:
    assigned = False
    # 각 기계를 순회하면서 현재 작업을 배정할 수 있는지 확인
    for machine in machines:
        # 기계의 마지막 작업 종료 시간보다 현재 작업 시작 시간이 늦으면 배정
        if machine[-1][1] <= start:
            machine.append((job_id, start, end))
            assigned = True
            break
    # 현재 작업을 배정할 수 있는 기계가 없다면, 새 기계에 작업을 추가
    if not assigned:
        machines.append([(job_id, start, end)])

# 시간표 생성
time_table = [[" " for _ in range(10)] for _ in range(len(machines))]

# 각 기계의 시간표에 작업 이름을 할당
for i, machine in enumerate(machines):
    for job_id, start, end in machine:
        for t in range(start, end):
            time_table[i][t] = f"t{job_id}"

# 시간표 출력
print("time ", end="")
for t in range(10):
    print(f"{t:>3}", end="")
print()

for i, row in enumerate(time_table):
    print(f"Machine {len(machines) - i}", end=" ")
    for cell in row:
        print(f"{cell:>3}", end="")
    print()
