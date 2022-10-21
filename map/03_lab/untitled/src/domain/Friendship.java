package domain;

import java.util.Objects;

public class Friendship {
    private int firstUserId;
    private int secondUserId;

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Friendship that = (Friendship) o;
        return firstUserId == that.firstUserId && secondUserId == that.secondUserId;
    }

    @Override
    public int hashCode() {
        return Objects.hash(firstUserId, secondUserId);
    }

    public Friendship(int firstUserId, int secondUserId) {
        this.firstUserId = firstUserId;
        this.secondUserId = secondUserId;
    }

    public int getFirstUserId() {
        return firstUserId;
    }

    public int getSecondUserId() {
        return secondUserId;
    }
}
