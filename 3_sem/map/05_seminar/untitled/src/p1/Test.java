package p1;

import java.util.List;

class Square {
    private double side;

    public double getSide() {
        return side;
    }

    public void setSide(double side) {
        this.side = side;
    }

    public Square(double side) {
        this.side = side;
    }
}

class Circle {
    private double radius;

    public double getRadius() {
        return radius;
    }

    public void setRadius(double radius) {
        this.radius = radius;
    }

    public Circle(double radius) {
        this.radius = radius;
    }
}

public class Test {
    public static <E> void printArie(List<E> l, Area<E> f) {
        l.forEach((a) -> System.out.println(f.compute(a)));
    }
    public static void main(String[] args) {
        Square square1 = new Square(5);
        Square square2 = new Square(3.5);
        Circle circle1 = new Circle(3.2);

        Area<Square> squareArea = (Square a) -> (double) a.getSide() * a.getSide();
        Area<Circle> circleArea = (Circle a) -> (double) Math.PI * Math.pow(a.getRadius(), 2);

        printArie(List.of(square1, square2), squareArea);
        printArie(List.of(circle1), circleArea);
    }
}
