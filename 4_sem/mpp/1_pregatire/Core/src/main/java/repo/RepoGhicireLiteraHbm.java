package repo;

import domain.GhicireLitera;
import domain.GhicireLiteraId;
import org.hibernate.Session;
import org.hibernate.SessionFactory;
import org.hibernate.query.Query;

import java.util.List;

public class RepoGhicireLiteraHbm implements RepoGhicireLitera {
    SessionFactory sessionFactory;

    public RepoGhicireLiteraHbm(SessionFactory sessionFactory) {
        this.sessionFactory = sessionFactory;
    }

    @Override
    public GhicireLitera find(GhicireLiteraId ghicireLiteraId) throws IdNotFoundException {
        return null;
    }

    @Override
    public void store(GhicireLitera ghicireLitera) throws IdAlreadyExistsException {
        try (Session session = sessionFactory.openSession()) {
            session.beginTransaction();
            session.persist(ghicireLitera);
            session.getTransaction().commit();
        }
    }

    @Override
    public void update(GhicireLiteraId ghicireLiteraId, GhicireLitera ghicireLitera) throws IdNotFoundException {

    }

    @Override
    public void remove(GhicireLiteraId ghicireLiteraId) throws IdNotFoundException {

    }

    @Override
    public GhicireLitera[] getAll() {
        return new GhicireLitera[0];
    }

    @Override
    public GhicireLitera[] findByJocIdAndRunda(int jocId, int runda) {
        List<GhicireLitera> resultList;
        try (Session session = sessionFactory.openSession()) {
            resultList = session.createQuery("FROM GhicireLitera WHERE id.jocId = ? AND id.runda = ?")
                    .setParameter(0, jocId)
                    .setParameter(1, runda)
                    .getResultList();
        }
        return resultList.toArray(new GhicireLitera[0]);
    }

    @Override
    public GhicireLitera[] findByJocIdAndGhicitorJucatorId(int jocId, int ghicitorJucatorId) {
        List<GhicireLitera> resultList;
        try (Session session = sessionFactory.openSession()) {
            resultList = session.createQuery("FROM GhicireLitera WHERE id.jocId = ? AND id.ghicitorJucatorId = ?")
                    .setParameter(0, jocId)
                    .setParameter(1, ghicitorJucatorId)
                    .getResultList();
        }
        return resultList.toArray(new GhicireLitera[0]);
    }
}
