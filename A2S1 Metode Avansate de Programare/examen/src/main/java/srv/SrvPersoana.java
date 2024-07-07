package srv;

import domain.Oras;
import domain.Persoana;
import repo.ItemAlreadyExistsException;
import repo.ItemDoesntExistException;
import repo.RepoPersoana;

import java.nio.file.attribute.UserPrincipal;
import java.util.Arrays;
import java.util.Set;
import java.util.stream.Collectors;

public class SrvPersoana {
    RepoPersoana repoPersoana;

    public SrvPersoana(RepoPersoana repoPersoana) {
        this.repoPersoana = repoPersoana;
    }

    public void register(String nume, String prenume, String username, String parola, Oras oras, String strada, String numarStrada, String telefon) {
        try {
            repoPersoana.store(new Persoana(0, 0, nume, prenume, username, parola, oras, strada, numarStrada, telefon));
        } catch (ItemAlreadyExistsException e) {
            throw new RuntimeException(e);
        }
    }

    public Persoana[] getPersoane() {
        return repoPersoana.getAll();
    }

    public Persoana findPersoana(long id) {
        try {
            return repoPersoana.find(id);
        } catch (ItemDoesntExistException e) {
            throw new RuntimeException(e);
        }
    }
}
