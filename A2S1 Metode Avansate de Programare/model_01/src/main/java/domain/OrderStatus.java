package domain;

public enum OrderStatus {
    PLACED, PREPARING, SERVED;

    public int getValue() {
        switch (this) {
            case PLACED -> {
                return 0;
            }
            case PREPARING -> {
                return 1;
            }
            case SERVED -> {
                return 2;
            }
        }
        return 0;
    }

    public static OrderStatus fromValue(int value) {
        switch (value) {
            case 0 -> {
                return PLACED;
            }
            case 1 -> {
                return PREPARING;
            }
            case 2 -> {
                return SERVED;
            }
        }
        return PLACED;
    }
}
