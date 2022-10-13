package model.sorter;

import java.util.ArrayList;
import java.util.Collections;

public class BubbleSorter extends AbstractSorter {

    @Override
    public void sort(ArrayList<Integer> list) {
        for (int i = 0; i < list.size(); ++i) {
            for (int j = 0; j < list.size()-i-1; ++j) {
                if (list.get(j) > list.get(j+1)) {
                    Collections.swap(list, j, j+1);
                }
            }
        }
    }
}
