package domain;

public enum HotelType {
    FAMILY, TEENAGERS, OLD_PEOPLE;

    public int getValue() {
        switch (this) {
            case FAMILY -> {
                return 0;
            }
            case TEENAGERS -> {
                return 1;
            }
            case OLD_PEOPLE -> {
                return 2;
            }
        }
        return 0;
    }

    public static HotelType fromValue(int value) {
        switch (value) {
            case 0 -> {
                return FAMILY;
            }
            case 1 -> {
                return TEENAGERS;
            }
            case 2 -> {
                return OLD_PEOPLE;
            }
        }
        return FAMILY;
    }
}
