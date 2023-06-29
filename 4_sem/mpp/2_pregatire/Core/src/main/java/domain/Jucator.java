package domain;

public class Jucator implements Entity<Integer> {
    int id;
    String alias;

    public Jucator(String alias) {
        this.alias = alias;
    }

    @Override
    public Integer getId() {
        return id;
    }

    @Override
    public void setId(Integer id) {
        this.id = id;
    }

    public String getAlias() {
        return alias;
    }

    public void setAlias(String alias) {
        this.alias = alias;
    }
}
