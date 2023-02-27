package p4;

public class Student extends Entity<Integer> {
    private int group;
    private String name;

    @Override
    public String toString() {
        return "Student{" +
                "group=" + group +
                ", name='" + name + '\'' +
                '}';
    }

    public int getGroup() {
        return group;
    }

    public void setGroup(int group) {
        this.group = group;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public Student(Integer integer, int group, String name) {
        super(integer);
        this.group = group;
        this.name = name;
    }
}
