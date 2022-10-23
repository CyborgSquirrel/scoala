package domain;

import java.util.Date;
import java.util.HashSet;
import java.util.Objects;

public class User {
    private int id;
    private String name;

    /**
     * Creates a string representation of the user.
     * @return a string representation of the user
     */
    @Override
    public String toString() {
        return "User{" +
                "name='" + name + '\'' +
                '}';
    }

    /**
     * Creates a new {@link User}.
     * @param id the user's id
     * @param name the user's name
     */
    public User(int id, String name) {
        this.id = id;
        this.name = name;
    }

    /**
     * Checks whether caller and o are equal.
     * @param o the object which will be compared with the caller
     * @return whether caller and o are equal
     */
    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        User user = (User) o;
        return id == user.id;
    }

    /**
     * Returns the object's hash code.
     * @return the object's hash code
     */
    @Override
    public int hashCode() {
        return Objects.hash(id);
    }

    /**
     * Returns the user's id.
     * @return the user's id
     */
    public int getId() {
        return id;
    }
}
