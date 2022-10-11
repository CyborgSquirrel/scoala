import java.util.ArrayList;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.println("Hello world!");

        String scannedString = scanner.nextLine();
        int scannedInt = scanner.nextInt();
        float scannedFloat = scanner.nextFloat();

        System.out.println(scannedString);
        System.out.println(scannedInt);
        System.out.println(scannedFloat);

        ArrayList<Integer> list = new ArrayList<>();
        list.add(66);
        list.add(100);
        list.add(28);
        list.add(21);
        list.add(40);
        list.add(5);
        list.add(99);
        list.add(43);
        list.add(25);

        int largestNumber = list.get(0);
        int smallestNumber = list.get(0);
        for (int i = 1; i < list.size(); i++) {
            largestNumber = Integer.max(largestNumber, list.get(i));
            smallestNumber = Integer.min(smallestNumber, list.get(i));
        }
        System.out.println(largestNumber);
        System.out.println(smallestNumber);

        Cube cube = new Cube(12.5f);
        System.out.println(cube.area());

        Employee employee_1 = new Employee("John Doe", 24, 1000, "coder");
        Employee employee_2 = new Employee("Vinny", 33, 12000, "manager");

        System.out.println("Employee 1");
        System.out.println(employee_1.toString());
        System.out.println("Employee 2");
        System.out.println(employee_2.toString());
    }
}
