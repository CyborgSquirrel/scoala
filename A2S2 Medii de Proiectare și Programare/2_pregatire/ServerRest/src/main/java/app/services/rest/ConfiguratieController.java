package app.services.rest;

import domain.Configuratie;
import domain.Joc;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;
import repo.*;

import javax.annotation.PostConstruct;
import java.util.ArrayList;

@CrossOrigin(origins = "http://localhost:3000", maxAge = 3600)
@RestController
@RequestMapping("/app/configuratie")
public class ConfiguratieController {
    private RepoConfiguratie repoConfiguratie;

    @PostConstruct
    public void initialize() {
        RepoManager repoManager = new RepoManager();
        repoConfiguratie = repoManager.getRepoConfiguratie();
    }

    @RequestMapping(method = RequestMethod.POST)
    public Configuratie store(@RequestBody Configuratie configuratie) {
        try {
            repoConfiguratie.store(configuratie);
            return configuratie;
        } catch (IdAlreadyExistsException e) {
            throw new RuntimeException(e);
        }
    }
}
