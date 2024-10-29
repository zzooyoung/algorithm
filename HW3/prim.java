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
    private static final int V = 6; // 정점의 수 (a:0, b:1, c:2, d:3, e:4, f:5)

    int minKey(int[] key, boolean[] mstSet) {
        int min = Integer.MAX_VALUE, minIndex = -1;
        for (int v = 0; v < V; v++) {
            if (!mstSet[v] && key[v] < min) {
                min = key[v];
                minIndex = v;
            }
        }
        return minIndex;
    }

    void primMST(int[][] graph) {
        int[] parent = new int[V];
        int[] key = new int[V];
        boolean[] mstSet = new boolean[V];
        
        Arrays.fill(key, Integer.MAX_VALUE);
        key[0] = 0; // 시작점 a를 선택하여 key 값 0으로 설정
        parent[0] = -1;

        for (int count = 0; count < V - 1; count++) {
            int u = minKey(key, mstSet);
            mstSet[u] = true;

            for (int v = 0; v < V; v++) {
                if (graph[u][v] != 0 && !mstSet[v] && graph[u][v] < key[v]) {
                    parent[v] = u;
                    key[v] = graph[u][v];
                }
            }
        }

        printMST(parent, graph);
    }

    void printMST(int[] parent, int[][] graph) {
        System.out.println("Minimum Spanning Tree (a:0, b:1, c:2, d:3, e:4, f:5):");
        for (int i = 1; i < V; i++) {
            System.out.println("(" + parent[i] + ", " + i + ", " + graph[i][parent[i]] + ")");
        }
    }

    public static void main(String[] args) {
        Prim mst = new Prim();
        
        int[][] graph = {
            {0, 3, 0, 2, 4, 0}, // a
            {3, 0, 1, 4, 0, 2}, // b
            {0, 1, 0, 0, 0, 1}, // c
            {2, 4, 0, 0, 5, 7}, // d
            {4, 0, 0, 5, 0, 9}, // e
            {0, 2, 1, 7, 9, 0}  // f
        };

        long startTime = System.nanoTime();
        mst.primMST(graph);
        long endTime = System.nanoTime();
        
        System.out.println("Running Time: " + (endTime - startTime) + " nanoseconds");
    }
}
