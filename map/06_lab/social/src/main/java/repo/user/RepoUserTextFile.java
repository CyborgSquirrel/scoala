package repo.user;

import domain.User;
import repo.exception.ItemAlreadyExistsException;
import repo.exception.ItemDoesntExistException;
import util.valid.NameValidator;
import util.valid.exception.InvalidNameException;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Scanner;
import java.util.UUID;

public class RepoUserTextFile extends RepoUserInmem {
    private String filePath;

    private void readAllFromFile() {
        users.clear();
        File file = new File(filePath);
        try {
            Scanner scanner = new Scanner(file);
            while (scanner.hasNextLine()) {
                String line = scanner.nextLine();
                String[] items = line.split(",");
                if (items.length != 2) continue;
                UUID id;
                try {
                    id = UUID.fromString(items[0]);
                } catch (IllegalArgumentException e) {
                    continue;
                }
                String name = items[1];
                try {
                    NameValidator nameValidator = new NameValidator();
                    nameValidator.validate(name);
                } catch (InvalidNameException e) {
                    continue;
                }
                User user = new User(id, name);
                users.put(user.getId(), user);
            }
        } catch (FileNotFoundException e) {
            // if there is no file, then there is no data to read
        }
    }

    private void writeAllToFile() {
        try {
            try (FileWriter fileWriter = new FileWriter(filePath)) {
                for (User user : users.values()) {
                    fileWriter.write(user.getId().toString());
                    fileWriter.write(",");
                    fileWriter.write(user.getName());
                    fileWriter.write("\n");
                }
            }
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    public RepoUserTextFile(String filePath) {
        super();
        this.filePath = filePath;
        readAllFromFile();
    }

    @Override
    public void store(User user) throws ItemAlreadyExistsException {
        super.store(user);
        writeAllToFile();
    }

    @Override
    public void update(User user) throws ItemDoesntExistException {
        super.update(user);
        writeAllToFile();
    }

    @Override
    public void erase(UUID id) throws ItemDoesntExistException {
        super.erase(id);
        writeAllToFile();
    }
}
