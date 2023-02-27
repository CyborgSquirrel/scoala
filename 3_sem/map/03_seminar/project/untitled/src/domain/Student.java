package domain;

import model.Entity;
import repo.HasId;

import java.util.Objects;

public class Student extends Entity<Long> implements Comparable<Student> {
    private String name;
    private float average;

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public float getAverage() {
        return average;
    }

    public void setAverage(float average) {
        this.average = average;
    }

    public Student(String name, float average) {
        this.name = name;
        this.average = average;
    }

    @Override
    public String toString() {
        return "domain.Student{" +
                "name='" + name + '\'' +
                ", average=" + average +
                '}';
    }

    @Override
    public int hashCode() {
        return Objects.hash(getAverage(), getName());
    }

    @Override
    public boolean equals(Object o) {
        // Verifica daca e acelasi obiect in memorie.
        if (this == o) return true;

        // Se asigura ca obiectul nu este null, si ca cele doua obiecte au aceeasi clasa.
        if (o == null || getClass() != o.getClass()) return false;

        // Obiectul este convertit in Student.
        Student student = (Student) o;

        // Compara campurile celor doua obiecte.
        return Float.compare(student.average, average) == 0 && Objects.equals(name, student.name);
    }

    @Override
    public int compareTo(Student o) {
        return name.compareTo(o.name);
    }
}
