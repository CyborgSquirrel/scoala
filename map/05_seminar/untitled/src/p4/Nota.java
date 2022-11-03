package p4;

public class Nota {
    String professor;
    Student student;
    Tema tema;

    @Override
    public String toString() {
        return "Nota{" +
                "professor='" + professor + '\'' +
                ", student=" + student +
                ", tema=" + tema +
                ", value=" + value +
                '}';
    }

    public String getProfessor() {
        return professor;
    }

    public void setProfessor(String professor) {
        this.professor = professor;
    }

    public Student getStudent() {
        return student;
    }

    public void setStudent(Student student) {
        this.student = student;
    }

    public Tema getTema() {
        return tema;
    }

    public void setTema(Tema tema) {
        this.tema = tema;
    }

    public double getValue() {
        return value;
    }

    public void setValue(double value) {
        this.value = value;
    }

    public Nota(String professor, Student student, Tema tema, double value) {
        this.professor = professor;
        this.student = student;
        this.tema = tema;
        this.value = value;
    }

    double value;
}
