package tui;

@FunctionalInterface
public interface ParsingStrategy<T> {
    /**
     * @param line the line of text that will be parsed
     * @return the parsed object
     */
    T parse(String line);
}
