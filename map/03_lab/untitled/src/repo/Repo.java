package repo;

import repo.exception.ItemAlreadyExistsException;
import repo.exception.ItemDoesntExistException;

import java.util.ArrayList;

/**
 * Generic interface for repos.
 * @param <T> the object stored in the repo
 * @param <I> the object which may be used as an index
 */
public interface Repo<T, I> {
    /**
     * Stores t in the repo.
     * @param t the object which will be stored
     * @throws ItemAlreadyExistsException if the object already exists
     */
    void store(T t) throws ItemAlreadyExistsException;

    /**
     * Updates t in the repo.
     * @param t the object that will be updated
     * @throws ItemDoesntExistException if an object with t's id doesn't already exist
     */
    void update(T t) throws ItemDoesntExistException;

    /**
     * Erases object with provided id from the repo.
     * @param id the id of the object that will be erased
     * @throws ItemDoesntExistException if there is no object with provided id in repo
     */
    void erase(I id) throws ItemDoesntExistException;

    /**
     * Returns the object which has the provided id.
     * @param id the id of the object which will be returned
     * @return the object with the provided id
     * @throws ItemDoesntExistException if an object with the provided id doesn't exist
     */
    T find(I id) throws ItemDoesntExistException;

    /**
     * Returns an array of all the objects in repo.
     * @return an array of all the objects in repo
     */
    T[] getAll();
}
