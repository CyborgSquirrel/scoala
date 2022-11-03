package tui;

import domain.User;
import service.ServiceUser;
import util.valid.NameValidator;
import util.valid.ValidationStrategy;

import java.util.ArrayList;
import java.util.List;
import java.util.Optional;
import java.util.Scanner;

public class TUI {
    /**
     * @param scanner scanner from which text will be read
     * @param prompt prompt which will be shown before requested input
     * @param parsingStrategy strategy with which input will be parsed
     * @param validationStrategy strategy with which input will be validated
     * @param <T> type which will be parsed and validated
     * @return parsed object
     */
    public static <T> T textPrompt(
            Scanner scanner,
            String prompt,
            ParsingStrategy<T> parsingStrategy,
            ValidationStrategy validationStrategy
    ) {
        System.out.print(prompt + " = ");
        String line = scanner.nextLine();
        T parsed = parsingStrategy.parse(line);
        validationStrategy.validate(parsed);
        return parsed;
    }

    /**
     * @param scanner scanner from which text will be read
     * @param options the options which will be presented to the user
     * @return the index of the option chosen by the user
     */
    public static int optionsPrompt(
            Scanner scanner,
            List<String> options
    ) {
        boolean success = false;
        int option = 0;
        while (!success) {
            for (int i = 0; i < options.size(); ++i) {
                System.out.println(Integer.toString(i + 1) + ". " + options.get(i));
            }
            System.out.print("option = ");
            option = Integer.parseInt(scanner.nextLine())-1;
            if (option < 0 || option > options.size()) {
                System.err.println("That's an invalid option my boy.");
            } else {
                success = true;
            }
        }
        return option;
    }

    /**
     * @param serviceUser user service
     * @param scanner scanner from which text will be read
     * @return the user that was chosen (or nothing)
     */
    public static Optional<User> userByNamePrompt(
            ServiceUser serviceUser,
            Scanner scanner
    ) {
        NameValidator nameValidator = new NameValidator();
        String name = TUI.textPrompt(scanner, "name", line -> line, nameValidator);
        ArrayList<User> usersByName = serviceUser.findUsersByName(name);
        if (usersByName.isEmpty()) {
            System.err.println("No user with that name was found.");
            return Optional.empty();
        } else {
            List<User> topUsersByName = usersByName.subList(0, Math.min(5, usersByName.size()));
            List<String> topUserNames = topUsersByName.stream().map(user -> user.getName()).toList();
            int option = TUI.optionsPrompt(scanner, topUserNames);
            User user = topUsersByName.get(option);
            return Optional.of(user);
        }
    }
}
