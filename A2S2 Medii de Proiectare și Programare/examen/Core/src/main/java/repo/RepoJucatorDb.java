package repo;

import domain.Jucator;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;

public class RepoJucatorDb implements RepoJucator {
    private static final Logger LOGGER = LogManager.getLogger();

    // BEGIN: work smart not hard
    private static final String ENTITY_NAME = "Jucator";
    private static final SqlUtil SQL_UTIL = new SqlUtil(
            "Jucator",
            new String[]{"id"},
            new String[]{"alias"}
    );


    private static Jucator readEntityFromResultSet(ResultSet resultSet) throws SQLException {
        int id = resultSet.getInt("id");
        String alias = resultSet.getString("alias");
        Jucator jucator = new Jucator(alias);
        jucator.setId(id);
        return jucator;
    }

    private static int addIdColumns(int offset, PreparedStatement preparedStatement, Integer id) {
        try {
            preparedStatement.setInt(offset, id);
            offset += 1;

            return offset;
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    private static int addDataColumns(int offset, PreparedStatement preparedStatement, Jucator entity) {
        try {
            preparedStatement.setString(offset, entity.getAlias());
            offset += 1;

            return offset;
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    // END

    String url;

    public RepoJucatorDb(String url) {
        this.url = url;
    }

    @Override
    public Jucator find(Integer id) throws IdNotFoundException {
        LOGGER.traceEntry();
        Jucator entity = null;
        try (
                var connection = DriverManager.getConnection(url);
                var preparedStatement = connection.prepareStatement(
                        SQL_UTIL.makeFind()
                );
        ) {
            int offset = 1;
            offset = addIdColumns(offset, preparedStatement, id);

            ResultSet resultSet = preparedStatement.executeQuery();
            if (resultSet.next()) {
                entity = readEntityFromResultSet(resultSet);
                LOGGER.trace("find " + ENTITY_NAME + " in db");
            } else {
                throw new IdNotFoundException();
            }
        } catch (SQLException e) {
            LOGGER.error(e);
        }
        LOGGER.traceExit(entity);
        return entity;
    }

    @Override
    public void store(Jucator entity) throws IdAlreadyExistsException {
        LOGGER.traceEntry();
        try (
                var connection = DriverManager.getConnection(url);
                var preparedStatement = connection.prepareStatement(
                        SQL_UTIL.makeStore()
                );
        ) {
            int offset = 1;
            offset = addDataColumns(offset, preparedStatement, entity);

            int rowCount = preparedStatement.executeUpdate();
            if (rowCount == 0) {
                throw new IdAlreadyExistsException();
            }
            LOGGER.trace("store " + ENTITY_NAME + " in db");
        } catch (SQLException e) {
            LOGGER.error(e);
        }
        LOGGER.traceExit();
    }

    @Override
    public void update(Integer id, Jucator entity) throws IdNotFoundException {
        LOGGER.traceEntry();
        try (
                var connection = DriverManager.getConnection(url);
                var preparedStatement = connection.prepareStatement(
                        SQL_UTIL.makeUpdate()
                );
        ) {
            int offset = 1;
            offset = addDataColumns(offset, preparedStatement, entity);
            offset = addIdColumns(offset, preparedStatement, id);

            int rowCount = preparedStatement.executeUpdate();
            if (rowCount == 0) {
                throw new IdNotFoundException();
            }
            LOGGER.trace("update " + ENTITY_NAME + " in db");
        } catch (SQLException e) {
            LOGGER.error(e);
        }
        LOGGER.traceExit();
    }

    @Override
    public void remove(Integer id) throws IdNotFoundException {
        LOGGER.traceEntry();
        try (
                var connection = DriverManager.getConnection(url);
                var preparedStatement = connection.prepareStatement(
                        SQL_UTIL.makeRemove()
                );
        ) {
            int offset = 1;
            offset = addIdColumns(offset, preparedStatement, id);

            int rowCount = preparedStatement.executeUpdate();
            if (rowCount == 0) {
                throw new IdNotFoundException();
            }
            LOGGER.trace("remove " + ENTITY_NAME + " from db");
        } catch (SQLException e) {
            LOGGER.error(e);
        }
        LOGGER.traceExit();
    }

    @Override
    public Jucator[] getAll() {
        LOGGER.traceEntry();
        ArrayList<Jucator> entityArrayList = new ArrayList<>();
        try (
                var connection = DriverManager.getConnection(url);
                var preparedStatement = connection.prepareStatement(
                        SQL_UTIL.makeGetAll()
                );
        ) {
            ResultSet resultSet = preparedStatement.executeQuery();
            LOGGER.trace("get all " + ENTITY_NAME + " from db");
            while (resultSet.next()) {
                Jucator entity = readEntityFromResultSet(resultSet);
                entityArrayList.add(entity);
            }
        } catch (SQLException e) {
            LOGGER.error(e);
        }
        Jucator[] entities = entityArrayList.toArray(new Jucator[0]);
        LOGGER.traceExit(entities);
        return entities;
    }

    @Override
    public Jucator findByAlias(String alias) {
        LOGGER.traceEntry();
        Jucator entity = null;
        try (
                var connection = DriverManager.getConnection(url);
                var preparedStatement = connection.prepareStatement(
                        "SELECT id, alias FROM Jucator WHERE alias = ?"
                );
        ) {
            preparedStatement.setString(1, alias);

            ResultSet resultSet = preparedStatement.executeQuery();
            if (resultSet.next()) {
                entity = readEntityFromResultSet(resultSet);
                LOGGER.trace("find Jucator in db");
            }
        } catch (SQLException e) {
            LOGGER.error(e);
        }
        LOGGER.traceExit(entity);
        return entity;
    }
}
