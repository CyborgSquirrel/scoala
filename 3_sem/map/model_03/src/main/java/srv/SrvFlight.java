package srv;

import domain.Flight;
import repo.RepoFlight;

import java.time.LocalDate;
import java.time.LocalDateTime;
import java.util.Arrays;
import java.util.Objects;
import java.util.Set;
import java.util.stream.Collectors;

public class SrvFlight {
    RepoFlight repoFlight;

    public SrvFlight(RepoFlight repoFlight) {
        this.repoFlight = repoFlight;
    }

    public Set<String> getFromSet() {
        return Arrays.stream(repoFlight.getAll())
                .map(flight -> flight.getFrom())
                .collect(Collectors.toSet());
    }

    public Set<String> getToSet() {
        return Arrays.stream(repoFlight.getAll())
                .map(flight -> flight.getTo())
                .collect(Collectors.toSet());
    }

    public Flight[] getFlightsFromToWithDepartureDate(String from, String to, LocalDate departureDate) {
        return Arrays.stream(repoFlight.getAll())
                .filter(flight -> Objects.equals(flight.getFrom(), from)
                && Objects.equals(flight.getTo(), to)
                && Objects.equals(flight.getDepartureTime().toLocalDate(), departureDate))
                .toArray(Flight[]::new);
    }
}
