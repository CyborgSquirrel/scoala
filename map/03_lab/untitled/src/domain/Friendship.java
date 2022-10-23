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

    /**
     * Creates a new {@link Friendship}.
     * @param firstUserId the id of the first user taking part in the friendship
     * @param secondUserId the id of the second user taking part in the friendship
     */
    public Friendship(int firstUserId, int secondUserId) {
        this.firstUserId = firstUserId;
        this.secondUserId = secondUserId;
    }

    /**
     * Gets the first user's id.
     * @return the first user's id
     */
    public int getFirstUserId() {
        return firstUserId;
    }

    /**
     * Gets the second user's id.
     * @return the second user's id
     */
    public int getSecondUserId() {
        return secondUserId;
    }
}
