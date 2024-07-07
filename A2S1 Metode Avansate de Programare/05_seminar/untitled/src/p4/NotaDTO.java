package p4;

public class NotaDTO {
    double nota;
    String studentName;
    String temaId;

    @Override
    public String toString() {
        return "NotaDTO{" +
                "nota=" + nota +
                ", studentName='" + studentName + '\'' +
                ", temaId='" + temaId + '\'' +
                '}';
    }

    public double getNota() {
        return nota;
    }

    public void setNota(double nota) {
        this.nota = nota;
    }

    public String getStudentName() {
        return studentName;
    }

    public void setStudentName(String studentName) {
        this.studentName = studentName;
    }

    public String getTemaId() {
        return temaId;
    }

    public void setTemaId(String temaId) {
        this.temaId = temaId;
    }

    public NotaDTO(double nota, String studentName, String temaId) {
        this.nota = nota;
        this.studentName = studentName;
        this.temaId = temaId;
    }
}
