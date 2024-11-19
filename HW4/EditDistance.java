// File Name : EditDistance.java
// Description : 알고리즘 HW4 과제 중 3.Edit Distance algorithm 구현 입니다.
// - Input : 수업 예제인 ‘strong’과 ‘stone’
// - Output : Chapter 5-2, 17p의 테이블

import java.util.Arrays;

public class EditDistance {

    public static void main(String[] args) {
        String s = "strong";
        String t = "stone";

        int[][] table = calculateEditDistance(s, t);

        // Print the table
        printTable(table, s, t);

        // Print the edit distance
        System.out.println("\nMinimum Edit Distance: " + table[s.length()][t.length()]);
    }

    public static int[][] calculateEditDistance(String s, String t) {
        int m = s.length();
        int n = t.length();

        int[][] table = new int[m + 1][n + 1];

        // Initialize the table
        for (int i = 0; i <= m; i++) {
            table[i][0] = i; // Cost of deleting characters from S
        }
        for (int j = 0; j <= n; j++) {
            table[0][j] = j; // Cost of inserting characters into S
        }

        // Fill the table
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                int cost = (s.charAt(i - 1) == t.charAt(j - 1)) ? 0 : 1;

                table[i][j] = Math.min(
                        table[i - 1][j] + 1, // Deletion
                        Math.min(
                                table[i][j - 1] + 1, // Insertion
                                table[i - 1][j - 1] + cost // Substitution
                        )
                );
            }
        }

        return table;
    }

    public static void printTable(int[][] table, String s, String t) {
        int m = s.length();
        int n = t.length();

        // Print column headers (characters of T)
        System.out.print("  ");
        System.out.print("  ");
        for (int j = 0; j < n; j++) {
            System.out.print(t.charAt(j) + " ");
        }
        System.out.println();

        // Print the table with row headers (characters of S)
        for (int i = 0; i <= m; i++) {
            if (i == 0) {
                System.out.print("  ");
            } else {
                System.out.print(s.charAt(i - 1) + " ");
            }

            for (int j = 0; j <= n; j++) {
                System.out.print(table[i][j] + " ");
            }
            System.out.println();
        }
    }
}
