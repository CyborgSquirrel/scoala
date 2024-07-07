package container;

import model.Task;
import utils.Constants;

public class QueueContainer extends SizedContainer {

    /**
     * Construct a {@link QueueContainer}.
     */
    public QueueContainer() {
        super();
    }

    /**
     * Remove a task from the {@link QueueContainer}.
     * @return the task which was removed
     */
    @Override
    public Task remove() {
        if (!this.isEmpty()) {
            Task removedTask = this.tasks[0];
            for (int i = 1; i < this.size; ++i) {
                this.tasks[i - 1] = this.tasks[i];
            }
            this.size--;
            return removedTask;
        }
        return null;
    }

    /**
     * Add a task to the {@link QueueContainer}.
     * @param task the task which will be added
     */
    @Override
    public void add(Task task) {
        if (this.size >= this.tasks.length) {
            Task newTasks[] = new Task[this.tasks.length*2];
            System.arraycopy(this.tasks, 0, newTasks, 0, this.tasks.length);
            this.tasks = newTasks;
        }
        this.tasks[this.size] = task;
        this.size++;
    }

}
