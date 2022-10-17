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
                "timpul sa faci tema",
                "Profesor",
                "Andrei",
                LocalDateTime.now()
        ));
        tasks.add(new MessageTask(
                "rezervare Dorsia",
                "rezervare la local",
                "hai sa mergem",
                "Paul Allen",
                "Patrick Bateman",
                LocalDateTime.now()
        ));
        tasks.add(new MessageTask(
                "Zilele Clujului",
                "eveniment in Cluj",
                "interesant",
                "Ion",
                "Ana",
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

        if (args.length >= 1) {
            ContainerStrategy containerStrategy = null;
            /*  */ if (args[0].equals("queue")) {
                containerStrategy = ContainerStrategy.QUEUE;
            } else if (args[0].equals("stack")) {
                containerStrategy = ContainerStrategy.STACK;
            }
            if (containerStrategy != null) {
                System.out.println("==========");
                StrategyTaskRunner strategyTaskRunner = new StrategyTaskRunner(containerStrategy);
                for (Task task : tasks) {
                    strategyTaskRunner.addTask(task);
                }
                strategyTaskRunner.executeAll();
            }
        }

        System.out.println("==========");
        StrategyTaskRunner stackTaskRunner = new StrategyTaskRunner(ContainerStrategy.QUEUE);
        for (Task task : tasks) {
            stackTaskRunner.addTask(task);
        }
        stackTaskRunner.executeAll();

        System.out.println("==========");
        StrategyTaskRunner queueTaskRunner = new StrategyTaskRunner(ContainerStrategy.QUEUE);
        for (Task task : tasks) {
            queueTaskRunner.addTask(task);
        }
        queueTaskRunner.executeAll();

        System.out.println("==========");
        DelayTaskRunner delayTaskRunner = new DelayTaskRunner(new StrategyTaskRunner(ContainerStrategy.QUEUE));
        for (Task task : tasks) {
            delayTaskRunner.addTask(task);
        }
        delayTaskRunner.executeAll();

        System.out.println("==========");
        PrinterTaskRunner printerTaskRunner = new PrinterTaskRunner(new StrategyTaskRunner(ContainerStrategy.QUEUE));
        for (Task task : tasks) {
            printerTaskRunner.addTask(task);
        }
        printerTaskRunner.executeAll();
    }
}
