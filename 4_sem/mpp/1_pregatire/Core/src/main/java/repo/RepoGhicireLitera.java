package repo;

import domain.GhicireLitera;
import domain.GhicireLiteraId;

public interface RepoGhicireLitera extends Repo<GhicireLiteraId, GhicireLitera> {
    GhicireLitera[] findByJocIdAndRunda(int jocId, int runda);
    GhicireLitera[] findByJocIdAndGhicitorJucatorId(int jocId, int ghicitorJucatorId);
}
