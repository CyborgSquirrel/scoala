package repo;

import domain.Entity;

public interface Repo<ID, E extends Entity<ID>> {
    E find(ID id) throws IdNotFoundException;
    void store(E e) throws IdAlreadyExistsException;
    void update(ID id, E e) throws IdNotFoundException;
    void remove(ID id) throws IdNotFoundException;
    E[] getAll();
}
