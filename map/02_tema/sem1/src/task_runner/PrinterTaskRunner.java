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
        this.taskRunner.executeOneTask();
        System.out.println("Task has been executed at hour: " + LocalDateTime.now().getHour());
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
