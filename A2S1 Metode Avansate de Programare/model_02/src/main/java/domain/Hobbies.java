package domain;

public enum Hobbies {
    READING, MUSIC, HIKING, WALKING, EXTREME_SPORTS;

    public int getValue() {
        switch (this) {
            case READING -> {
                return 0b00000001;
            }
            case MUSIC -> {
                return 0b00000010;
            }
            case HIKING -> {
                return 0b00000100;
            }
            case WALKING -> {
                return 0b00001000;
            }
            case EXTREME_SPORTS -> {
                return 0b00010000;
            }
        }
        return 0;
    }

}
