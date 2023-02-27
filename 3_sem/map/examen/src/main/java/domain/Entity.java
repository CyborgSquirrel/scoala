package domain;

public class Entity {
    long serialVersionUID;
    long id;

    public Entity(long serialVersionUID, long id) {
        this.serialVersionUID = serialVersionUID;
        this.id = id;
    }

    public long getSerialVersionUID() {
        return serialVersionUID;
    }

    public long getId() {
        return id;
    }
}
