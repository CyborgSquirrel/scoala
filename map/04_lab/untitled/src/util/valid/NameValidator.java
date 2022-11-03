package util.valid;

import util.valid.exception.InvalidNameException;

public class NameValidator implements ValidationStrategy<String> {
    @Override
    public void validate(String name) {
        if (name.strip() == "") {
            throw new InvalidNameException();
        }
        for (char c : name.toCharArray()) {
            if (!Character.isAlphabetic(c)) {
                throw new InvalidNameException();
            }
        }
    }
}
