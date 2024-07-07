package p4;

public class Tema {
    String desc;
    String id;

    @Override
    public String toString() {
        return "Tema{" +
                "desc='" + desc + '\'' +
                ", id='" + id + '\'' +
                '}';
    }

    public String getDesc() {
        return desc;
    }

    public void setDesc(String desc) {
        this.desc = desc;
    }

    public String getId() {
        return id;
    }

    public void setId(String id) {
        this.id = id;
    }

    public Tema(String desc, String id) {
        this.desc = desc;
        this.id = id;
    }
}
