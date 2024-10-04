
    // File Name : QuickSort.java
    // Description : 알고리즘 HW2 과제 중 2.Quick sort 구현 입니다.
    // input_sort.txt 파일을 입력 데이터로 설정
    // Quick sort를 구현하여 올림차순으로 정렬 후 output_quick_sort.xlsx (or output_quick_sort_txt) 파일 출력

import java.io.*;
import java.util.ArrayList;
import java.util.List;
    
public class QuickSort {
    
    // Quick Sort 알고리즘 구현
    public static void quickSort(int[] arr, int left, int right) { 
        if (left < right) {
            int p = partition(arr, left, right);

            quickSort(arr, left, p - 1);
            quickSort(arr, p + 1, right);
        } 
    }
    
    // Partition 함수: 피벗을 기준으로 배열을 분할
    public static int partition(int[] arr, int left, int right) {
        int pivot = arr[right];  // 가장 오른쪽 요소를 피벗으로 설정
        int i = left - 1;

        for (int j = left; j < right; j++) {
            if (arr[j] < pivot) {
                i++;
                // arr[i]와 arr[j] 교환
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    
        // arr[i+1]과 피벗을 교환
        int temp = arr[i + 1];
        arr[i + 1] = arr[right];
        arr[right] = temp;

        return i + 1;
    }
    
    public static void main(String[] args) {
        long start = System.nanoTime();
    
        List<Integer> list = new ArrayList<>();

        // 상대 경로를 위한 Working Dir Path
        String path = System.getProperty("user.dir") + File.separator + "HW2" + File.separator;

        System.out.println("Working directory: " + path);
    
        // 입력 파일에서 데이터 읽기
        try(BufferedReader br = new BufferedReader(new FileReader(path + "input_sort.txt"))) {
            String line;
            while ((line = br.readLine()) != null) {
                list.add(Integer.parseInt(line));
            }
        } catch (IOException e) {
            System.out.println("Failed to open the file.");
            e.printStackTrace();
            return;
        }
        
        // List를 배열로 변환
        int[] intInput = list.stream().mapToInt(i -> i).toArray();
    
        // Quick Sort 실행
        quickSort(intInput, 0, intInput.length - 1);
    
        // 정렬된 데이터를 출력 파일로 쓰기
        try(BufferedWriter bw = new BufferedWriter(new FileWriter(path + "output_quick_sort.txt"))) {
            for (int num : intInput) {
                bw.write(num + "\n");
            }
        } catch (IOException e) {
            System.out.println("Failed to write the file.");
            e.printStackTrace();
            return;
        }
    
        // 실행 시간 출력
        long end = System.nanoTime();
        double duration = (end - start) / 1_000_000_000.0; // 초 단위로 변환
        System.out.printf("Execution time: %.6f seconds\n", duration);
    }
}
    