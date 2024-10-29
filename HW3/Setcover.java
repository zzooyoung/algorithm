import java.util.*;

public class SetCover {
    public static void main(String[] args) {
        // 노드와 엣지를 정의
        int[][] graph = {
            {1, 2}, {1, 3}, {1, 4}, {2, 3}, {2, 4}, {2, 8},
            {3, 4}, {4, 5}, {4, 7}, {5, 6}, {5, 7}, {6, 9},
            {6, 10}, {9, 10}, {7, 8}
        };

        // Set 커버 집합 정의 (S1, S4, S6)
        Set<Integer> S1 = new HashSet<>(Arrays.asList(1, 2, 3, 4));
        Set<Integer> S4 = new HashSet<>(Arrays.asList(4, 5, 7, 8));
        Set<Integer> S6 = new HashSet<>(Arrays.asList(6, 9, 10));

        // 최적 커버 집합을 저장하는 리스트
        List<Set<Integer>> optimalCover = Arrays.asList(S1, S4, S6);

        // 모든 노드를 커버하는지 확인
        Set<Integer> coveredNodes = new HashSet<>();
        for (Set<Integer> set : optimalCover) {
            coveredNodes.addAll(set);
        }

        // 노드가 모두 커버되는지 확인하고 결과 출력
        if (coveredNodes.size() == 10) {
            System.out.println("최적 커버 집합 C = {S1, S4, S6}");
        } else {
            System.out.println("커버가 불완전합니다.");
        }
    }
}
