import java.util.*;

class Edge {
    int src, dest, weight;
    
    Edge(int src, int dest, int weight) {
        this.src = src;
        this.dest = dest;
        this.weight = weight;
    }
}

public class Prim {
    private static final int V = 6; // 정점 개수 (a:0, b:1, c:2, d:3, e:4, f:5)
    private static List<Edge>[] adjList = new ArrayList[V];

    public static void main(String[] args) {
        // 간선 리스트 입력
        List<Edge> edges = Arrays.asList(
            new Edge(0, 1, 3),
            new Edge(0, 3, 2),
            new Edge(0, 4, 4),
            new Edge(1, 2, 1),
            new Edge(1, 5, 2),
            new Edge(1, 3, 4),
            new Edge(2, 5, 1),
            new Edge(3, 4, 5),
            new Edge(3, 5, 7),
            new Edge(4, 5, 9)
        );

        // 인접 리스트 초기화 및 간선 추가
        for (int i = 0; i < V; i++) {
            adjList[i] = new ArrayList<>();
        }
        for (Edge edge : edges) {
            adjList[edge.src].add(edge);
            adjList[edge.dest].add(new Edge(edge.dest, edge.src, edge.weight)); // 무방향 그래프이므로 반대 방향도 추가
        }

        // Prim 알고리즘 실행
        primMST(2); // 시작 정점을 2 (즉, C)로 설정
    }

    private static void primMST(int startVertex) {
        int[] parent = new int[V];
        int[] key = new int[V];
        boolean[] inMST = new boolean[V];
        
        Arrays.fill(key, Integer.MAX_VALUE);
        key[startVertex] = 0; // 시작 정점의 키를 0으로 설정
        parent[startVertex] = -1; // 시작 정점은 부모가 없음

        // 실행 시간 측정 시작
        long startTime = System.nanoTime();

        for (int count = 0; count < V - 1; count++) {
            int u = minKey(key, inMST);
            inMST[u] = true;

            for (Edge edge : adjList[u]) {
                int v = edge.dest;
                int weight = edge.weight;
                if (!inMST[v] && weight < key[v]) {
                    parent[v] = u;
                    key[v] = weight;
                }
            }
        }

        // 실행 시간 측정 종료
        long endTime = System.nanoTime();
        double durationMillis = (endTime - startTime) / 1e6;

        // MST 출력
        printMST(parent, key);

        // 실행 시간 출력
        System.out.printf("Running time: %.3f ms\n", durationMillis);
    }

    // 현재 MST에 포함되지 않은 정점들 중 최소 가중치를 갖는 정점을 찾는 함수
    private static int minKey(int[] key, boolean[] inMST) {
        int min = Integer.MAX_VALUE, minIndex = -1;
        for (int v = 0; v < V; v++) {
            if (!inMST[v] && key[v] < min) {
                min = key[v];
                minIndex = v;
            }
        }
        return minIndex;
    }

    // MST 결과 출력 함수
    private static void printMST(int[] parent, int[] key) {
        System.out.println("Minimum Spanning Tree:");
        
        List<int[]> result = new ArrayList<>();
        for (int i = 1; i < V; i++) {  // 정점 2에서 시작
            if (parent[i] != -1) {
                result.add(new int[]{parent[i], i, key[i]});
            }
        }

        // 결과를 지정된 순서로 출력
        result.sort((a, b) -> {
            if (a[0] != b[0]) return Integer.compare(a[0], b[0]);
            return Integer.compare(a[1], b[1]);
        });

        for (int[] edge : result) {
            System.out.printf("(%d, %d, %d)\n", edge[0], edge[1], edge[2]);
        }
    }
}
