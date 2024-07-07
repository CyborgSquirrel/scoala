package task_runner;

import model.Task;

import java.time.LocalDateTime;

public class PrinterTaskRunner extends AbstractTaskRunner {
    /**
     * Constructs a {@link PrinterTaskRunner}.
     * @param taskRunner
     */
    public PrinterTaskRunner(TaskRunner taskRunner) {
        super(taskRunner);
    }

    /**
     * Executes one task, then prints a status message.
     */
    @Override
    public void executeOneTask() {
        super.executeOneTask();
        System.out.println("Task has been executed at hour: " + LocalDateTime.now().getHour());
    }
}
