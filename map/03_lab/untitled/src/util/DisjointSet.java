package util;

import java.util.ArrayList;
import java.util.Collection;
import java.util.HashMap;

public class DisjointSet {
    private HashMap<Integer, Integer> elems;
    public DisjointSet() {
        this.elems = new HashMap<>();
    }
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
    public void union(int a, int b) {
        a = this.find(a);
        b = this.find(b);
        this.elems.put(a, b);
    }
    public boolean connected(int a, int b) {
        return this.find(a) == this.find(b);
    }
    public Collection<ArrayList<Integer>> getSets() {
        HashMap<Integer, ArrayList<Integer>> sets = new HashMap<>();
        for (int element : this.elems.values()) {
            int parent = this.find(element);
            if (!sets.containsKey(parent)) {
                sets.put(parent, new ArrayList<>());
            }
            ArrayList<Integer> set = sets.get(parent);
            set.add(element);
        }
        return sets.values();
    }
}
