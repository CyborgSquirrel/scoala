package repo;

import model.Entity;
import model.validator.ValidationException;
import model.validator.Validator;

import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class InMemoryRepo<ID, E extends Entity<ID>> implements Repo<E, ID> {
    private Map<ID, E> entities;
    private Validator<E> validator;
    public InMemoryRepo(Validator<E> validator) {
        entities = new HashMap<>();
        validator = validator;
    }

    @Override
    public E save(E entity) throws ValidationException {
        if (entity == null) {
            throw new IllegalArgumentException("Entity cannot be null");
        }
        if (entities.containsKey(entity.getId())) {
            return entities.get(entity.getId());
        }
        validator.validate(entity);
        entities.put(entity.getId(), entity);
        return entity;
    }

    @Override
    public E delete(ID id) {
        return null;
    }

    @Override
    public List<E> getAll() {
        return entities.values().stream().toList();
    }

    @Override
    public E find(ID id) {
        return null;
    }
}
