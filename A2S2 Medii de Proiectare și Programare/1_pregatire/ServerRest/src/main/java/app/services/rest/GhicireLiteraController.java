package app.services.rest;

import domain.GhicireLitera;
import domain.Joc;
import org.hibernate.SessionFactory;
import org.hibernate.boot.MetadataSources;
import org.hibernate.boot.registry.StandardServiceRegistry;
import org.hibernate.boot.registry.StandardServiceRegistryBuilder;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;
import repo.*;

import javax.annotation.PostConstruct;
import java.util.ArrayList;

@CrossOrigin(origins = "http://localhost:3000", maxAge = 3600)
@RestController
@RequestMapping("/app/ghicire")
public class GhicireLiteraController {
    private RepoGhicireLitera repoGhicireLitera;

    @PostConstruct
    public void initialize() {
        RepoManager repoManager = new RepoManager();
        repoGhicireLitera = repoManager.getRepoGhicireLitera();
    }

    @RequestMapping(method = RequestMethod.GET)
    public ResponseEntity<?> ghicireLitera(@RequestParam int jocId, @RequestParam int jucatorId) {
        GhicireLitera[] ghiciriLitera = repoGhicireLitera.findByJocIdAndGhicitorJucatorId(jocId, jucatorId);
        return new ResponseEntity<GhicireLitera[]>(ghiciriLitera, HttpStatus.OK);
    }
}
