package domain;

import java.sql.ResultSet;
import java.sql.SQLException;

public class Persoana extends Entity {
    String nume;
    String prenume;
    String username;
    String parola;
    Oras oras;
    String strada;
    String numarStrada;
    String telefon;

    public static Persoana fromResultSet(ResultSet resultSet) {
        long id;
        try {
            id = resultSet.getLong("id");
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        long serialVersionUID;
        try {
            serialVersionUID = resultSet.getLong("serialVersionUID");
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        String nume;;
        try {
            nume = resultSet.getString("nume");
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        String prenume;
        try {
            prenume = resultSet.getString("prenume");
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        String username;
        try {
            username = resultSet.getString("username");
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        String parola;
        try {
            parola = resultSet.getString("parola");
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        Oras oras;
        try {
            oras = Oras.fromValue(resultSet.getString("oras"));
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        String strada;
        try {
            strada = resultSet.getString("strada");
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        String numarStrada;
        try {
            numarStrada = resultSet.getString("numarStrada");
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        String telefon;
        try {
            telefon = resultSet.getString("telefon");
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        return new Persoana(serialVersionUID, id, nume, prenume, username, parola, oras, strada, numarStrada, telefon);
    }

    public Persoana(long serialVersionUID, long id, String nume, String prenume, String username, String parola, Oras oras, String strada, String numarStrada, String telefon) {
        super(serialVersionUID, id);
        this.nume = nume;
        this.prenume = prenume;
        this.username = username;
        this.parola = parola;
        this.oras = oras;
        this.strada = strada;
        this.numarStrada = numarStrada;
        this.telefon = telefon;
    }

    public String getNume() {
        return nume;
    }

    public String getPrenume() {
        return prenume;
    }

    public String getUsername() {
        return username;
    }

    public String getParola() {
        return parola;
    }

    public Oras getOras() {
        return oras;
    }

    public String getStrada() {
        return strada;
    }

    public String getNumarStrada() {
        return numarStrada;
    }

    public String getTelefon() {
        return telefon;
    }
}
