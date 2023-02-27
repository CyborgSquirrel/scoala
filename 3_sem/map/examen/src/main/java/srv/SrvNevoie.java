package srv;

import domain.Nevoie;
import domain.Oras;
import domain.Persoana;
import repo.ItemAlreadyExistsException;
import repo.ItemDoesntExistException;
import repo.RepoNevoie;
import repo.RepoPersoana;

import java.time.LocalDateTime;
import java.util.Arrays;
import java.util.HashSet;
import java.util.Set;

public class SrvNevoie {
    RepoNevoie repoNevoie;
    RepoPersoana repoPersoana;

    Set<OnNevoieModified> onNevoieModifieds = new HashSet<>();

    public SrvNevoie(RepoNevoie repoNevoie, RepoPersoana repoPersoana) {
        this.repoNevoie = repoNevoie;
        this.repoPersoana = repoPersoana;
    }

    public void registerOnNevoieModified(OnNevoieModified onNevoieModified) {
        onNevoieModifieds.add(onNevoieModified);
    }

    public void unregisterOnNevoieModified(OnNevoieModified onNevoieModified) {
        onNevoieModifieds.remove(onNevoieModified);
    }

    private void onNevoieModifiedUpdate() {
        for (OnNevoieModified onNevoieModified : onNevoieModifieds) {
            onNevoieModified.callback();
        }
    }

    public void addNevoie(String titlu, String descriere, LocalDateTime deadline, long omInNevoie) {
        try {
            repoNevoie.store(new Nevoie(
                    0,
                    0,
                    titlu,
                    descriere,
                    deadline,
                    omInNevoie,
                    null,
                    "Caut erou!"
            ));
            onNevoieModifiedUpdate();
        } catch (ItemAlreadyExistsException e) {
            throw new RuntimeException(e);
        }
    }

    public Nevoie[] getApplicableNevoi(Oras oras, long persoanaId) {
        return Arrays.stream(repoNevoie.getAll())
                .filter(nevoie -> {
                    try {
                        return nevoie.getOmInNevoie() != persoanaId && repoPersoana.find(nevoie.getOmInNevoie()).getOras() == oras;
                    } catch (ItemDoesntExistException e) {
                        throw new RuntimeException(e);
                    }
                }).toArray(Nevoie[]::new);
    }

    public Nevoie[] getGoodDeeds(long persoanaId) {
        return Arrays.stream(repoNevoie.getAll())
                .filter(nevoie -> nevoie.getOmSalvator() != null && nevoie.getOmSalvator() == persoanaId)
                .toArray(Nevoie[]::new);
    }

    public void assignNevoie(Nevoie nevoie, long omSalvator) {
        Nevoie nevoie1 = new Nevoie(
                nevoie.getSerialVersionUID(),
                nevoie.getId(),
                nevoie.getTitlu(),
                nevoie.getDescriere(),
                nevoie.getDeadline(),
                nevoie.getOmInNevoie(),
                omSalvator,
                "Erou gasit!"
        );
        try {
            repoNevoie.update(nevoie1);
            onNevoieModifiedUpdate();
        } catch (ItemAlreadyExistsException e) {
            throw new RuntimeException(e);
        }
    }
}
