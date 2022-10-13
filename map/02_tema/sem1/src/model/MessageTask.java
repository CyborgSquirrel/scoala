package model;

import model.Task;
import utils.Constants;

import java.time.LocalDateTime;

public class MessageTask extends Task {
    String message;
    String from;
    String to;
    LocalDateTime date;

    public MessageTask(String taskId, String description, String message, String from, String to, LocalDateTime date) {
        super(taskId, description);
        this.message = message;
        this.from = from;
        this.to = to;
        this.date = date;
    }

    public String getMessage() {
        return message;
    }

    public void setMessage(String message) {
        this.message = message;
    }

    public String getFrom() {
        return from;
    }

    public void setFrom(String from) {
        this.from = from;
    }

    public String getTo() {
        return to;
    }

    public void setTo(String to) {
        this.to = to;
    }

    public LocalDateTime getDate() {
        return date;
    }

    public void setDate(LocalDateTime date) {
        this.date = date;
    }

    @Override
    public String toString() {
        return super.toString()
                + " " + message
                + " " + from
                + " " + to
                + " " + date.format(Constants.DATE_TIME_FORMATTER);
    }

    @Override
    public void execute() {
        System.out.println(this.toString());
    }
}
