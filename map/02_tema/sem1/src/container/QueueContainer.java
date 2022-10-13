package container;

import model.Task;
import utils.Constants;

public class QueueContainer extends SizedContainer {

    public QueueContainer() {
        super();
    }

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
