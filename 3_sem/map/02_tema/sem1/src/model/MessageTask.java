package model;

import utils.Constants;

import java.time.LocalDateTime;

public class MessageTask extends Task {
    String message;
    String from;
    String to;
    LocalDateTime date;

    /**
     * Construct a {@link MessageTask}.
     * @param taskId the taskId
     * @param description the description
     * @param message the message
     * @param from the source
     * @param to the destination
     * @param date the date
     */
    public MessageTask(String taskId, String description, String message, String from, String to, LocalDateTime date) {
        super(taskId, description);
        this.message = message;
        this.from = from;
        this.to = to;
        this.date = date;
    }

    /**
     * Returns the message.
     * @return the message
     */
    public String getMessage() {
        return message;
    }

    /**
     * Sets the message to the provided value.
     * @param message the value to which the message will be set
     */
    public void setMessage(String message) {
        this.message = message;
    }

    /**
     * Returns the source of the message.
     * @return the source
     */
    public String getFrom() {
        return from;
    }

    /**
     * Sets the source of the message.
     * @param from the value to which the source will be set
     */
    public void setFrom(String from) {
        this.from = from;
    }

    /**
     * Returns the destination of the message.
     * @return the destination
     */
    public String getTo() {
        return to;
    }

    /**
     * Sets the destination of the message.
     * @param to the value to which the destination will be set
     */
    public void setTo(String to) {
        this.to = to;
    }

    /**
     * Returns the date of the message.
     * @return
     */
    public LocalDateTime getDate() {
        return date;
    }

    /**
     * Sets the date of the message.
     * @param date
     */
    public void setDate(LocalDateTime date) {
        this.date = date;
    }

    /**
     * Converts the {@link MessageTask} to a string.
     * @return
     */
    @Override
    public String toString() {
        return super.toString()
                + " " + message
                + " " + from
                + " " + to
                + " " + date.format(Constants.DATE_TIME_FORMATTER);
    }

    /**
     * Prints the message.
     */
    @Override
    public void execute() {
        System.out.println(this.toString());
    }
}
