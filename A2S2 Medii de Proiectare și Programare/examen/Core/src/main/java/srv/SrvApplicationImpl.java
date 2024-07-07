package srv;

import domain.DTOPozitie;
import domain.Joc;
import domain.Jucator;
import domain.Pozitie;
import repo.*;
import srv.protocol.event.OnJocSfarsit;
import srv.protocol.message.DTOClasamentItem;
import srv.protocol.message.DTOSfarsitJoc;
import srv.protocol.message.ResponseAlegePozitie;
import srv.protocol.message.ResponseStartJoc;

import java.time.Duration;
import java.time.LocalDateTime;
import java.time.Period;
import java.util.*;

public class SrvApplicationImpl implements SrvApplication {
    RepoJucator repoJucator;
    RepoJoc repoJoc;
    RepoPozitie repoPozitie;
    ArrayList<OnJocSfarsit> onJocSfarsitArrayList;

    public SrvApplicationImpl(RepoJucator repoJucator,
                              RepoJoc repoJoc,
                              RepoPozitie repoPozitie) {
        this.repoJucator = repoJucator;
        this.repoJoc = repoJoc;
        this.repoPozitie = repoPozitie;

        this.onJocSfarsitArrayList = new ArrayList<>();
    }

    @Override
    public ResponseStartJoc startJoc(String alias) throws CredentialeNevalideException {
        Jucator jucator = repoJucator.findByAlias(alias);

        if (jucator == null) {
            throw new CredentialeNevalideException();
        }

        Random random = new Random();

        ArrayList<DTOPozitie> toateGropile = new ArrayList<>();
        for (int linie = 0; linie < 4; ++linie) {
            for (int coloana = 0; coloana < 4; ++coloana) {
                toateGropile.add(new DTOPozitie(linie, coloana));
            }
        }

        ArrayList<DTOPozitie> groapaArrayList = new ArrayList<>();
        for (int i = 0; i < 5; ++i) {
            int groapaIndex = random.nextInt(toateGropile.size());
            groapaArrayList.add(toateGropile.get(groapaIndex));
            toateGropile.remove(groapaIndex);
        }

        DTOPozitie[] gropi = groapaArrayList.toArray(new DTOPozitie[0]);

        Joc joc = new Joc(jucator.getId(),
                LocalDateTime.now(),
                null,
                gropi,
                0,
                false);
        try {
            repoJoc.store(joc);
        } catch (IdAlreadyExistsException e) {
            throw new RuntimeException(e);
        }

        ResponseStartJoc responseStartJoc = new ResponseStartJoc(jucator, joc.getId());

        return responseStartJoc;
    }


    @Override
    public void subscribeOnJocSfarsit(OnJocSfarsit onJocSfarsit) {
        onJocSfarsitArrayList.add(onJocSfarsit);
    }

    @Override
    public ResponseAlegePozitie alegePozitie(int jocId, int linie, int coloana) {
        ResponseAlegePozitie responseAlegePozitie = new ResponseAlegePozitie();

        Joc joc;
        try {
            joc = repoJoc.find(jocId);
        } catch (IdNotFoundException e) {
            throw new RuntimeException(e);
        }

        boolean wasFinalizat = joc.isFinalizat();

        // verifica daca e groapa
        // daca da => response sfarsit joc
        // daca nu => actualizeaza punctaj
        // ia si toate miscarile pt joc si verifica daca sunt mai multe de 4
        // linia trebuie sa fie pozitii.size()

        Pozitie[] pozities = repoPozitie.getByJocId(jocId);
        int pozitieSize = pozities.length;

        if (pozitieSize == linie) {
            Pozitie pozitie = new Pozitie(jocId, linie, coloana);
            try {
                repoPozitie.store(pozitie);
            } catch (IdAlreadyExistsException e) {
                throw new RuntimeException(e);
            }

            boolean nimeritGroapa = false;

            DTOPozitie dtoPozitie = pozitie.makeDtoPozitie();
            for (DTOPozitie dtoPozitieGroapa : joc.getGropi()) {
                if (Objects.equals(dtoPozitieGroapa, dtoPozitie)) {
                    nimeritGroapa = true;
                    break;
                }
            }

            if (nimeritGroapa) {
                joc.setFinalizat(true);
            } else {
                joc.setPunctaj(joc.getPunctaj() + linie+1);
            }

            if (pozitieSize >= 3) {
                joc.setFinalizat(true);
            }
        }

        if (joc.isFinalizat()) {
            DTOClasamentItem[] clasament = getClasament();

            int clasamentIndex = 0;
            for (DTOClasamentItem dtoClasamentItem : clasament) {
                clasamentIndex += 1;
                if (dtoClasamentItem.getJocId() == joc.getId()) {
                    break;
                }
            }

            joc.setTimestampSfarsit(LocalDateTime.now());

            try {
                repoJoc.update(jocId, joc);
            } catch (IdNotFoundException e) {
                throw new RuntimeException(e);
            }

            DTOSfarsitJoc dtoSfarsitJoc = new DTOSfarsitJoc(
                    joc.getPunctaj(),
                    joc.getGropi(),
                    clasamentIndex
            );

            responseAlegePozitie.setDtoSfarsitJoc(dtoSfarsitJoc);
        } else {
            try {
                repoJoc.update(jocId, joc);
            } catch (IdNotFoundException e) {
                throw new RuntimeException(e);
            }
        }

        if (!wasFinalizat && joc.isFinalizat()) {
            for (OnJocSfarsit onJocSfarsit : onJocSfarsitArrayList) {
                onJocSfarsit.update();
            }
        }

        return responseAlegePozitie;
    }

    @Override
    public DTOClasamentItem[] getClasament() {
        ArrayList<DTOClasamentItem> clasamentItemArrayList = new ArrayList<>();
        for (Joc joc : repoJoc.getAll()) {
            // TODO: Get finalizate.
            if (!joc.isFinalizat()) continue;

            if (joc.getTimestampSfarsit() == null) continue;

            Jucator jucator;
            try {
                jucator = repoJucator.find(joc.getJucatorId());
            } catch (IdNotFoundException e) {
                throw new RuntimeException(e);
            }

            Duration durata = Duration.between(joc.getTimestampInceput(), joc.getTimestampSfarsit());
            int durataSecunde = (int) durata.getSeconds();

            DTOClasamentItem dtoClasamentItem = new DTOClasamentItem(
                    jucator.getAlias(),
                    joc.getPunctaj(),
                    durataSecunde,
                    joc.getId()
            );

            clasamentItemArrayList.add(dtoClasamentItem);
        }

        clasamentItemArrayList.sort(
                Comparator.comparing(DTOClasamentItem::getPuncte, Comparator.reverseOrder())
                        .thenComparing(DTOClasamentItem::getDurataSecunde, Comparator.reverseOrder())
        );

        return clasamentItemArrayList.toArray(new DTOClasamentItem[0]);
    }
}
