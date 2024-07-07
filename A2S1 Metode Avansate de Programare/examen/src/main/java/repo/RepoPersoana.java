package repo;

import domain.Persoana;

import java.sql.*;
import java.util.ArrayList;

public class RepoPersoana {
    private String url;
    private String userName;
    private String password;

    public RepoPersoana(String url, String userName, String password) {
        this.url = url;
        this.userName = userName;
        this.password = password;
    }

    public Persoana find(long id) throws ItemDoesntExistException {
        try (
                Connection connection = DriverManager.getConnection(this.url, this.userName, this.password);
                PreparedStatement statement = connection.prepareStatement(
                        "SELECT \"Persoana\".id id, serialVersionUID, nume, prenume, username, parola, oras, strada, numarStrada, telefon FROM \"Persoana\" INNER JOIN \"Entity\" ON \"Entity\".id = \"Persoana\".id WHERE \"Persoana\".id = ?"
                );
        ) {
            statement.setLong(1, id);

            ResultSet resultSet = statement.executeQuery();
            if (resultSet.next()) {
                return Persoana.fromResultSet(resultSet);
            } else {
                throw new ItemDoesntExistException();
            }

        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    public Persoana[] getAll() {
        try (
                Connection connection = DriverManager.getConnection(this.url, this.userName, this.password);
                PreparedStatement statement = connection.prepareStatement(
                        "SELECT \"Persoana\".id id, serialVersionUID, nume, prenume, username, parola, oras, strada, numarStrada, telefon FROM \"Persoana\" INNER JOIN \"Entity\" ON \"Entity\".id = \"Persoana\".id"
                );
                ResultSet resultSet = statement.executeQuery();
        ) {
            ArrayList<Persoana> persoane = new ArrayList<>();
            while (resultSet.next()) {
                Persoana persoana = Persoana.fromResultSet(resultSet);
                persoane.add(persoana);
            }
            return persoane.toArray(new Persoana[0]);
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    public void store(Persoana persoana) throws ItemAlreadyExistsException {
        String[] returnId = { "id" };

        long id;
        try (
                Connection connection = DriverManager.getConnection(this.url, this.userName, this.password);
                PreparedStatement statement = connection.prepareStatement(
                        "INSERT INTO \"Entity\"(serialVersionUID) VALUES (?)",
                        returnId
                );
        ) {
            statement.setLong(1, persoana.getSerialVersionUID());

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
                        "INSERT INTO \"Persoana\"(id, nume, prenume, username, parola, oras, strada, numarStrada, telefon) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?)"
                );
        ) {
            statement.setLong(1, id);
            statement.setString(2, persoana.getNume());
            statement.setString(3, persoana.getPrenume());
            statement.setString(4, persoana.getUsername());
            statement.setString(5, persoana.getParola());
            statement.setString(6, persoana.getOras().toValue());
            statement.setString(7, persoana.getStrada());
            statement.setString(8, persoana.getNumarStrada());
            statement.setString(9, persoana.getTelefon());

            statement.execute();
        } catch (SQLException e) {
            if (e.getSQLState().startsWith("23")) {
                throw new ItemAlreadyExistsException();
            }
            throw new RuntimeException(e);
        }
    }
}
