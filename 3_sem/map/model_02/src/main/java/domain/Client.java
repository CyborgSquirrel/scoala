package domain;

import java.sql.ResultSet;
import java.sql.SQLException;

public class Client {
    int id;
    String name;
    int fidelityGrade;
    int age;
    int hobbies;

    public static Client fromResultSet(ResultSet resultSet) {
        int id;
        try {
            id = resultSet.getInt("id");
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        String name;
        try {
            name = resultSet.getString("name");
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        int fidelityGrade;
        try {
            fidelityGrade = resultSet.getInt("fidelityGrade");
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        int age;
        try {
            age = resultSet.getInt("age");
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        int hobbies;
        try {
            hobbies = resultSet.getInt("hobbies");
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        return new Client(id, name, fidelityGrade, age, hobbies);
    }

    public Client(int id, String name, int fidelityGrade, int age, int hobbies) {
        this.id = id;
        this.name = name;
        this.fidelityGrade = fidelityGrade;
        this.age = age;
        this.hobbies = hobbies;
    }

    public int getId() {
        return id;
    }

    public String getName() {
        return name;
    }

    public int getFidelityGrade() {
        return fidelityGrade;
    }

    public int getAge() {
        return age;
    }

    public int getHobbies() {
        return hobbies;
    }
}
