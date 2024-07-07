package service;

import domain.Message;
import repo.exception.ItemAlreadyExistsException;
import repo.message.RepoMessage;
import repo.user.RepoUser;

import java.time.LocalDateTime;
import java.util.UUID;

public class ServiceMessage {
    RepoUser repoUser;
    RepoMessage repoMessage;

    public ServiceMessage(RepoUser repoUser, RepoMessage repoMessage) {
        this.repoUser = repoUser;
        this.repoMessage = repoMessage;
    }

    public void send(UUID sourceUserId, UUID destinationUserId, String text) {
        try {
            repoMessage.store(new Message(UUID.randomUUID(), sourceUserId, destinationUserId, text, LocalDateTime.now()));
        } catch (ItemAlreadyExistsException e) {
            throw new RuntimeException(e);
        }
    }

    public Message[] getAll() {
        return repoMessage.getAll();
    }
}
