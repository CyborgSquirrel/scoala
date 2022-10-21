import domain.Student;
import myMap.MyMap;

import java.util.*;

public class Main {
    public static List<Student> getList(){
        List<Student> l=new ArrayList<Student>();
        l.add(new Student("1",9.7f));
        l.add(new Student("2",7.3f));
        l.add(new Student("3",6f));
        l.add(new Student("4",6.9f));
        l.add(new Student("5",9.5f));
        l.add(new Student("6",9.9f));
        return l;
    }
    public static void main(String[] args) {
        Student s1 = new Student("Dan", 4.5f);
        Student s2 = new Student("Ana", 8.5f);
        Student s3 = new Student("Dan", 4.5f);
        Student s4 = new Student("Nicu", 9.25f);
        Student s5 = new Student("Gicu", 3.17f);

        // HASH SET
        HashSet<Student> hashSet = new HashSet<>();
        hashSet.add(s1);
        hashSet.add(s2);
        hashSet.add(s3);
        System.out.println("");
        System.out.println("HashSet");
        System.out.println(hashSet.toString());

        // TREE SET
        TreeSet<Student> treeSet = new TreeSet<>(
                Comparator.comparing(Student::getName)
                        .thenComparing(Student::getAverage)
        );
        treeSet.add(s1);
        treeSet.add(s2);
        treeSet.add(s3);
        treeSet.add(s4);
        treeSet.add(s5);
        System.out.println("");
        System.out.println("TreeSet");
        System.out.println(treeSet.toString());

        // HASH MAP
        HashMap<String, Student> hashMap = new HashMap<>();
        hashMap.put("s1", s1);
        hashMap.put("s2", s2);
        hashMap.put("s3", s3);
        hashMap.put("s4", s4);
        hashMap.put("s5", s5);
        System.out.println("");
        System.out.println("HashMap");
        System.out.println(hashMap.toString());

        // TREE MAP
        TreeMap<String, Student> treeMap = new TreeMap<>();
        treeMap.put("s1", s1);
        treeMap.put("s2", s2);
        treeMap.put("s3", s3);
        treeMap.put("s4", s4);
        treeMap.put("s5", s5);
        System.out.println("");
        System.out.println("TreeMap");
        System.out.println(treeMap.toString());

        // MY MAP
        MyMap myMap = new MyMap();
        myMap.add(s1);
        myMap.add(s2);
        myMap.add(s3);
        myMap.add(s4);
        myMap.add(s5);
        System.out.println("");
        System.out.println("MyMap");
        System.out.println(myMap.toString());
        System.out.println(myMap.getEntries());

        List<Student> list = getList();
        for (Student student : list) {
            myMap.add(student);
        }

        for (Map.Entry<Integer, ArrayList<Student>> entry : myMap.getEntries()) {
            Collections.sort(
                    entry.getValue(),
                    Comparator.comparing(Student::getName)
            );
        }
        System.out.println(myMap);
    }
}
