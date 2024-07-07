package app.services.rest;

import domain.Joc;
import org.hibernate.SessionFactory;
import org.hibernate.boot.MetadataSources;
import org.hibernate.boot.registry.StandardServiceRegistry;
import org.hibernate.boot.registry.StandardServiceRegistryBuilder;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;
import repo.IdNotFoundException;
import repo.RepoJoc;
import repo.RepoJocHbm;
import repo.RepoManager;

import javax.annotation.PostConstruct;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Properties;

@CrossOrigin(origins = "http://localhost:3000", maxAge = 3600)
@RestController
@RequestMapping("/app/joc")
public class JocController {
    private RepoJoc repoJoc;

    @PostConstruct
    public void initialize() {
        RepoManager repoManager = new RepoManager();
        repoJoc = repoManager.getRepoJoc();
    }

    @RequestMapping(value = "/{id}/cuvinte", method = RequestMethod.GET)
    public ResponseEntity<?> cuvinte(@PathVariable int id) {
        try {
            Joc joc = repoJoc.find(id);
            ArrayList<String> cuvinte = new ArrayList<>();
            for (int i = 0; i < 3; ++i) {
                cuvinte.add(joc.getJucatorCuvant(i));
            }
            return new ResponseEntity<String[]>(cuvinte.toArray(new String[0]), HttpStatus.OK);
        } catch (IdNotFoundException e) {
            return new ResponseEntity<String>("Joc not found.", HttpStatus.NOT_FOUND);
        }
    }
}
