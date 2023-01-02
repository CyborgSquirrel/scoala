package repo.message;

import domain.Message;
import repo.exception.ItemAlreadyExistsException;
import repo.exception.ItemDoesntExistException;

import java.util.HashMap;
import java.util.UUID;

public class RepoMessageInmem extends RepoMessage {
    protected HashMap<UUID, Message> messages;

    public RepoMessageInmem() {
        this.messages = new HashMap<>();
    }

    @Override
    public void store(Message message) throws ItemAlreadyExistsException {
        if (messages.containsKey(message.getId())) {
            throw new ItemAlreadyExistsException();
        }
        messages.put(message.getId(), message);
    }

    @Override
    public void update(Message message) throws ItemDoesntExistException {
        if (!messages.containsKey(message.getId())) {
            throw new ItemDoesntExistException();
        }
        messages.put(message.getId(), message);
    }

    @Override
    public void erase(UUID id) throws ItemDoesntExistException {
        if (!messages.containsKey(id)) {
            throw new ItemDoesntExistException();
        }
        messages.remove(id);
    }

    @Override
    public Message find(UUID id) throws ItemDoesntExistException {
        if (!messages.containsKey(id)) {
            throw new ItemDoesntExistException();
        }
        return messages.get(id);
    }

    @Override
    public Message[] getAll() {
        return this.messages.values().toArray(new Message[0]);
    }
}
