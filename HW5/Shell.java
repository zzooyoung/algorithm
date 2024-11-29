// File Name : Shell.java
// Description : 알고리즘 HW5 과제 중 4.Shell algorithm 구현 입니다.
// - Input : input.txt
// - Output : shell_output.txt

import java.io.*;
import java.util.*;

public class Shell {

    // Shell Sort Method
    public static void shellSort(int[] arr) {
        // gap h
        int[] gaps = {100, 50, 10, 5, 1};

        // each gap Big --> small
        for (int gap : gaps) {
            for (int i = gap; i < arr.length; i++) {
                int temp = arr[i];
                int j = i;
                // gap 간격을 기준으로 삽입 정렬
                while (j >= gap && arr[j - gap] > temp) {
                    arr[j] = arr[j - gap];
                    j -= gap;
                }
                arr[j] = temp;
            }
        }
    }

    // Read File to int From File
    public static int[] readNumbersFromFile(String fileName) {
        List<Integer> numbersList = new ArrayList<>();
        try (BufferedReader br = new BufferedReader(new FileReader(fileName))) {
            String line;
            while ((line = br.readLine()) != null) {
                String[] tokens = line.split("\\s+");
                for (String token : tokens) {
                    try {
                        numbersList.add(Integer.parseInt(token));
                    } catch (NumberFormatException e) {
                        System.err.println("Number Format Error: " + token);
                    }
                }
            }
        } catch (IOException e) {
            System.err.println("File I/O Error : " + e.getMessage());
            return null;
        }
        

        int[] arr = new int[numbersList.size()];
        for (int i = 0; i < numbersList.size(); i++) {
            arr[i] = numbersList.get(i);
        }
        return arr;
    }

    // Write Number to file
    public static void writeNumbersToFile(String fileName, int[] arr) {
        try (BufferedWriter bw = new BufferedWriter(new FileWriter(fileName))) {
            for (int i = 0; i < arr.length; i++) {
                bw.write(arr[i] + "\n");
            }
            bw.newLine();
        } catch (IOException e) {
            System.err.println("File Write Error: " + e.getMessage());
        }
    }

    public static void main(String[] args) {
        // File read from input.txt
        int[] arr = readNumbersFromFile("input.txt");
        if (arr == null) {
            return;  // Error Catch
        }

        // Shell Sort Execution
        shellSort(arr);

        // 결과를 shell_output.txt로 저장
        writeNumbersToFile("shell_output.txt", arr);

        System.out.println("Save shell_output.txt");
    }
}
