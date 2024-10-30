import java.util.*;

public class SetCover {

    public static void main(String[] args) {
        // Universal Set (list)
        List<Integer> U = new ArrayList<>(Arrays.asList(1, 2, 3, 4, 5, 6, 7, 8, 9, 10));

        // subset F (each vertex edge)
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

        // Set Cover execute
        List<String> coverSet = setCover(U, F);

        // print result
        System.out.print("C = {");
        StringJoiner sj = new StringJoiner(", ");
        for (String s : coverSet) {
            sj.add(s);
        }
        System.out.print(sj.toString() + "}");
    }

    public static List<String> setCover(List<Integer> U, Map<String, List<Integer>> F) {
        List<String> C = new ArrayList<>(); // select sets
        while (!U.isEmpty()) {
            String bestSet = null;
            int maxCovered = 0;

            // Max Si
            for (Map.Entry<String, List<Integer>> entry : F.entrySet()) {
                List<Integer> currentSet = entry.getValue();
                int coveredCount = countIntersection(U, currentSet);

                if (coveredCount > maxCovered) {
                    maxCovered = coveredCount;
                    bestSet = entry.getKey();
                }
            }

            // Addition C, removed covered vertex
            if (bestSet != null) {
                C.add(bestSet);                  
                removeElements(U, F.get(bestSet));
                F.remove(bestSet);
            }
        }
        return C;
    }

    
    public static int countIntersection(List<Integer> U, List<Integer> currentSet) {
        int count = 0;
        for (int element : currentSet) {
            if (U.contains(element)) {
                count++;
            }
        }
        return count;
    }

    // U - currentSet
    public static void removeElements(List<Integer> U, List<Integer> currentSet) {
        U.removeIf(currentSet::contains); 
    }
}
