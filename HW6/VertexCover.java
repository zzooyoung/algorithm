// File Name : VertexCover.java
// Description : 알고리즘 HW6 과제 중 2. Vertex Cover Algorithm 구현 입니다.
// - Input : Graph
// - Output : maximal matching에 의한 Edge의 집합 (단, Edge는 A-B, G-H의 형태로 표시)
import java.util.*;

public class VertexCover {

    static class Graph {
        private Map<Integer, Set<Integer>> adjList;

        public Graph() {
            adjList = new HashMap<>();
        }

        // Add edge to the graph 
        public void addEdge(int u, int v) {
            adjList.putIfAbsent(u, new HashSet<>());
            adjList.putIfAbsent(v, new HashSet<>());
            adjList.get(u).add(v);
            adjList.get(v).add(u);
        }

        // vertices in the graph
        public Set<Integer> getVertices() {
            return adjList.keySet();
        }

        // all neighbors of a vertex
        public Set<Integer> getNeighbors(int u) {
            return adjList.getOrDefault(u, new HashSet<>());
        }

        // all edges in the graph 
        public Set<String> getEdges() {
            Set<String> edges = new HashSet<>();
            for (int u : adjList.keySet()) {
                for (int v : adjList.get(u)) {
                    if (u < v) {
                        edges.add((char)(u + 'A') + "-" + (char)(v + 'A'));
                    }
                }
            }
            return edges;
        }
    }

    // Maximal Matching using Greedy
    public static Set<String> findMaximalMatching(Graph graph) {
        Set<String> matching = new HashSet<>(); 
        Set<Integer> visited = new HashSet<>();
        
        for (int u : graph.getVertices()) {
            if (!visited.contains(u)) {
                for (int v : graph.getNeighbors(u)) {
                    if (!visited.contains(v)) {
                        matching.add((char)(u + 'A') + "-" + (char)(v + 'A'));
                        visited.add(u);
                        visited.add(v);
                        break; 
                    }
                }
            }
        }
        return matching;
    }

    public static void main(String[] args) {
        Graph graph = new Graph();

        // Input edges in input Gragh
        graph.addEdge(0, 4);  // A-E
        graph.addEdge(1, 2);  // B-C
        graph.addEdge(1, 4);  // B-E
        graph.addEdge(1, 5);  // B-F
        graph.addEdge(1, 6);  // B-G
        graph.addEdge(2, 3);  // C-D
        graph.addEdge(3, 7);  // D-H
        graph.addEdge(4, 8);  // E-I
        graph.addEdge(4, 9);  // E-J
        graph.addEdge(4, 5);  // E-F
        graph.addEdge(5, 9);  // F-J
        graph.addEdge(5, 6);  // F-G
        graph.addEdge(6, 10); // G-K
        graph.addEdge(6, 11); // G-L
        graph.addEdge(7, 11); // H-L
        graph.addEdge(8, 12); // I-M
        graph.addEdge(8, 9);  // I-J
        graph.addEdge(9, 12); // J-M
        graph.addEdge(9, 13); // J-N
        graph.addEdge(9, 14); // J-O
        graph.addEdge(9, 10); // J-K
        graph.addEdge(10, 14); // K-O
        graph.addEdge(10, 11); // K-L
        graph.addEdge(11, 15); // L-P
        graph.addEdge(2, 7);  // C-H
        graph.addEdge(3, 6);  // D-G
        graph.addEdge(6, 9);  // G-J
        graph.addEdge(6, 7);  // G-H
        graph.addEdge(11, 14); // L-O

        // Find the maximal matching
        Set<String> maximalMatching = findMaximalMatching(graph);
        
        // Print result maximal matching
        System.out.println("Maximal Matching:");
        for (String edge : maximalMatching) {
            System.out.println(edge);
        }
    }
}
