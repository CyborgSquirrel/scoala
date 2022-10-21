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
        super.executeOneTask();
    }
}
