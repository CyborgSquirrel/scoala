package domain;

public enum Oras {
    BRASOV,
    NEW_YORK,
    CLUJ_NAPOCA,
    BUCURESTI,
    LONDON;

    public String toValue() {
        switch (this) {
            case BRASOV -> {
                return "Brasov";
            }
            case NEW_YORK -> {
                return "New York";
            }
            case CLUJ_NAPOCA -> {
                return "Cluj Napoca";
            }
            case BUCURESTI -> {
                return "Bucuresti";
            }
            case LONDON -> {
                return "London";
            }
        }
        return "Brasov";
    }

    public static Oras fromValue(String value) {
        switch (value) {
            case "Brasov" -> {
                return BRASOV;
            }
            case "New York" -> {
                return NEW_YORK;
            }
            case "Cluj Napoca" -> {
                return CLUJ_NAPOCA;
            }
            case "Bucuresti" -> {
                return BUCURESTI;
            }
            case "London" -> {
                return LONDON;
            }
        }
        return BRASOV;
    }
}
