package domain;

public class Jucator implements Entity<Integer> {
    int id;
    String nume;
    String parola;

    public Jucator(String nume, String parola) {
        this.nume = nume;
        this.parola = parola;
    }

    @Override
    public Integer getId() {
        return id;
    }

    @Override
    public void setId(Integer id) {
        this.id = id;
    }

    public String getNume() {
        return nume;
    }

    public void setNume(String nume) {
        this.nume = nume;
    }

    public String getParola() {
        return parola;
    }

    public void setParola(String parola) {
        this.parola = parola;
    }
}
