package container;

// TODO: QUESTION: What type should the Strategy for the abstract Factory be?
public class TaskContainerFactory implements Factory {
    static TaskContainerFactory instance = null;
    TaskContainerFactory() {

    }

    public static TaskContainerFactory getInstance() {
        if (TaskContainerFactory.instance == null) {
            TaskContainerFactory.instance = new TaskContainerFactory();
        }
        return TaskContainerFactory.instance;
    }

    public Container createContainer(ContainerStrategy containerStrategy) {
        /*  */ if (containerStrategy == ContainerStrategy.STACK) {
            return new StackContainer();
        } else if (containerStrategy == ContainerStrategy.QUEUE) {
            return new QueueContainer();
        }
        return null;
    }
}
