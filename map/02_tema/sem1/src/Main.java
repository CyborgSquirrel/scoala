import container.ContainerStrategy;
import model.MessageTask;
import model.SortingTask;
import model.Task;
import model.sorter.BubbleSorter;
import model.sorter.MergeSorter;
import task_runner.DelayTaskRunner;
import task_runner.PrinterTaskRunner;
import task_runner.StrategyTaskRunner;

import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;

public class Main {
    static ArrayList<Task> createTasks() {
        BubbleSorter bubbleSorter = new BubbleSorter();
        MergeSorter mergeSorter = new MergeSorter();

        ArrayList<Task> tasks = new ArrayList<>();
        tasks.add(new MessageTask(
                "tema oop",
                "tema interesanta",
                "cv",
                "Gicu",
                "Andrei",
                LocalDateTime.now()
        ));
        tasks.add(new MessageTask(
                "rezervare dorsia",
                "hai",
                "sa mergem",
                "Paul Allen",
                "Patrick Bateman",
                LocalDateTime.now()
        ));
        tasks.add(new MessageTask(
                "Zilele Clujului",
                "evenimentes",
                "interesant",
                "Ion",
                "Antiion",
                LocalDateTime.now()
        ));
        tasks.add(new SortingTask(
                "sort some numbers",
                "slowly, with bubblesort",
                new ArrayList<>(List.of(
                        46, 27, 30, 36, 12, 42, 47, 45, 20, 49
                )),
                bubbleSorter
        ));
        tasks.add(new SortingTask(
                "sort some more numbers",
                "quickly, with mergesort",
                new ArrayList<>(List.of(
                        6, 18, 6, 14, 17, 6, 20, 10, 1, 20, 6, 16, 7, 2, 9, 7, 5, 11, 10, 4
                )),
                mergeSorter
        ));

        return tasks;
    }
    public static void main(String[] args) {
        ArrayList<Task> tasks = createTasks();

        StrategyTaskRunner stackTaskRunner = new StrategyTaskRunner(ContainerStrategy.QUEUE);
        for (Task task : tasks) {
            stackTaskRunner.addTask(task);
        }
        stackTaskRunner.executeAll();

        StrategyTaskRunner queueTaskRunner = new StrategyTaskRunner(ContainerStrategy.QUEUE);
        for (Task task : tasks) {
            queueTaskRunner.addTask(task);
        }
        queueTaskRunner.executeAll();

        DelayTaskRunner delayTaskRunner = new DelayTaskRunner(new StrategyTaskRunner(ContainerStrategy.QUEUE));
        for (Task task : tasks) {
            delayTaskRunner.addTask(task);
        }
        delayTaskRunner.executeAll();

        PrinterTaskRunner printerTaskRunner = new PrinterTaskRunner(new StrategyTaskRunner(ContainerStrategy.QUEUE));
        for (Task task : tasks) {
            printerTaskRunner.addTask(task);
        }
        printerTaskRunner.executeAll();
    }
}
