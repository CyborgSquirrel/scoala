package util;

import java.util.ArrayList;
import java.util.Collection;
import java.util.HashMap;

public class DisjointSet {
    private HashMap<Integer, Integer> elems;

    /**
     * Creates a new {@link DisjointSet}.
     */
    public DisjointSet() {
        this.elems = new HashMap<>();
    }

    /**
     * Finds a's canonical element.
     * @param a the element whose canonical element will be found
     * @return a's canonical element
     */
    public int find(int a) {
        if (!this.elems.containsKey(a)) {
            this.elems.put(a, a);
        }

        int p = this.elems.get(a);
        if (a != p) {
            p = this.find(p);
            this.elems.put(a, p);
        }
        return p;
    }

    /**
     * Unites a's and b's sets.
     * @param a
     * @param b
     */
    public void union(int a, int b) {
        a = this.find(a);
        b = this.find(b);
        this.elems.put(a, b);
    }

    /**
     * Check whether a and b belong to the same set.
     * @param a
     * @param b
     * @return whether a and b belong to the same set
     */
    public boolean connected(int a, int b) {
        return this.find(a) == this.find(b);
    }

    /**
     * Get all disjoint sets as map from canonical element to elements in set.
     * @return disjoint sets
     */
    public HashMap<Integer, ArrayList<Integer>> getSetsWithCanonicalElement() {
        HashMap<Integer, ArrayList<Integer>> sets = new HashMap<>();
        for (int element : this.elems.keySet()) {
            int parent = this.find(element);
            if (!sets.containsKey(parent)) {
                sets.put(parent, new ArrayList<>());
            }
            ArrayList<Integer> set = sets.get(parent);
            set.add(element);
        }
        return sets;
    }

    /**
     * Get all disjoint sets.
     * @return disjoint sets
     */
    public Collection<ArrayList<Integer>> getSets() {
        return getSetsWithCanonicalElement().values();
    }
}
