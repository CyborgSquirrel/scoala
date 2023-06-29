package repo;

import domain.Joc;
import domain.Pozitie;
import org.hibernate.Session;
import org.hibernate.SessionFactory;

public class RepoPozitieHbm implements RepoPozitie {
    SessionFactory sessionFactory;

    public RepoPozitieHbm(SessionFactory sessionFactory) {
        this.sessionFactory = sessionFactory;
    }

    @Override
    public Pozitie find(Integer id) throws IdNotFoundException {
        Pozitie entity;
        try (Session session = sessionFactory.openSession()) {
            entity = session.createQuery("FROM Pozitie WHERE id = ?", Pozitie.class)
                    .setParameter(0, id)
                    .getSingleResult();
        }
        return entity;
    }

    @Override
    public void store(Pozitie entity) throws IdAlreadyExistsException {
        try (Session session = sessionFactory.openSession()) {
            session.beginTransaction();
            session.persist(entity);
            session.getTransaction().commit();
        }
    }

    @Override
    public void update(Integer id, Pozitie entity) throws IdNotFoundException {
        try (Session session = sessionFactory.openSession()) {
            session.beginTransaction();
            entity.setId(id);
            session.update(entity);
            session.getTransaction().commit();
        }
    }

    @Override
    public void remove(Integer integer) throws IdNotFoundException {
        assert false;
    }

    @Override
    public Pozitie[] getAll() {
        Pozitie[] entities;
        try (Session session = sessionFactory.openSession()) {
            entities = session.createQuery("FROM Pozitie", Pozitie.class)
                    .getResultList()
                    .toArray(new Pozitie[0]);
        }
        return entities;
    }

    @Override
    public Pozitie[] getByJocId(int jocId) {
        Pozitie[] entities;
        try (Session session = sessionFactory.openSession()) {
            entities = session.createQuery("FROM Pozitie WHERE jocId = ?", Pozitie.class)
                    .setParameter(0, jocId)
                    .getResultList()
                    .toArray(new Pozitie[0]);
        }
        return entities;
    }
}
