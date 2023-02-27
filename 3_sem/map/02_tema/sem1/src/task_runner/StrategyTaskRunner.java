package task_runner;

import container.Container;
import container.TaskContainerFactory;
import model.Task;
import container.ContainerStrategy;

public class StrategyTaskRunner implements TaskRunner {
    private final Container container;

    /**
     * Constructs a {@link StrategyTaskRunner}.
     * @param containerStrategy the strategy with which the container will be created
     */
    public StrategyTaskRunner(ContainerStrategy containerStrategy) {
        TaskContainerFactory taskContainerFactory = TaskContainerFactory.getInstance();
        this.container = taskContainerFactory.createContainer(containerStrategy);
    }

    /**
     * Executes one task.
     */
    @Override
    public void executeOneTask() {
        Task task = container.remove();
        task.execute();
    }

    /**
     * Executes all the tasks.
     */
    @Override
    public void executeAll() {
        while (!container.isEmpty()) {
            executeOneTask();
        }
    }

    /**
     * Adds a task.
     * @param t
     */
    @Override
    public void addTask(Task t) {
        container.add(t);
    }

    /**
     * Checks whether there are any tasks left.
     * @return
     */
    @Override
    public boolean hasTask() {
        return !container.isEmpty();
    }
}
