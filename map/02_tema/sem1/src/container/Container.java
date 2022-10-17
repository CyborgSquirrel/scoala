package container;

import model.Task;

public interface Container {
    /**
     * Removes a task from the container.
     * @return task which was removed
     */
    Task remove();

    /**
     * Adds a task to the container.
     * @param task task which will be added
     */
    void add(Task task);

    /**
     * Returns the size of the container.
     * @return the size of the container
     */
    int size();

    /**
     * Checks whether the container is empty.
     * @return whether the container is empty
     */
    boolean isEmpty();
}
