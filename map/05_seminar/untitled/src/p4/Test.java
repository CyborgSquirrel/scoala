package p4;

import javafx.util.Pair;

import java.util.*;
import java.util.function.Predicate;
import java.util.stream.Collectors;

public class Test {
    public static void main(String[] args) {
        List<Student> students = Arrays.asList(
                new Student(0, 221, "Andrei"),
                new Student(1, 212, "Ion"),
                new Student(2, 224, "Marian"),
                new Student(3, 217, "Nicu")
        );

        List<Tema> temas = Arrays.asList(
                new Tema("tema1", "1"),
                new Tema("tema2", "2"),
                new Tema("tema3", "3"),
                new Tema("tema4", "4")
        );

        List<Nota> notas = Arrays.asList(
                new Nota("prof1", students.get(0), temas.get(0), 9.5),
                new Nota("prof1", students.get(1), temas.get(1), 5.75),
                new Nota("prof2", students.get(2), temas.get(2), 8.25),
                new Nota("prof2", students.get(3), temas.get(2), 10),
                new Nota("prof3", students.get(3), temas.get(3), 7.65)
        );

        report1(notas);
        report3(notas, temas.get(2));
        report3(notas, temas.get(3));
        report4(notas);
        report5(notas);
    }
    // 1. toate notele acordate de un anumit profesor, la o anumita grupa
    private static void report1(List<Nota> notas) {
        Predicate<Nota> byProfessor = a -> a.getProfessor().equals("prof1");
        Predicate<Nota> byGroup = a -> a.getStudent().getGroup() == 212;
        Predicate<Nota> filter = byGroup.and(byProfessor);
        notas.stream().filter(filter).forEach(a -> System.out.println(a));
    }
    // 2. media notelor pt fiecare student (Collectors.groupingBy)
//    private static void report2(List<Nota> notas) {
//        notas.stream()
//                .collect(Collectors.groupingBy(a -> a.getStudent()))
//                .entrySet()
//                .stream().mapToDouble(a -> {
//                    int size = a.getValue().size();
//                    return a.getValue().stream()
//                            .reduce(0, (b,c) -> b.getValue()+c.getValue()) / (float) size;
//                });
//    }
    // 3. media notelor la o anumita tema
    private static void report3(List<Nota> notas, Tema tema) {
        OptionalDouble average = notas.stream()
                .filter(a -> a.getTema() == tema)
                .mapToDouble(a -> a.getValue())
                .average();
        System.out.println(average.getAsDouble());
    }
    // 4. tema cu cea mai mare medie
    private static void report4(List<Nota> notas) {
        Pair<Tema, Double> max = notas.stream()
                .collect(Collectors.groupingBy(a -> a.getTema()))
                .entrySet()
                .stream().map(a -> {
                    double average = a.getValue().stream()
                            .mapToDouble(b -> b.getValue())
                            .average().getAsDouble();
                    return new Pair<>(a.getKey(), average);
                })
                .max(Comparator.comparingDouble(a -> a.getValue()))
                .get();
        System.out.println(max);
    }
    // 5. tema cea mai grea (media notelor cea mai mica)
    private static void report5(List<Nota> notas) {
        Pair<Tema, Double> min = notas.stream()
                .collect(Collectors.groupingBy(a -> a.getTema()))
                .entrySet()
                .stream().map(a -> {
                    double average = a.getValue().stream()
                            .mapToDouble(b -> b.getValue())
                            .average().getAsDouble();
                    return new Pair<>(a.getKey(), average);
                })
                .min(Comparator.comparingDouble(a -> a.getValue()))
                .get();
        System.out.println(min);
    }
}
