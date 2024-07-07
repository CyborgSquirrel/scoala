import domain.Student;
import model.validator.StudentValidator;
import model.validator.Validator;
import repo.StudentsFileRepo;

public class TestStudent {
    public static void main(String[] args) {
        Validator<Student> studentValidator = new StudentValidator();
        StudentsFileRepo studentsFileRepo = new StudentsFileRepo(studentValidator, "studentsData.csv");
        studentsFileRepo.getAll().forEach(System.out::println);
    }
}
