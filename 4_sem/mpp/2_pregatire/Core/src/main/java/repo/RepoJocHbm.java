package repo;

import domain.Joc;
import org.hibernate.Session;
import org.hibernate.SessionFactory;

public class RepoJocHbm implements RepoJoc {
    SessionFactory sessionFactory;

    public RepoJocHbm(SessionFactory sessionFactory) {
        this.sessionFactory = sessionFactory;
    }

    @Override
    public Joc find(Integer id) throws IdNotFoundException {
        Joc entity;
        try (Session session = sessionFactory.openSession()) {
            entity = session.createQuery("FROM Joc WHERE id = ?", Joc.class)
                    .setParameter(0, id)
                    .getSingleResult();
        }
        return entity;
    }

    @Override
    public void store(Joc joc) throws IdAlreadyExistsException {
        try (Session session = sessionFactory.openSession()) {
            session.beginTransaction();
            session.persist(joc);
            session.getTransaction().commit();
        }
    }

    @Override
    public void update(Integer id, Joc joc) throws IdNotFoundException {
        try (Session session = sessionFactory.openSession()) {
            session.beginTransaction();
            joc.setId(id);
            session.update(joc);
            session.getTransaction().commit();
        }
    }

    @Override
    public void remove(Integer integer) throws IdNotFoundException {
        assert false;
    }

    @Override
    public Joc[] getAll() {
        Joc[] entities;
        try (Session session = sessionFactory.openSession()) {
            entities = session.createQuery("FROM Joc", Joc.class)
                    .getResultList()
                    .toArray(new Joc[0]);
        }
        return entities;
    }
}
