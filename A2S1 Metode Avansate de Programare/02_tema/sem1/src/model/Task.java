package model;

import java.util.Objects;

public abstract class Task {
    String taskId;
    String description;

    /**
     * Constructs a {@link Task}.
     * @param taskId
     * @param description
     */
    public Task(String taskId, String description) {
        this.taskId = taskId;
        this.description = description;
    }

    /**
     * Returns the task's id.
     * @return
     */
    public String getTaskId() {
        return taskId;
    }

    /**
     * Gets the task's description.
     * @return
     */
    public String getDescription() {
        return description;
    }

    /**
     * Sets the task's description.
     * @param description
     */
    public void setDescription(String description) {
        this.description = description;
    }

    /**
     * Converts the task to a string.
     * @return
     */
    public String toString() {
        return getTaskId()
                + " " + getDescription();
    }

    /**
     * Compares a task with an object.
     * @param o
     * @return
     */
    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof  Task)) return false;
        Task task = (Task) o;
        return Objects.equals(getTaskId(), task.getTaskId())
                && Objects.equals(getDescription(), task.getDescription());
    }

    /**
     * Returns the hashCode of the task.
     * @return
     */
    @Override
    public int hashCode() {
        return Objects.hash(getTaskId(), getDescription());
    }

    /**
     * Executes the task.
     */
    public abstract void execute();
}
