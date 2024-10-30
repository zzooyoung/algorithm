// File Name : Prim.java
// Description : 알고리즘 HW3 과제 중 3.Prim algorithm 구현 입니다.
// - Input 형태: vertex a -> vertex b의 간선의 가중치가 c라고 하면 (a, b, c)로 표현
// - Output 형태: Input 형태와 마찬가지로 vertex a -> vertex b의 간선의 가중치가 c라고 하면 (a, b, c)로 표현


import java.util.*;

public class Prim {
    static class Edge implements Comparable<Edge> {
        int vertex;
        int weight;
        int from; // record first point


        Edge(int from, int vertex, int weight) {
            this.from = from;
            this.vertex = vertex;
            this.weight = weight;
        }

        @Override
        public int compareTo(Edge other) {
            return this.weight - other.weight;
        }
    }

    // Main
    public static void main(String[] args) {
        // (vertex a, vertex b, weight)
        int[][] edges = {
            {0, 1, 3},
            {0, 3, 2},
            {0, 4, 4},
            {1, 2, 1},
            {1, 3, 4},
            {2, 5, 1},
            {3, 4, 5},
            {3, 5, 7},
            {4, 5, 9}
        };

        // Starting Vertex (vertex C, index 2)
        int start = 2;

        // Prim Execute
        primMST(edges, start, 6);  // 6: vertex amount
    }

    public static void primMST(int[][] edges, int start, int n) {
        List<List<Edge>> graph = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            graph.add(new ArrayList<>());
        }

        for (int[] edge : edges) {
            int u = edge[0];
            int v = edge[1];
            int weight = edge[2];
            graph.get(u).add(new Edge(u, v, weight));
            graph.get(v).add(new Edge(v, u, weight));  // for bi-direction
        }
        // sort by weighted using PriorityQueue
        boolean[] visited = new boolean[n];
        PriorityQueue<Edge> pq = new PriorityQueue<>(); 
        visited[start] = true;

        // addtion edges
        for (Edge e : graph.get(start)) { 
            pq.offer(e); 
        }

        List<String> result = new ArrayList<>();

        while (!pq.isEmpty()) {
            Edge edge = pq.poll(); // lower weight
            int u = edge.from;
            int v = edge.vertex;
            int weight = edge.weight;

            if (visited[v]) continue;

            result.add("(" + u + ", " + v + ", " + weight + ")");
            visited[v] = true;

            // No cycle
            for (Edge e : graph.get(v)) {
                if (!visited[e.vertex]) {
                    pq.offer(e);
                }
            }
        }

        // print
        for (String edge : result) {
            System.out.println(edge);
        }
    }
}
