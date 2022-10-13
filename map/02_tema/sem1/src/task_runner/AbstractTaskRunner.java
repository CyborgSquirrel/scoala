package task_runner;

import model.Task;

public abstract class AbstractTaskRunner implements TaskRunner {
    protected TaskRunner taskRunner;

    public AbstractTaskRunner(TaskRunner taskRunner) {
        this.taskRunner = taskRunner;
    }
}
