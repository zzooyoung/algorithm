import java.util.*;

public class SetCover {

    public static void main(String[] args) {
        // 집합 U 정의 (전체 마을 번호)
        List<Integer> U = new ArrayList<>(Arrays.asList(1, 2, 3, 4, 5, 6, 7, 8, 9, 10));

        // 부분 집합 F 정의 (각 마을 연결 정보를 저장)
        Map<String, List<Integer>> F = new LinkedHashMap<>();
        F.put("S1", Arrays.asList(1, 2, 3, 8));
        F.put("S2", Arrays.asList(1, 2, 3, 4, 8));
        F.put("S3", Arrays.asList(1, 2, 3, 4));
        F.put("S4", Arrays.asList(2, 3, 4, 5, 7, 8));
        F.put("S5", Arrays.asList(4, 5, 6, 7));
        F.put("S6", Arrays.asList(5, 6, 7, 9, 10));
        F.put("S7", Arrays.asList(4, 5, 6, 7));
        F.put("S8", Arrays.asList(1, 2, 4, 8));
        F.put("S9", Arrays.asList(6, 9));
        F.put("S10", Arrays.asList(6, 10));

        // Set Cover 알고리즘 실행
        List<String> coverSet = setCover(U, F);

        // 결과 출력
        System.out.print("C = {");
        StringJoiner sj = new StringJoiner(", ");
        for (String s : coverSet) {
            sj.add(s);
        }
        System.out.print(sj.toString() + "}");
    }

    public static List<String> setCover(List<Integer> U, Map<String, List<Integer>> F) {
        List<String> C = new ArrayList<>(); // 선택된 집합들
        while (!U.isEmpty()) {
            String bestSet = null;
            int maxCovered = 0;

            // U의 원소를 가장 많이 가진 집합 Si 선택
            for (Map.Entry<String, List<Integer>> entry : F.entrySet()) {
                List<Integer> currentSet = entry.getValue();
                int coveredCount = countIntersection(U, currentSet);

                if (coveredCount > maxCovered) {
                    maxCovered = coveredCount;
                    bestSet = entry.getKey();
                }
            }

            // 선택된 집합을 C에 추가하고 U에서 해당 원소 제거
            if (bestSet != null) {
                C.add(bestSet);                  // 최적의 집합을 결과 집합 C에 추가
                removeElements(U, F.get(bestSet)); // U에서 커버된 마을 제거
                F.remove(bestSet);                // 선택된 집합을 F에서 제거
            }
        }
        return C;
    }

    // 두 리스트의 교집합 원소 개수를 세는 함수
    public static int countIntersection(List<Integer> U, List<Integer> currentSet) {
        int count = 0;
        for (int element : currentSet) {
            if (U.contains(element)) {
                count++;
            }
        }
        return count;
    }

    // U에서 currentSet에 포함된 원소들을 제거하는 함수
    public static void removeElements(List<Integer> U, List<Integer> currentSet) {
        U.removeIf(currentSet::contains); // currentSet에 있는 모든 원소를 U에서 제거
    }
}
