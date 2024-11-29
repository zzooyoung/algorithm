// File Name : Bubble.java
// Description : 알고리즘 HW5 과제 중 1.Bubble Sort Algorithm 구현 입니다.
// - Input : input.txt
// - Output : bubble_output.txt

import java.io.*;
import java.util.*;

public class Bubble {

    // Main
    public static void main(String[] args) {
        // File Path Using Working Directory 
        String path = System.getProperty("user.dir") + File.separator + "input.txt";
        String outputFilePath = System.getProperty("user.dir") + File.separator + "bubble_output.txt";
        
        // Read Data and Write at List
        List<Integer> numbers = readNumbersFromFile(path);
        
        // Execute Bubble Sort
        bubbleSort(numbers);
        
        // Write Result to File
        writeNumbersToFile(numbers, outputFilePath);
    }
    
    // Read Numbers From file (input.txt)
    public static List<Integer> readNumbersFromFile(String filePath) {
        List<Integer> numbers = new ArrayList<>();
        
        try (BufferedReader br = new BufferedReader(new FileReader(filePath))) {
            String line;
            while ((line = br.readLine()) != null) {
                // number into numbers
                String[] tokens = line.split("\\s+");
                
                for (String token : tokens) {
                    try {
                        numbers.add(Integer.parseInt(token));
                    } catch (NumberFormatException e) {
                        System.err.println("Number Format Error " + token);
                    }
                }
            }
        } catch (IOException e) {
            System.err.println("File I/O Error : " + e.getMessage());
        }
        
        return numbers;
    }
    
    // Bubble Sort
    public static void bubbleSort(List<Integer> list) {
        int n = list.size();
        for (int pass = 0; pass < n - 1; pass++) {
            for (int i = 0; i < n - 1 - pass; i++) {
                if (list.get(i) > list.get(i + 1)) {
                    // Swap
                    Collections.swap(list, i, i + 1);
                }
            }
        }
    }
    
    // Write Results to bubble_output.txt 
    public static void writeNumbersToFile(List<Integer> numbers, String filePath) {
        try (BufferedWriter bw = new BufferedWriter(new FileWriter(filePath))) {
            for (Integer num : numbers) {
                bw.write(num + "\n");
            }
            bw.newLine(); 
        } catch (IOException e) {
            System.err.println("File Write Error: " + e.getMessage());
        }
    }
}
