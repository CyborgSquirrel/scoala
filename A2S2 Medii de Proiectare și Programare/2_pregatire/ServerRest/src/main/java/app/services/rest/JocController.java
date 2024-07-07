//package app.services.rest;
//
//import domain.GhicireLitera;
//import org.springframework.http.HttpStatus;
//import org.springframework.http.ResponseEntity;
//import org.springframework.web.bind.annotation.*;
//import repo.*;
//
//import javax.annotation.PostConstruct;
//
//@CrossOrigin(origins = "http://localhost:3000", maxAge = 3600)
//@RestController
//@RequestMapping("/app/joc")
//public class JocController {
//    RepoJoc repoJoc;
//    RC
//
//    @PostConstruct
//    public void initialize() {
//        RepoManager repoManager = new RepoManager();
//        repoJoc = repoManager.getRepoJoc();
//    }
//
//    @RequestMapping(method = RequestMethod.GET)
//    public ResponseEntity<?> ghicireLitera(@RequestParam int jucatorId, @RequestParam int jucatorId) {
//        GhicireLitera[] ghiciriLitera = repoGhicireLitera.findByJocIdAndGhicitorJucatorId(jocId, jucatorId);
//        return new ResponseEntity<GhicireLitera[]>(ghiciriLitera, HttpStatus.OK);
//    }
//}
