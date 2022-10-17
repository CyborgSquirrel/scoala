package container;

public interface Factory {
    /**
     * Creates a container with the provided strategy.
     * @param containerStrategy the strategy with which the container will be created
     * @return the container
     */
    Container createContainer(ContainerStrategy containerStrategy);
}
