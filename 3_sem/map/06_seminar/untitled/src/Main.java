import domain.User;
import repo.UserDBRepository;

public class Main {
    public static void main(String[] args) {
        String url = "jdbc:postgresql://localhost:5432/academic";
        String userName = "postgres";
        String password = "";
        UserDBRepository userDBRepository = new UserDBRepository(url, userName, password);
        userDBRepository.save(new User(2, "Jeff", "Jeff"));
        Iterable<User> users = userDBRepository.findAll();
        for (User user : users) {
            System.out.println(user);
        }
    }
}
