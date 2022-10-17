package model;

import model.sorter.AbstractSorter;

import java.util.ArrayList;

public class SortingTask extends Task {
    ArrayList<Integer> list;
    AbstractSorter sorter;

    /**
     * Constructs a sorting task.
     * @param taskId
     * @param description
     * @param list
     * @param sorter
     */
    public SortingTask(String taskId, String description, ArrayList<Integer> list, AbstractSorter sorter) {
        super(taskId, description);
        this.list = list;
        this.sorter = sorter;
    }

    /**
     * Sorts the list.
     */
    @Override
    public void execute() {
        this.sorter.sort(this.list);
        System.out.println(this.list);
    }
}
