// File Name : Branch and Bound.java
// Description : 알고리즘 HW7 과제 중 3. Branch and Bound Algorithm 구현 입니다.
// - Input : 강의자료 Chapter 9-2, 10p의 그래프 (시작점 A 가정)
// - Output : [A, B, E, C, D, A], 거리 = 16

import java.util.*;

class BranchandBound {

    static class Node {
        List<Character> path;
        int bound;
        int cost;
        char lastNode;

        Node(List<Character> path, int cost, int bound, char lastNode) {
            this.path = new ArrayList<>(path);
            this.cost = cost;
            this.bound = bound;
            this.lastNode = lastNode;
        }
    }

    static Map<Character, Map<Character, Integer>> graph = new HashMap<>();
    static int bestValue = Integer.MAX_VALUE;
    static List<Character> bestSolution = new ArrayList<>();

    static int calculateBound(Node node, Set<Character> remaining) {
        int bound = node.cost;

        // Add minimum outgoing edge for each remaining node
        for (char city : remaining) {
            int minEdge = Integer.MAX_VALUE;
            for (Map.Entry<Character, Integer> neighbor : graph.get(city).entrySet()) {
                minEdge = Math.min(minEdge, neighbor.getValue());
            }
            if (minEdge != Integer.MAX_VALUE) {
                bound += minEdge;
            }
        }
        return bound;
    }

    static void branchAndBoundTSP(char start) {
        PriorityQueue<Node> pq = new PriorityQueue<>(Comparator.comparingInt(n -> n.bound)); // Search min Bound
        List<Character> initialPath = new ArrayList<>();
        initialPath.add(start);

        Node root = new Node(initialPath, 0, calculateBound(new Node(initialPath, 0, 0, start), graph.keySet()), start);
        pq.add(root);

        while (!pq.isEmpty()) {
            Node current = pq.poll();

            if (current.bound >= bestValue) {
                continue;
            }

            if (current.path.size() == graph.size()) {
                current.path.add(start);
                current.cost += graph.get(current.lastNode).get(start);
                // find min
                if (current.cost < bestValue) {
                    bestValue = current.cost;
                    bestSolution = current.path;
                }
                continue;
            }

            for (Map.Entry<Character, Integer> neighbor : graph.get(current.lastNode).entrySet()) {
                char nextCity = neighbor.getKey();

                if (!current.path.contains(nextCity)) {
                    List<Character> newPath = new ArrayList<>(current.path);
                    newPath.add(nextCity);
                    int newCost = current.cost + neighbor.getValue();
                    Set<Character> remaining = new HashSet<>(graph.keySet());
                    remaining.removeAll(newPath);

                    int newBound = calculateBound(new Node(newPath, newCost, 0, nextCity), remaining);

                    if (newBound < bestValue) {
                        pq.add(new Node(newPath, newCost, newBound, nextCity));
                    }
                }
            }
        }
    }

    public static void main(String[] args) {
        // Initialize graph
        graph.put('A', Map.of('B', 2, 'D', 3, 'C', 7));
        graph.put('B', Map.of('A', 2, 'C', 3, 'D', 5, 'E', 6));
        graph.put('C', Map.of('A', 7, 'B', 3, 'D', 4, 'E', 1));
        graph.put('D', Map.of('A', 3, 'B', 5, 'C', 4, 'E', 9));
        graph.put('E', Map.of('A', 10, 'B', 6, 'C', 1, 'D', 9));

        branchAndBoundTSP('A');

        System.out.println(bestSolution + ", 거리 = " + bestValue);
    }
}
