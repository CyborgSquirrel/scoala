package repo;

import domain.Friendship;
import domain.FriendshipId;
import repo.exception.ItemAlreadyExistsException;
import repo.exception.ItemDoesntExistException;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.time.LocalDateTime;
import java.time.format.DateTimeParseException;
import java.time.temporal.TemporalQueries;
import java.util.Scanner;
import java.util.UUID;

public class RepoFriendshipTextFile extends RepoFriendshipInmem {
    private String filePath;

    private void readAllFromFile() {
        friendships.clear();
        File file = new File(filePath);
        try {
            Scanner scanner = new Scanner(file);
            while (scanner.hasNextLine()) {
                String line = scanner.nextLine();
                String[] items = line.split(",");
                UUID firstUserId;
                try {
                    firstUserId = UUID.fromString(items[0]);
                } catch (ArrayIndexOutOfBoundsException|IllegalArgumentException e) {
                    continue;
                }
                UUID secondUserId;
                try {
                    secondUserId = UUID.fromString(items[1]);
                } catch (ArrayIndexOutOfBoundsException|IllegalArgumentException e) {
                    continue;
                }
                LocalDateTime friendsSince;
                try {
                    friendsSince = Friendship.DATE_TIME_FORMATTER.parse(items[2], TemporalQueries.localDate()).atStartOfDay();
                } catch (ArrayIndexOutOfBoundsException|DateTimeParseException e) {
                    continue;
                }
                Friendship friendship = new Friendship(new FriendshipId(firstUserId, secondUserId), friendsSince);
                friendships.put(friendship.getId(), friendship);
            }
        } catch (FileNotFoundException e) {
            // if there is no file, then there is no data to read
        }
    }

    private void writeAllToFile() {
        try {
            try (FileWriter fileWriter = new FileWriter(filePath)) {
                for (Friendship friendship : friendships.values()) {
                    fileWriter.write(friendship.getId().getFirstUserId().toString());
                    fileWriter.write(",");
                    fileWriter.write(friendship.getId().getSecondUserId().toString());
                    fileWriter.write(",");
                    fileWriter.write(friendship.getFriendsSince().format(Friendship.DATE_TIME_FORMATTER));
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
    public void erase(FriendshipId friendshipId) throws ItemDoesntExistException {
        super.erase(friendshipId);
        writeAllToFile();
    }
}
