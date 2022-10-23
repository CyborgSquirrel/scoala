package util.valid;

import util.valid.exception.InvalidNameException;

public class NameValidator implements ValidationStrategy {
    @Override
    public void validate(String input) {
        if (input == "") {
            throw new InvalidNameException();
        }
    }
}
