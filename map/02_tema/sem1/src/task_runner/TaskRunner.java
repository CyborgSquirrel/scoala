package task_runner;

import model.Task;

public interface TaskRunner {
    /**
     * executa un task din colecţia de task-uri de executat
      */
    void executeOneTask();
    /**
     * executǎ toate task-urile din colecţia de task-uri.
     */
    void executeAll();
    /**
     * adaugǎ un task în colecţia de task-uri de executat
     */
    void addTask(Task t);
    /**
     * verifica daca mai sunt task-ri de executat
     */
    boolean hasTask();
}
