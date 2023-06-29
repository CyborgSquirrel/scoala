package repo;

import domain.DTOPozitie;
import domain.Joc;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import java.sql.*;
import java.time.LocalDateTime;
import java.util.ArrayList;

public class RepoJocDb implements RepoJoc {
    private static final Logger LOGGER = LogManager.getLogger();

    // BEGIN: work smart not hard
    private static final String ENTITY_NAME = "Joc";
    private static final SqlUtil SQL_UTIL = new SqlUtil(
            "Joc",
            new String[]{"id"},
            new String[]{"jucatorId", "timestampInceput", "timestampSfarsit",
                    "gropiLinie_0", "gropiColoana_0",
                    "gropiLinie_1", "gropiColoana_1",
                    "gropiLinie_2", "gropiColoana_2",
                    "gropiLinie_3", "gropiColoana_3",
                    "gropiLinie_4", "gropiColoana_4",
                    "punctaj", "finalizat"}
    );

    private static Joc readEntityFromResultSet(ResultSet resultSet) throws SQLException {
        int id = resultSet.getInt("id");
        int jucatorId = resultSet.getInt("jucatorId");
        LocalDateTime timestampInceput = resultSet.getTimestamp("timestampInceput").toLocalDateTime();

        LocalDateTime timestampSfarsit = null;
        try {
            timestampSfarsit = resultSet.getTimestamp("timestampSfarsit").toLocalDateTime();
        } catch (NullPointerException e) {

        }

        ArrayList<DTOPozitie> gropiArrayList = new ArrayList<>();
        for (int i = 0; i < 5; ++i) {
            StringBuilder linieBuilder = new StringBuilder();
            linieBuilder.append("gropiLinie_");
            linieBuilder.append(i);
            String linieString = linieBuilder.toString();
            int linie = resultSet.getInt(linieString);

            StringBuilder coloanaBuilder = new StringBuilder();
            coloanaBuilder.append("gropiColoana_");
            coloanaBuilder.append(i);
            String coloanaString = coloanaBuilder.toString();
            int coloana = resultSet.getInt(coloanaString);

            DTOPozitie groapa = new DTOPozitie(linie, coloana);
            gropiArrayList.add(groapa);
        }

        DTOPozitie[] gropi = gropiArrayList.toArray(new DTOPozitie[0]);

        int punctaj = resultSet.getInt("punctaj");
        boolean finalizat = resultSet.getBoolean("finalizat");

        Joc entity = new Joc(jucatorId, timestampInceput, timestampSfarsit, gropi, punctaj, finalizat);
        entity.setId(id);
        return entity;
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

    private static int addDataColumns(int offset, PreparedStatement preparedStatement, Joc entity) {
        try {
            preparedStatement.setInt(offset, entity.getJucatorId());
            offset += 1;
            preparedStatement.setTimestamp(offset, Timestamp.valueOf(entity.getTimestampInceput()));
            offset += 1;

            if (entity.getTimestampSfarsit() == null) {
                preparedStatement.setNull(offset, Types.NULL);
            } else {
                preparedStatement.setTimestamp(offset, Timestamp.valueOf(entity.getTimestampSfarsit()));
            }
            offset += 1;

            for (int i = 0; i < 5; ++i) {
                preparedStatement.setInt(offset, entity.getGropi()[i].getLinie());
                offset += 1;
                preparedStatement.setInt(offset, entity.getGropi()[i].getColoana());
                offset += 1;
            }
            preparedStatement.setInt(offset, entity.getPunctaj());
            offset += 1;
            preparedStatement.setBoolean(offset, entity.isFinalizat());
            offset += 1;

            return offset;
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    // END

    String url;

    public RepoJocDb(String url) {
        this.url = url;
    }

    @Override
    public Joc find(Integer id) throws IdNotFoundException {
        LOGGER.traceEntry();
        Joc entity = null;
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
    public void store(Joc entity) throws IdAlreadyExistsException {
        LOGGER.traceEntry();
        try (
                var connection = DriverManager.getConnection(url);
                var preparedStatement = connection.prepareStatement(
                        SQL_UTIL.makeStore()
                );
        ) {
            int offset = 1;
            offset = addDataColumns(offset, preparedStatement, entity);

            ResultSet resultSet = preparedStatement.executeQuery();

            System.out.println(resultSet.getInt("id"));
            if (resultSet.next()) {
                entity.setId(resultSet.getInt("id"));
            } else {
                throw new IdAlreadyExistsException();
            }
            LOGGER.trace("store " + ENTITY_NAME + " in db");
        } catch (SQLException e) {
            LOGGER.error(e);
        }
        LOGGER.traceExit();
    }

    @Override
    public void update(Integer id, Joc entity) throws IdNotFoundException {
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
    public Joc[] getAll() {
        LOGGER.traceEntry();
        ArrayList<Joc> entityArrayList = new ArrayList<>();
        try (
                var connection = DriverManager.getConnection(url);
                var preparedStatement = connection.prepareStatement(
                        SQL_UTIL.makeGetAll()
                );
        ) {
            ResultSet resultSet = preparedStatement.executeQuery();
            LOGGER.trace("get all " + ENTITY_NAME + " from db");
            while (resultSet.next()) {
                Joc entity = readEntityFromResultSet(resultSet);
                entityArrayList.add(entity);
            }
        } catch (SQLException e) {
            LOGGER.error(e);
        }
        Joc[] entities = entityArrayList.toArray(new Joc[0]);
        LOGGER.traceExit(entities);
        return entities;
    }

    @Override
    public Joc[] getByJucatorId(int jucatorId) {
        LOGGER.traceEntry();
        ArrayList<Joc> entityArrayList = new ArrayList<>();
        try (
                var connection = DriverManager.getConnection(url);
                var preparedStatement = connection.prepareStatement(
                        SQL_UTIL.makeGetAll() + " WHERE jucatorId = ?"
                );
        ) {
            preparedStatement.setInt(1, jucatorId);

            ResultSet resultSet = preparedStatement.executeQuery();
            LOGGER.trace("get all " + ENTITY_NAME + " from db");
            while (resultSet.next()) {
                Joc entity = readEntityFromResultSet(resultSet);
                entityArrayList.add(entity);
            }
        } catch (SQLException e) {
            LOGGER.error(e);
        }
        Joc[] entities = entityArrayList.toArray(new Joc[0]);
        LOGGER.traceExit(entities);
        return entities;
    }
}
