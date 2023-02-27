package repo;

import domain.Nevoie;
import domain.Persoana;

import java.sql.*;
import java.util.ArrayList;

public class RepoNevoie {
    private String url;
    private String userName;
    private String password;

    public RepoNevoie(String url, String userName, String password) {
        this.url = url;
        this.userName = userName;
        this.password = password;
    }

    public Nevoie find(long id) throws ItemDoesntExistException {
        try (
                Connection connection = DriverManager.getConnection(this.url, this.userName, this.password);
                PreparedStatement statement = connection.prepareStatement(
                        "SELECT \"Nevoie\".id id, serialVersionUID, titlu, descriere, deadline, omInNevoie, omSalvator, status FROM \"Nevoie\" INNER JOIN \"Entity\" ON \"Entity\".id = \"Nevoie\".id WHERE \"Nevoie\".id = ?"
                );
        ) {
            statement.setLong(1, id);

            ResultSet resultSet = statement.executeQuery();
            if (resultSet.next()) {
                return Nevoie.fromResultSet(resultSet);
            } else {
                throw new ItemDoesntExistException();
            }

        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    public Nevoie[] getAll() {
        try (
                Connection connection = DriverManager.getConnection(this.url, this.userName, this.password);
                PreparedStatement statement = connection.prepareStatement(
                        "SELECT \"Nevoie\".id id, serialVersionUID, titlu, descriere, deadline, omInNevoie, omSalvator, status FROM \"Nevoie\" INNER JOIN \"Entity\" ON \"Entity\".id = \"Nevoie\".id"
                );
                ResultSet resultSet = statement.executeQuery();
        ) {
            ArrayList<Nevoie> nevoies = new ArrayList<>();
            while (resultSet.next()) {
                Nevoie nevoie = Nevoie.fromResultSet(resultSet);
                nevoies.add(nevoie);
            }
            return nevoies.toArray(new Nevoie[0]);
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    public void store(Nevoie nevoie) throws ItemAlreadyExistsException {
        String[] returnId = { "id" };

        long id;
        try (
                Connection connection = DriverManager.getConnection(this.url, this.userName, this.password);
                PreparedStatement statement = connection.prepareStatement(
                        "INSERT INTO \"Entity\"(serialVersionUID) VALUES (?)",
                        returnId
                );
        ) {
            statement.setLong(1, nevoie.getSerialVersionUID());

            statement.execute();

            ResultSet generatedKeys = statement.getGeneratedKeys();
            generatedKeys.next();
            id = generatedKeys.getLong("id");
        } catch (SQLException e) {
            if (e.getSQLState().startsWith("23")) {
                throw new ItemAlreadyExistsException();
            }
            throw new RuntimeException(e);
        }

        try (
                Connection connection = DriverManager.getConnection(this.url, this.userName, this.password);
                PreparedStatement statement = connection.prepareStatement(
                        "INSERT INTO \"Nevoie\"(id, titlu, descriere, deadline, omInNevoie, omSalvator, status) VALUES (?, ?, ?, ?, ?, ?, ?)"
                );
        ) {
            statement.setLong(1, id);
            statement.setString(2, nevoie.getTitlu());
            statement.setString(3, nevoie.getDescriere());
            statement.setTimestamp(4, Timestamp.valueOf(nevoie.getDeadline()));
            statement.setLong(5, nevoie.getOmInNevoie());
            if (nevoie.getOmSalvator() == null) {
                statement.setNull(6, Types.BIGINT);
            } else {
                statement.setLong(6, nevoie.getOmSalvator());
            }
            statement.setString(7, nevoie.getStatus());

            statement.execute();
        } catch (SQLException e) {
            System.out.println(e);
            if (e.getSQLState().startsWith("23")) {
                throw new ItemAlreadyExistsException();
            }
            throw new RuntimeException(e);
        }
    }

    public void update(Nevoie nevoie) throws ItemAlreadyExistsException {
        try (
                Connection connection = DriverManager.getConnection(this.url, this.userName, this.password);
                PreparedStatement statement = connection.prepareStatement(
                        "UPDATE \"Nevoie\" SET titlu = ?, descriere = ?, deadline = ?, omInNevoie = ?, omSalvator = ?, status = ? WHERE id = ?"
                );
        ) {
            statement.setString(1, nevoie.getTitlu());
            statement.setString(2, nevoie.getDescriere());
            statement.setTimestamp(3, Timestamp.valueOf(nevoie.getDeadline()));
            statement.setLong(4, nevoie.getOmInNevoie());
            if (nevoie.getOmSalvator() == null) {
                statement.setNull(5, Types.BIGINT);
            } else {
                statement.setLong(5, nevoie.getOmSalvator());
            }
            statement.setString(6, nevoie.getStatus());
            statement.setLong(7, nevoie.getId());

            statement.execute();
        } catch (SQLException e) {
            if (e.getSQLState().startsWith("23")) {
                throw new ItemAlreadyExistsException();
            }
            throw new RuntimeException(e);
        }
    }
}
