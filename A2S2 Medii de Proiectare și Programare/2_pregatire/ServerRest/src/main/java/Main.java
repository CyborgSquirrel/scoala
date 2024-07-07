import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.context.annotation.ComponentScan;
import org.springframework.context.annotation.Import;

// @PathVariable
// @RequestParam
// method = RequestMethod.GET
// value = "/{pathVariable}"

@ComponentScan("app")
@SpringBootApplication
@Import(WebSecurityConfig.class)
public class Main {
    public static void main(String[] args) {
        SpringApplication.run(Main.class, args);
    }
}
