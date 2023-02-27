package domain;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.time.LocalDateTime;

public class Nevoie extends Entity {
    String titlu;
    String descriere;
    LocalDateTime deadline;
    long omInNevoie;
    Long omSalvator;
    String status;

    public static Nevoie fromResultSet(ResultSet resultSet) {
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
        String titlu;
        try {
            titlu = resultSet.getString("titlu");
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        String descriere;
        try {
            descriere = resultSet.getString("descriere");
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        LocalDateTime deadline;
        try {
            deadline = resultSet.getTimestamp("deadline").toLocalDateTime();
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        long omInNevoie;
        try {
            omInNevoie = resultSet.getLong("omInNevoie");
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        Long omSalvator;
        try {
            omSalvator = resultSet.getLong("omSalvator");
            if (resultSet.wasNull()) {
                omSalvator = null;
            }
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        String status;
        try {
            status = resultSet.getString("status");
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        return new Nevoie(serialVersionUID, id, titlu, descriere, deadline, omInNevoie, omSalvator, status);
    }

    public Nevoie(long serialVersionUID, long id, String titlu, String descriere, LocalDateTime deadline, long omInNevoie, Long omSalvator, String status) {
        super(serialVersionUID, id);
        this.titlu = titlu;
        this.descriere = descriere;
        this.deadline = deadline;
        this.omInNevoie = omInNevoie;
        this.omSalvator = omSalvator;
        this.status = status;
    }

    public String getTitlu() {
        return titlu;
    }

    public String getDescriere() {
        return descriere;
    }

    public LocalDateTime getDeadline() {
        return deadline;
    }

    public long getOmInNevoie() {
        return omInNevoie;
    }

    public Long getOmSalvator() {
        return omSalvator;
    }

    public String getStatus() {
        return status;
    }
}
