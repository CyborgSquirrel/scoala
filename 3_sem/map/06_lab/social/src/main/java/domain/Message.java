package domain;

import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.UUID;

public class Message {
    public static final DateTimeFormatter DATE_TIME_FORMATTER = DateTimeFormatter.ofPattern("yyyy-MM-dd kk:mm");

    public String getText() {
        return text;
    }

    public LocalDateTime getTimestamp() {
        return timestamp;
    }

    private UUID id;

    public UUID getId() {
        return id;
    }

    public UUID getSourceUserId() {
        return sourceUserId;
    }

    public UUID getDestinationUserId() {
        return destinationUserId;
    }

    private UUID sourceUserId;
    private UUID destinationUserId;
    private LocalDateTime timestamp;
    private String text;

    public Message(UUID id, UUID sourceUserId, UUID destinationUserId, String text, LocalDateTime timestamp) {
        this.id = id;
        this.sourceUserId = sourceUserId;
        this.destinationUserId = destinationUserId;
        this.text = text;
        this.timestamp = timestamp;
    }
}
