package domain;

import java.util.Objects;
import java.util.UUID;

public class User {
    private UUID id;
    private String name;

    /**
     * @return a string representation of the user
     */
    @Override
    public String toString() {
        return "User{" +
                "name='" + name + '\'' +
                '}';
    }

    /**
     * @param id the user's id
     * @param name the user's name
     */
    public User(UUID id, String name) {
        this.id = id;
        this.name = name;
    }

    /**
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
     * @return the object's hash code
     */
    @Override
    public int hashCode() {
        return Objects.hash(id);
    }

    /**
     * @return the user's id
     */
    public UUID getId() {
        return id;
    }

    /**
     * @return the user's name
     */
    public String getName() {
        return name;
    }
}
