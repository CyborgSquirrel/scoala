package repo;

import domain.Friendship;
import repo.exception.ItemAlreadyExistsException;
import repo.exception.ItemDoesntExistException;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Scanner;
import java.util.UUID;

public class RepoFriendshipTextFile extends RepoFriendship {
    private String filePath;

    private void readAllFromFile() {
        friendships.clear();
        File file = new File(filePath);
        try {
            Scanner scanner = new Scanner(file);
            while (scanner.hasNextLine()) {
                String line = scanner.nextLine();
                String[] items = line.split(",");
                if (items.length != 2) continue;
                UUID firstUserId;
                try {
                    firstUserId = UUID.fromString(items[0]);
                } catch (IllegalArgumentException e) {
                    continue;
                }
                UUID secondUserId;
                try {
                    secondUserId = UUID.fromString(items[1]);
                } catch (IllegalArgumentException e) {
                    continue;
                }
                Friendship friendship = new Friendship(firstUserId, secondUserId);
                friendships.add(friendship);
            }
        } catch (FileNotFoundException e) {
            // if there is no file, then there is no data to read
        }
    }

    private void writeAllToFile() {
        try {
            try (FileWriter fileWriter = new FileWriter(filePath)) {
                for (Friendship friendship : friendships) {
                    fileWriter.write(friendship.getFirstUserId().toString());
                    fileWriter.write(",");
                    fileWriter.write(friendship.getSecondUserId().toString());
                    fileWriter.write("\n");
                }
            }
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    public RepoFriendshipTextFile(String filePath) {
        super();
        this.filePath = filePath;
        readAllFromFile();
    }

    @Override
    public void store(Friendship friendship) throws ItemAlreadyExistsException {
        super.store(friendship);
        writeAllToFile();
    }

    @Override
    public void update(Friendship friendship) throws ItemDoesntExistException {
        super.update(friendship);
        writeAllToFile();
    }

    @Override
    public void erase(Friendship friendship) throws ItemDoesntExistException {
        super.erase(friendship);
        writeAllToFile();
    }
}
