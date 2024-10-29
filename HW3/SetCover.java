import java.util.*;

public class SetCover {
    // 각 마을 간 연결 상태를 인접 리스트로 표현합니다.
    static Map<Integer, Set<Integer>> adjacencyList = new HashMap<>();
    static List<Set<Integer>> sets = new ArrayList<>(); // 커버 가능한 집합들
    static Set<Integer> universe = new HashSet<>(); // 모든 마을 집합
    static List<Set<Integer>> optimalSolution = new ArrayList<>();
    
    public static void main(String[] args) {
        // 그래프 초기화 및 마을 간 연결 정의
        initGraph();

        // 모든 마을 추가
        for (int i = 1; i <= 10; i++) {
            universe.add(i);
        }
        
        // 각 마을에서 접근 가능한 부분 집합 생성
        for (int node : universe) {
            Set<Integer> coverSet = new HashSet<>(adjacencyList.get(node));
            coverSet.add(node);
            sets.add(coverSet);
        }
        
        // Greedy Set Cover 실행
        List<Set<Integer>> greedySolution = greedySetCover();
        
        // 최적 솔루션 실행 및 비교
        optimalSolution = findOptimalCover(new ArrayList<>(), new HashSet<>(), 0);

        // 결과 출력
        System.out.print("Greedy Solution: ");
        printSolution(greedySolution);
        
        System.out.print("Optimal Solution: ");
        printSolution(optimalSolution);
    }

    // 그래프 초기화 함수 (새로운 엣지 정보에 맞춰 수정)
    private static void initGraph() {
        addEdge(1, 2);
        addEdge(1, 3);
        addEdge(1, 8);
        addEdge(2, 3);
        addEdge(2, 4);
        addEdge(2, 8);
        addEdge(3, 4);
        addEdge(4, 5);
        addEdge(4, 7);
        addEdge(4, 8);
        addEdge(5, 6);
        addEdge(5, 7);
        addEdge(6, 7);
        addEdge(6, 9);
        addEdge(6, 10);
    }

    // 마을 간 연결 정의 함수
    private static void addEdge(int u, int v) {
        adjacencyList.computeIfAbsent(u, k -> new HashSet<>()).add(v);
        adjacencyList.computeIfAbsent(v, k -> new HashSet<>()).add(u);
    }

    // Greedy Set Cover 알고리즘 구현
    private static List<Set<Integer>> greedySetCover() {
        Set<Integer> covered = new HashSet<>();
        List<Set<Integer>> solution = new ArrayList<>();

        while (!covered.containsAll(universe)) {
            Set<Integer> bestSet = null;
            int maxCover = 0;

            for (Set<Integer> set : sets) {
                Set<Integer> temp = new HashSet<>(set);
                temp.removeAll(covered);
                if (temp.size() > maxCover) {
                    maxCover = temp.size();
                    bestSet = set;
                }
            }

            if (bestSet != null) {
                solution.add(bestSet);
                covered.addAll(bestSet);
            }
        }
        return solution;
    }

    // 모든 가능한 커버를 찾는 최적 솔루션 구현
    private static List<Set<Integer>> findOptimalCover(List<Set<Integer>> currentSolution, Set<Integer> covered, int index) {
        if (covered.containsAll(universe)) {
            return new ArrayList<>(currentSolution);
        }
        if (index >= sets.size()) {
            return null;
        }

        List<Set<Integer>> withSet = null;
        if (sets.get(index) != null) {
            currentSolution.add(sets.get(index));
            Set<Integer> newCovered = new HashSet<>(covered);
            newCovered.addAll(sets.get(index));
            withSet = findOptimalCover(currentSolution, newCovered, index + 1);
            currentSolution.remove(currentSolution.size() - 1);
        }

        List<Set<Integer>> withoutSet = findOptimalCover(currentSolution, covered, index + 1);

        if (withSet == null) return withoutSet;
        if (withoutSet == null) return withSet;
        
        return withSet.size() < withoutSet.size() ? withSet : withoutSet;
    }

    // 결과 형식에 맞춰 출력하는 함수
    private static void printSolution(List<Set<Integer>> solution) {
        if (solution == null) {
            System.out.println("해당 솔루션이 존재하지 않습니다.");
            return;
        }
        StringBuilder sb = new StringBuilder();
        sb.append("C = {");
        for (int i = 0; i < solution.size(); i++) {
            int setIndex = sets.indexOf(solution.get(i)) + 1;
            sb.append("S_").append(setIndex);
            if (i < solution.size() - 1) {
                sb.append(", ");
            }
        }
        sb.append("}");
        System.out.println(sb.toString());
    }
}
