package app.services.rest;

import domain.DTOPozitie;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;
import repo.*;
import srv.SrvApplication;
import srv.SrvApplicationImpl;

import javax.annotation.PostConstruct;

@CrossOrigin(origins = "http://localhost:3000", maxAge = 3600)
@RestController
@RequestMapping("/app/joc")
public class JocController {
    SrvApplication srvApplication;

    @PostConstruct
    public void initialize() {
        RepoManager repoManager = new RepoManager();

        srvApplication = new SrvApplicationImpl(repoManager.getRepoJucator(),
                repoManager.getRepoJoc(),
                repoManager.getRepoPozitie());
    }

    @RequestMapping(path = "/{id}/pozitii-propuse", method = RequestMethod.POST)
    public ResponseEntity<?> adaugaPozitiePropusa(@PathVariable int id, @RequestBody DTOPozitie dtoPozitie) {
        srvApplication.alegePozitie(id, dtoPozitie.getLinie(), dtoPozitie.getColoana());
        return new ResponseEntity<String>("ok", HttpStatus.OK);
    }
}
