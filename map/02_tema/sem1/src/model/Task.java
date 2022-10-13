package model;

import java.util.Objects;

public abstract class Task {
    String taskId;
    String description;

    public Task(String taskId, String description) {
        this.taskId = taskId;
        this.description = description;
    }

    public String getTaskId() {
        return taskId;
    }

    public void setTaskId(String taskId) {
        this.taskId = taskId;
    }

    public String getDescription() {
        return description;
    }

    public void setDescription(String description) {
        this.description = description;
    }

    public String toString() {
        return getTaskId()
                + " " + getDescription();
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof  Task)) return false;
        Task task = (Task) o;
        return Objects.equals(getTaskId(), task.getTaskId())
                && Objects.equals(getDescription(), task.getDescription());
    }

    @Override
    public int hashCode() {
        return Objects.hash(getTaskId(), getDescription());
    }

    public abstract void execute();
}
