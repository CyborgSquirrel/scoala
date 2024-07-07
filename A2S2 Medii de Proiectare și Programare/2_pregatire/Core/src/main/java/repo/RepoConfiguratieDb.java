package repo;

import domain.Configuratie;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;

public class RepoConfiguratieDb implements RepoConfiguratie {
    private static final Logger LOGGER = LogManager.getLogger();

    // BEGIN: work smart not hard
    private static final String ENTITY_NAME = "Configuratie";
    private static final SqlUtil SQL_UTIL = new SqlUtil(
            "Configuratie",
            new String[]{"id"},
            new String[]{"linie", "coloana", "indiciu"}
    );

    private static Configuratie readEntityFromResultSet(ResultSet resultSet) throws SQLException {
        int id = resultSet.getInt("id");
        int linie = resultSet.getInt("linie");
        int coloana = resultSet.getInt("coloana");
        String indiciu = resultSet.getString("indiciu");
        Configuratie configuratie = new Configuratie(linie, coloana, indiciu);
        configuratie.setId(id);
        return configuratie;
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

    private static int addDataColumns(int offset, PreparedStatement preparedStatement, Configuratie configuratie) {
        try {
            preparedStatement.setInt(offset, configuratie.getLinie());
            offset += 1;
            preparedStatement.setInt(offset, configuratie.getColoana());
            offset += 1;
            preparedStatement.setString(offset, configuratie.getIndiciu());
            offset += 1;

            return offset;
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    // END

    String url;

    public RepoConfiguratieDb(String url) {
        this.url = url;
    }

    @Override
    public Configuratie find(Integer id) throws IdNotFoundException {
        LOGGER.traceEntry();
        Configuratie entity = null;
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
    public void store(Configuratie entity) throws IdAlreadyExistsException {
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
    public void update(Integer id, Configuratie entity) throws IdNotFoundException {
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
    public Configuratie[] getAll() {
        LOGGER.traceEntry();
        ArrayList<Configuratie> entityArrayList = new ArrayList<>();
        try (
                var connection = DriverManager.getConnection(url);
                var preparedStatement = connection.prepareStatement(
                        SQL_UTIL.makeGetAll()
                );
        ) {
            ResultSet resultSet = preparedStatement.executeQuery();
            LOGGER.trace("get all " + ENTITY_NAME + " from db");
            while (resultSet.next()) {
                Configuratie entity = readEntityFromResultSet(resultSet);
                entityArrayList.add(entity);
            }
        } catch (SQLException e) {
            LOGGER.error(e);
        }
        Configuratie[] entities = entityArrayList.toArray(new Configuratie[0]);
        LOGGER.traceExit(entities);
        return entities;
    }
}
