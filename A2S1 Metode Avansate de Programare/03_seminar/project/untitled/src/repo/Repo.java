package repo;

import model.validator.ValidationException;

import java.util.List;

public interface Repo<E, ID> {
    E save(E entity) throws ValidationException;
    E delete(ID id);
    E find(ID id);
    List<E> getAll();
}
