package container;

import model.Task;
import utils.Constants;

public class StackContainer extends SizedContainer {

    public StackContainer() {
        super();
    }

    public Task remove() {
        if (!isEmpty()) {
            size--;
            return tasks[size];
        }
        return null;
    }

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
