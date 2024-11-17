// File Name : EditDistance.java
// Description : 알고리즘 HW4 과제 중 3.Edit Distance algorithm 구현 입니다.
// - Input : 수업 예제인 ‘strong’과 ‘stone’
// - Output : Chapter 5-2, 17p의 테이블

import java.util.Arrays;

public class EditDistance {

    public static void main(String[] args) {
        String s = "strong";
        String t = "stone";

        int[][] dp = calculateEditDistance(s, t);

        // Print the DP table
        printTable(dp, s, t);

        // Print the edit distance
        System.out.println("\nMinimum Edit Distance: " + dp[s.length()][t.length()]);
    }

    public static int[][] calculateEditDistance(String s, String t) {
        int m = s.length();
        int n = t.length();

        int[][] dp = new int[m + 1][n + 1];

        // Initialize the DP table
        for (int i = 0; i <= m; i++) {
            dp[i][0] = i; // Cost of deleting characters from S
        }
        for (int j = 0; j <= n; j++) {
            dp[0][j] = j; // Cost of inserting characters into S
        }

        // Fill the DP table
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                int cost = (s.charAt(i - 1) == t.charAt(j - 1)) ? 0 : 1;

                dp[i][j] = Math.min(
                        dp[i - 1][j] + 1, // Deletion
                        Math.min(
                                dp[i][j - 1] + 1, // Insertion
                                dp[i - 1][j - 1] + cost // Substitution
                        )
                );
            }
        }

        return dp;
    }

    public static void printTable(int[][] dp, String s, String t) {
        int m = s.length();
        int n = t.length();

        // Print column headers (characters of T)
        System.out.print("    ");
        System.out.print("  ");
        for (int j = 0; j < n; j++) {
            System.out.print(t.charAt(j) + " ");
        }
        System.out.println();

        // Print the DP table with row headers (characters of S)
        for (int i = 0; i <= m; i++) {
            if (i == 0) {
                System.out.print("  ");
            } else {
                System.out.print(s.charAt(i - 1) + " ");
            }

            for (int j = 0; j <= n; j++) {
                System.out.print(dp[i][j] + " ");
            }
            System.out.println();
        }
    }
}
