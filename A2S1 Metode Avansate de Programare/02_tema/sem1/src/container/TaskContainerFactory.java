package container;

// TODO: QUESTION: What type should the Strategy for the abstract Factory be?
public class TaskContainerFactory implements Factory {
    static TaskContainerFactory instance = null;

    /**
     * Construct a {@link TaskContainerFactory}.
     */
    private TaskContainerFactory() {

    }

    /**
     * Get an instance of the {@link TaskContainerFactory}.
     * @return the {@link TaskContainerFactory} instance
     */
    public static TaskContainerFactory getInstance() {
        if (TaskContainerFactory.instance == null) {
            TaskContainerFactory.instance = new TaskContainerFactory();
        }
        return TaskContainerFactory.instance;
    }

    /**
     * Create a container.
     * @param containerStrategy
     * @return a container with the provided strategy, or null if no container could be created
     */
    public Container createContainer(ContainerStrategy containerStrategy) {
        /*  */ if (containerStrategy == ContainerStrategy.STACK) {
            return new StackContainer();
        } else if (containerStrategy == ContainerStrategy.QUEUE) {
            return new QueueContainer();
        }
        return null;
    }
}
