package task_runner;

import model.Task;

public abstract class AbstractTaskRunner implements TaskRunner {
    private TaskRunner taskRunner;

    /**
     * Constructs an {@link AbstractTaskRunner}, which will decorate the provided {@link TaskRunner}.
     * @param taskRunner the {@link TaskRunner} which will be decorated
     */
    public AbstractTaskRunner(TaskRunner taskRunner) {
        this.taskRunner = taskRunner;
    }

    @Override
    public void executeOneTask() {
        taskRunner.executeOneTask();
    }

    @Override
    public void executeAll() {
        while (taskRunner.hasTask()) {
            executeOneTask();
        }
    }

    @Override
    public void addTask(Task t) {
        taskRunner.addTask(t);
    }

    @Override
    public boolean hasTask() {
        return taskRunner.hasTask();
    }
}
