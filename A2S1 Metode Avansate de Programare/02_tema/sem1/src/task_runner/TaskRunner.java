package task_runner;

import model.Task;

public interface TaskRunner {
    /**
     * Executes one task.
     */
    void executeOneTask();
    /**
     * Executes all the tasks.
     */
    void executeAll();
    /**
     * Adds a task.
     * @param t
     */
    void addTask(Task t);
    /**
     * Checks whether there are any tasks left.
     * @return
     */
    boolean hasTask();
}
