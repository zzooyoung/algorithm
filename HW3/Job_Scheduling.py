# File Name : Job_Scheduing.py
# Description : 알고리즘 HW3 과제 중 7. Job Scheduling algorithm 구현 입니다. 
# input: Chapter 4-2, 27p에 있는 t1-t7


# job list (start, end)
jobs = [
    (7, 8), (3, 7), (1, 5), (5, 9), (0, 2), (6, 8), (1, 6)
]

jobs_with_id = []
for i in range(len(jobs)):
    job_id = i + 1  # Time number start 1
    start, end = jobs[i]
    jobs_with_id.append((job_id, start, end))

# sorting by start
jobs = sorted(jobs_with_id, key=lambda x: x[1])

# list for machine
machines = []

# Assign job to each machine
for job in jobs:
    job_id, start, end = job
    assigned = False
    # check to assign available
    for machine in machines:
        # assign job
        if machine[-1][2] <= start:
            machine.append(job)
            assigned = True
            break
    # add a new machine
    if not assigned:
        machines.append([job])

# make timetable
time_table = []
for _ in range(len(machines)):
    time_table.append([" "] * 10)

# Assign a job name to each machine's timetable
for i in range(len(machines)):
    machine = machines[i]
    for job in machine:
        job_id, start, end = job
        for t in range(start, end):
            time_table[i][t] = f"t{job_id}"

# print timetable
print("time     ", end="")
for t in range(10):
    print(f"{t:>3}", end="")
print() # Line

for i in range(len(time_table) - 1, -1, -1):
    print(f"Machine {i + 1}", end=" ")
    for cell in time_table[i]:
        print(f"{cell:>3}", end="")
    print() # Line
