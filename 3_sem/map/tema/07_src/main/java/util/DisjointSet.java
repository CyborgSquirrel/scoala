package util;

import java.util.ArrayList;
import java.util.Collection;
import java.util.HashMap;

public class DisjointSet<T> {
    private HashMap<T, T> elems;

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
    public T find(T a) {
        if (!this.elems.containsKey(a)) {
            this.elems.put(a, a);
        }

        T p = this.elems.get(a);
        if (!a.equals(p)) {
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
    public void union(T a, T b) {
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
    public boolean connected(T a, T b) {
        return this.find(a).equals(this.find(b));
    }

    /**
     * Get all disjoint sets as map from canonical element to elements in set.
     * @return disjoint sets
     */
    public HashMap<T, ArrayList<T>> getSetsWithCanonicalElement() {
        HashMap<T, ArrayList<T>> sets = new HashMap<>();
        for (T element : this.elems.keySet()) {
            T parent = this.find(element);
            if (!sets.containsKey(parent)) {
                sets.put(parent, new ArrayList<>());
            }
            ArrayList<T> set = sets.get(parent);
            set.add(element);
        }
        return sets;
    }

    /**
     * Get all disjoint sets.
     * @return disjoint sets
     */
    public Collection<ArrayList<T>> getSets() {
        return getSetsWithCanonicalElement().values();
    }
}
