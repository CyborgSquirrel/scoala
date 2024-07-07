package app.services.rest;

import domain.DTOPozitie;
import domain.Joc;
import domain.Pozitie;
import org.springframework.web.bind.annotation.*;
import repo.*;
import srv.protocol.message.DTOJocFinalizat;

import javax.annotation.PostConstruct;
import java.time.Duration;
import java.util.AbstractList;
import java.util.ArrayList;
import java.util.Arrays;

@CrossOrigin(origins = "http://localhost:3000", maxAge = 3600)
@RestController
@RequestMapping("/app/jucator")
public class JucatorController {
    private RepoJoc repoJoc;
    private RepoPozitie repoPozitie;

    @PostConstruct
    public void initialize() {
        RepoManager repoManager = new RepoManager();
        repoJoc = repoManager.getRepoJoc();
        repoPozitie = repoManager.getRepoPozitie();
    }

    @RequestMapping(path = "/{id}/jocuri-finalizate", method = RequestMethod.GET)
    public DTOJocFinalizat[] jocuriFinalizate(@PathVariable int id) {
        ArrayList<DTOJocFinalizat> dtoJocFinalizatArrayList = new ArrayList<>();

        Joc[] jocuri = repoJoc.getByJucatorId(id);
        for (Joc joc : jocuri) {
            if (!joc.isFinalizat()) continue;;

            if (joc.getTimestampSfarsit() == null) continue;

            Pozitie[] pozitiiPropuseA = repoPozitie.getByJocId(joc.getId());
            DTOPozitie[] pozitiiPropuse = Arrays.stream(pozitiiPropuseA).map(pozitie -> pozitie.makeDtoPozitie()).toArray(DTOPozitie[]::new);

            Duration durata = Duration.between(joc.getTimestampInceput(), joc.getTimestampSfarsit());
            int durataSecunde = (int) durata.getSeconds();

            DTOJocFinalizat dtoJocFinalizat = new DTOJocFinalizat(
                    joc.getGropi(),
                    pozitiiPropuse,
                    joc.getPunctaj(),
                    durataSecunde
            );

            dtoJocFinalizatArrayList.add(dtoJocFinalizat);
        }

        return dtoJocFinalizatArrayList.toArray(new DTOJocFinalizat[0]);
    }
}
