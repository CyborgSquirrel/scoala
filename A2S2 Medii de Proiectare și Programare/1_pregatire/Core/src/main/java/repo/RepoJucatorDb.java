package repo;

import domain.Jucator;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;

public class RepoJucatorDb implements RepoJucator {
    private static final Logger logger = LogManager.getLogger();

    String url;

    public RepoJucatorDb(String url) {
        this.url = url;
    }

    private static Jucator readEntityFromResultSet(ResultSet resultSet) throws SQLException {
        int id = resultSet.getInt("id");
        String nume = resultSet.getString("nume");
        String parola = resultSet.getString("parola");
        Jucator jucator = new Jucator(nume, parola);
        jucator.setId(id);
        return jucator;
    }

    @Override
    public Jucator find(Integer id) throws IdNotFoundException {
        logger.traceEntry();
        Jucator entity = null;
        try (
                var connection = DriverManager.getConnection(url);
                var preparedStatement = connection.prepareStatement(
                        "SELECT id, nume, parola FROM Jucator WHERE id = ?"
                );
        ) {
            preparedStatement.setInt(1, id);

            ResultSet resultSet = preparedStatement.executeQuery();
            if (resultSet.next()) {
                entity = readEntityFromResultSet(resultSet);
                logger.trace("find Jucator in db");
            } else {
                throw new IdNotFoundException();
            }
        } catch (SQLException e) {
            logger.error(e);
        }
        logger.traceExit(entity);
        return entity;
    }

    @Override
    public void store(Jucator jucator) throws IdAlreadyExistsException {
        assert false;
    }

    @Override
    public void update(Integer integer, Jucator jucator) throws IdNotFoundException {
        assert false;
    }

    @Override
    public void remove(Integer integer) throws IdNotFoundException {
        assert false;
    }

    @Override
    public Jucator[] getAll() {
        assert false;
        return new Jucator[0];
    }

    @Override
    public Jucator findByNume(String nume) {
        logger.traceEntry();
        Jucator entity = null;
        try (
                var connection = DriverManager.getConnection(url);
                var preparedStatement = connection.prepareStatement(
                        "SELECT id, nume, parola FROM Jucator WHERE nume = ?"
                );
        ) {
            preparedStatement.setString(1, nume);

            ResultSet resultSet = preparedStatement.executeQuery();
            if (resultSet.next()) {
                entity = readEntityFromResultSet(resultSet);
                logger.trace("find Jucator in db");
            }
        } catch (SQLException e) {
            logger.error(e);
        }
        logger.traceExit(entity);
        return entity;
    }
}
