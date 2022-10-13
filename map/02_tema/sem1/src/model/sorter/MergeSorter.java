package model.sorter;

import java.util.ArrayList;

public class MergeSorter extends AbstractSorter {
    @Override
    public void sort(ArrayList<Integer> list) {
        mergeSort(list, 0, list.size()-1);
    }

    void mergeSort(ArrayList<Integer> list, int lt, int rt) {
        if (rt-lt+1 > 1) {
            int mid = (lt+rt) / 2;

            mergeSort(list, lt, mid);
            mergeSort(list, mid+1, rt);

            ArrayList<Integer> tmp = new ArrayList<Integer>(rt-lt+1);
            {
                int i = lt;
                int j = mid + 1;
                while (i <= mid && j <= rt) {
                    if (list.get(i) < list.get(j)) {
                        tmp.add(list.get(i));
                        i++;
                    } else {
                        tmp.add(list.get(j));
                        j++;
                    }
                }
                while (i <= mid) {
                    tmp.add(list.get(i));
                    i++;
                }
                while (j <= rt) {
                    tmp.add(list.get(j));
                    j++;
                }
            }

            for (int i = lt; i <= rt; ++i) {
                list.set(i, tmp.get(i-lt));
            }
        }
    }
}
