package container;

import model.Task;
import utils.Constants;

public abstract class SizedContainer implements Container {
    protected int size;
    protected Task[] tasks;

    /**
     * Constructs a {@link SizedContainer}.
     */
    public SizedContainer() {
        this.size = 0;
        this.tasks = new Task[Constants.TASKS_INITIAL_SIZE];
    }

    /**
     * Returns the size of the container.
     * @return the size of the container
     */
    @Override
    public int size() {
        return this.size;
    }

    /**
     * Checks whether the container is empty.
     * @return whether the container is empty
     */
    @Override
    public boolean isEmpty() {
        return this.size == 0;
    }
}
