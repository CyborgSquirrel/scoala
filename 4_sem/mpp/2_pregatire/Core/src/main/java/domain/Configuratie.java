package domain;

public class Configuratie implements Entity<Integer> {
    int id;
    int linie;
    int coloana;
    String indiciu;

    public Configuratie(int linie, int coloana, String indiciu) {
        this.linie = linie;
        this.coloana = coloana;
        this.indiciu = indiciu;
    }

    @Override
    public Integer getId() {
        return id;
    }

    @Override
    public void setId(Integer id) {
        this.id = id;
    }

    public int getLinie() {
        return linie;
    }

    public void setLinie(int linie) {
        this.linie = linie;
    }

    public int getColoana() {
        return coloana;
    }

    public void setColoana(int coloana) {
        this.coloana = coloana;
    }

    public String getIndiciu() {
        return indiciu;
    }

    public void setIndiciu(String indiciu) {
        this.indiciu = indiciu;
    }
}
