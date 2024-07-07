package repo;

import domain.Pozitie;

public interface RepoPozitie extends Repo<Integer, Pozitie> {
    Pozitie[] getByJocId(int jocId);
}
