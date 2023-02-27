import model.MessageTask;
import model.SortingTask;
import model.sorter.BubbleSorter;
import model.sorter.MergeSorter;

import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;

public class TestRunner {
    static ArrayList<MessageTask> createMessages() {
        ArrayList<MessageTask> messages = new ArrayList<>();
        messages.add(new MessageTask(
            "tema oop",
            "tema interesanta",
            "cv",
            "Gicu",
            "Andrei",
            LocalDateTime.now()
        ));
        messages.add(new MessageTask(
            "rezervare dorsia",
            "hai",
            "sa mergem",
            "Paul Allen",
            "Patrick Bateman",
            LocalDateTime.now()
        ));
        messages.add(new MessageTask(
            "Zilele Clujului",
            "evenimentes",
            "interesant",
            "Ion",
            "Antiion",
            LocalDateTime.now()
        ));
        return messages;
    }

    static void testMessageTask() {
        ArrayList<MessageTask> tasks = createMessages();
        for (MessageTask task : tasks) {
            task.execute();
        }
    }

    static void testSortingTask() {
        BubbleSorter bubbleSorter = new BubbleSorter();
        MergeSorter mergeSorter = new MergeSorter();

        ArrayList<SortingTask> tasks = new ArrayList<>();
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

        for (SortingTask task : tasks) {
            task.execute();
        }
    }

    public static void run() {
        testMessageTask();
        testSortingTask();
    }
}
