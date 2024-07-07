package repo;

import domain.Jucator;

public interface RepoJucator extends Repo<Integer, Jucator> {
    Jucator findByNume(String name);
}
