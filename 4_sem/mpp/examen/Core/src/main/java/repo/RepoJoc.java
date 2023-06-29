package repo;

import domain.Joc;

public interface RepoJoc extends Repo<Integer, Joc> {
    Joc[] getByJucatorId(int jucatorId);
}
