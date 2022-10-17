package task_runner;

import model.Task;

public abstract class AbstractTaskRunner implements TaskRunner {
    protected TaskRunner taskRunner;

    /**
     * Constructs an {@link AbstractTaskRunner}, which will decorate the provided {@link TaskRunner}.
     * @param taskRunner the {@link TaskRunner} which will be decorated
     */
    public AbstractTaskRunner(TaskRunner taskRunner) {
        this.taskRunner = taskRunner;
    }
}
