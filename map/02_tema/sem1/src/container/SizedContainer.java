package container;

import model.Task;
import utils.Constants;

public abstract class SizedContainer implements Container {
    protected int size;
    protected Task[] tasks;

    public SizedContainer() {
        this.size = 0;
        this.tasks = new Task[Constants.TASKS_INITIAL_SIZE];
    }

    @Override
    public int size() {
        return this.size;
    }

    @Override
    public boolean isEmpty() {
        return this.size == 0;
    }
}
