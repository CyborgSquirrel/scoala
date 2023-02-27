package container;

import model.Task;
import utils.Constants;

public class StackContainer extends SizedContainer {

    /**
     * Construct a {@link StackContainer}.
     */
    public StackContainer() {
        super();
    }

    /**
     * Remove a task from the {@link StackContainer}.
     * @return the task which was removed
     */
    public Task remove() {
        if (!isEmpty()) {
            size--;
            return tasks[size];
        }
        return null;
    }

    /**
     * Add a task to the {@link StackContainer}.
     * @param task the task which will be added
     */
    public void add(Task task) {
        if (tasks.length <= size) {
            Task newTasks[] = new Task[tasks.length * 2];
            System.arraycopy(tasks, 0, newTasks, 0, tasks.length);
            tasks = newTasks;
        }
        tasks[size] = task;
        size++;
    }
}
