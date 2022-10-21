package myMap;

import domain.Student;

import java.util.*;

public class MyMap {
    private Map<Integer, ArrayList<Student>> map;

    @Override
    public String toString() {
        return "MyMap{" +
                "map=" + map +
                '}';
    }

    public MyMap() {
        this.map = new TreeMap<>();
    }
    public void add(Student student) {
        int roundedAverage = Math.round(student.getAverage());
        ArrayList<Student> students;
        if (map.containsKey(roundedAverage)) {
            students = map.get(roundedAverage);
        } else {
            students = new ArrayList<>();
            map.put(roundedAverage, students);
        }
        students.add(student);
    }
    public Set<Map.Entry<Integer, ArrayList<Student>>> getEntries() {
        return map.entrySet();
    }

}
