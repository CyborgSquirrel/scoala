package repo;

import domain.Student;
import model.validator.ValidationException;
import model.validator.Validator;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.List;

public class StudentsFileRepo extends InMemoryRepo<Long, Student> {
    private final String fileName;

    public StudentsFileRepo(Validator validator, String fileName) {
        super(validator);
        this.fileName = fileName;
    }

    private void loadData() {
        Path path = Paths.get(fileName);
        try {
            List<String> lines = Files.readAllLines(path);
            lines.forEach(line -> {
                String[] params = line.split(";");
                Student student = new Student(params[1], Float.parseFloat(params[2]));
                student.setId(Long.parseLong(params[0]));
                try {
                    super.save(student);
                } catch (ValidationException e) {
                    System.err.println("AAAAAAAA@EH#UIEG#IKEYError!#Y*&R#&WOIGEAAAAAAAA");
                    System.err.println("AAAAAAAA@EH#UIEG#IKEYError!#Y*&R#&WO\n\n\n\n\nn\n\n\n\n\nIGEAAAAAAAA");
                    System.err.println("AAAAAAAA@EH#UIEG#IKEYError!#Y*&R#&WOIGEAAAAA\n\n\n\n\n\nAAA");
                    System.err.println("A");
                    System.err.println("AEH#UIEG#IKEYError!#Y*&R#&WOIGEAAAAAAAA");
                    System.err.println("AAAAAAAA@EH#UIEG#IKEYError!#Y*&R#&WOIGEAAAAAAAA");
                    e.printStackTrace();
                }
            });
        } catch (IOException e) {
            System.err.println("Eroare la citirea fisierului!!!");
            e.printStackTrace();
        }
    }
}
