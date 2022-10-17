package task_runner;

import model.Task;

public class DelayTaskRunner extends AbstractTaskRunner {
    /**
     * Constructs a {@link DelayTaskRunner}.
     * @param taskRunner
     */
    public DelayTaskRunner(TaskRunner taskRunner) {
        super(taskRunner);
    }

    /**
     * Waits 3 seconds, then executes one task.
     */
    @Override
    public void executeOneTask() {
        try {
            Thread.sleep(3_000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        this.taskRunner.executeOneTask();
    }

    /**
     * Executes all the tasks.
     */
    @Override
    public void executeAll() {
        while (hasTask()) {
            executeOneTask();
        }
    }

    /**
     * Adds a task.
     * @param t
     */
    @Override
    public void addTask(Task t) {
        this.taskRunner.addTask(t);
    }

    /**
     * Checks whether there are any tasks left.
     * @return
     */
    @Override
    public boolean hasTask() {
        return this.taskRunner.hasTask();
    }
}
