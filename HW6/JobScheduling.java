// File Name : JobScheduling.java
// Description : 알고리즘 HW6 과제 중 4. Job Scheduling Algorithm 구현 입니다.
// - Input : 강의 노트 Chapter 8-2, 5p에 나와 있는 값 - m = 4, operation_time = [5, 2, 4, 3, 4, 7, 9, 2, 4, 1]
// - Output : Result Table
import java.util.*;

public class JobScheduling {

    static class Job {
        int jobId;    // Job(task) ID (t1, t2, ...)
        int jobTime;  // Time for Job

        public Job(int jobId, int jobTime) {
            this.jobId = jobId;
            this.jobTime = jobTime;
        }
    }

    // Scheduling Func
    public static void scheduleJobs(int m, int[] operationTime) {
        int n = operationTime.length;


        Job[] jobs = new Job[n];
        for (int i = 0; i < n; i++) {
            jobs[i] = new Job(i + 1, operationTime[i]);
        }

        // End time
        int[] machineEndTime = new int[m];
        Arrays.fill(machineEndTime, 0);

        // Scheduling table
        int[][] schedule = new int[m][13];
        for (int i = 0; i < m; i++) {
            Arrays.fill(schedule[i], 0);
        }

        // Find Early end
        for (Job job : jobs) {
            int minEndTimeMachine = 0;
            for (int i = 1; i < m; i++) {
                if (machineEndTime[i] < machineEndTime[minEndTimeMachine]) {
                    minEndTimeMachine = i;
                }
            }

            int startTime = machineEndTime[minEndTimeMachine];
            int endTime = startTime + job.jobTime;

            for (int t = startTime; t < endTime && t < 13; t++) {
                schedule[minEndTimeMachine][t] = job.jobId; 
            }

            // Update
            machineEndTime[minEndTimeMachine] = endTime;
        }

        // Print Result
        System.out.print("   m/t");
        for (int t = 0; t <= 12; t++) {
            System.out.printf("%4d", t);
        }
        System.out.println();


        for (int i = 0; i < m; i++) {
            System.out.printf("     %-2d", (i + 1));  
            for (int t = 0; t <= 12; t++) {
                if (schedule[i][t] != 0) {
                    System.out.printf(" t%-2d", schedule[i][t]);  
                } else {
                    System.out.printf("   "); 
                }
            }
            System.out.println();
        }
    }

    public static void main(String[] args) {
        // Input
        int[] operationTime = {5, 2, 4, 3, 4, 7, 9, 2, 4, 1};
        
        int m = 4;

        // Func Call 
        scheduleJobs(m, operationTime);
    }
}
