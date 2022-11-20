package util.valid;

public interface ValidationStrategy<T> {
    /**
     * @param input input to be validated
     */
    void validate(T input);
}
