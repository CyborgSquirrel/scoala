package task_runner;

import model.Task;

import java.time.LocalDateTime;

public class PrinterTaskRunner extends AbstractTaskRunner {
    public PrinterTaskRunner(TaskRunner taskRunner) {
        super(taskRunner);
    }

    @Override
    public void executeOneTask() {
        this.taskRunner.executeOneTask();
        System.out.println("Task has been executed at hour: " + LocalDateTime.now().getHour());
    }

    @Override
    public void executeAll() {
        while (hasTask()) {
            executeOneTask();
        }
    }

    @Override
    public void addTask(Task t) {
        this.taskRunner.addTask(t);
    }

    @Override
    public boolean hasTask() {
        return this.taskRunner.hasTask();
    }
}
