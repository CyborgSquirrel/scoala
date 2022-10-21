package repo;

import repo.exception.ItemAlreadyExistsException;
import repo.exception.ItemDoesntExistException;

import java.util.ArrayList;

public interface Repo<T, I> {
    void store(T t) throws ItemAlreadyExistsException;
    void update(T t) throws ItemDoesntExistException;
    void erase(I id) throws ItemDoesntExistException;
    T find(I id) throws ItemDoesntExistException;
    T[] getAll();
}
