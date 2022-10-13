package task_runner;

import container.Container;
import container.TaskContainerFactory;
import model.Task;
import container.ContainerStrategy;

public class StrategyTaskRunner implements TaskRunner {
    private Container container;

    public StrategyTaskRunner(ContainerStrategy containerStrategy) {
        TaskContainerFactory taskContainerFactory = TaskContainerFactory.getInstance();
        this.container = taskContainerFactory.createContainer(containerStrategy);
    }

    @Override
    public void executeOneTask() {
        Task task = container.remove();
        task.execute();
    }

    @Override
    public void executeAll() {
        while (!container.isEmpty()) {
            executeOneTask();
        }
    }

    @Override
    public void addTask(Task t) {
        container.add(t);
    }

    @Override
    public boolean hasTask() {
        return !container.isEmpty();
    }
}
