package srv;

import domain.Ticket;
import repo.ItemAlreadyExistsException;
import repo.RepoTicket;

import java.time.LocalDateTime;
import java.util.*;

public class SrvTicket {
    RepoTicket repoTicket;
    Set<OnTicketsModified> onTicketsModifiedSet;

    public SrvTicket(RepoTicket repoTicket) {
        this.repoTicket = repoTicket;
        this.onTicketsModifiedSet = new HashSet<>();
    }

    public void purchaseTicket(String username, long flightId) throws ItemAlreadyExistsException {
        repoTicket.store(new Ticket(username, flightId, LocalDateTime.now()));
        onTicketsModified();
    }

    public void registerOnTicketsModified(OnTicketsModified onTicketsModified) {
        onTicketsModifiedSet.add(onTicketsModified);
    }

    public void unregisterOnTicketsModified(OnTicketsModified onTicketsModified) {
        onTicketsModifiedSet.remove(onTicketsModified);
    }

    void onTicketsModified() {
        for (OnTicketsModified onTicketsModified : onTicketsModifiedSet) {
            onTicketsModified.callback();
        }
    }

    public int getRemainingSeats(long flightId) {
        return (int) Arrays.stream(repoTicket.getAll())
                .filter(ticket -> ticket.getFlightId() == flightId)
                .count();
    }
}
