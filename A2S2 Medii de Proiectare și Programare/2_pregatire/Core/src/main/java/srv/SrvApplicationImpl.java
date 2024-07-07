package srv;

import domain.Configuratie;
import domain.Joc;
import domain.Jucator;
import repo.*;
import srv.protocol.event.OnJocSfarsit;
import srv.protocol.message.DTOClasamentItem;
import srv.protocol.message.DTOSfarsitJoc;
import srv.protocol.message.ResponseAlegePozitie;
import srv.protocol.message.ResponseStartJoc;

import java.time.LocalDateTime;
import java.util.*;

public class SrvApplicationImpl implements SrvApplication {
    RepoJucator repoJucator;
    RepoJoc repoJoc;
    RepoConfiguratie repoConfiguratie;
    ArrayList<OnJocSfarsit> onJocSfarsitArrayList;

//    Map<Integer, JocState> jocStateMap;

    public SrvApplicationImpl(RepoJucator repoJucator,
                              RepoJoc repoJoc,
                              RepoConfiguratie repoConfiguratie) {
        this.repoJucator = repoJucator;
        this.repoJoc = repoJoc;
        this.repoConfiguratie = repoConfiguratie;

        this.onJocSfarsitArrayList = new ArrayList<>();

//        this.jocStateMap = new HashMap<>();
    }

    @Override
    public ResponseStartJoc startJoc(String alias) throws CredentialeNevalideException {
        Jucator jucator = repoJucator.findByAlias(alias);

        if (jucator == null) {
            throw new CredentialeNevalideException();
        }

        Configuratie[] configuraties = repoConfiguratie.getAll();
        Random random = new Random();
        int configuratieIndex = random.nextInt(configuraties.length);

        Configuratie configuratie = configuraties[configuratieIndex];

        Joc joc = new Joc(jucator.getId(), configuratie.getId(), 0, LocalDateTime.now(), false, false);
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
        DTOSfarsitJoc dtoSfarsitJoc = new DTOSfarsitJoc();

        Joc joc;
        try {
            joc = repoJoc.find(jocId);
        } catch (IdNotFoundException e) {
            throw new RuntimeException(e);
        }

        boolean wasFinalizat = joc.isFinalizat();

        Configuratie configuratie;
        try {
            configuratie = repoConfiguratie.find(joc.getConfiguratieId());
        } catch (IdNotFoundException e) {
            throw new RuntimeException(e);
        }

        if (!joc.isFinalizat()) {
            if (configuratie.getLinie() == linie && configuratie.getColoana() == coloana) {
                joc.setFinalizat(true);
                joc.setGhicit(true);
            } else {
                float deltaLinie = configuratie.getLinie() - linie;
                float deltaColoana = configuratie.getColoana() - coloana;

                float distanta = (float) Math.sqrt(deltaLinie*deltaLinie + deltaColoana*deltaColoana);
                responseAlegePozitie.setDistanta(distanta);
            }

            joc.setIncercari(joc.getIncercari() + 1);

            if (joc.getIncercari() >= 5) {
                joc.setFinalizat(true);
            }
        }

        if (joc.isFinalizat()) {
            dtoSfarsitJoc.setPozitieClasament(0);
            dtoSfarsitJoc.setLinieIndiciu(configuratie.getLinie());
            dtoSfarsitJoc.setColoanaIndiciu(configuratie.getColoana());
            if (joc.isGhicit()) {
                dtoSfarsitJoc.setIndiciu(configuratie.getIndiciu());
                dtoSfarsitJoc.setNumarIncercariSau10(joc.getIncercari());
            } else {
                dtoSfarsitJoc.setNumarIncercariSau10(10);
            }

            responseAlegePozitie.setDtoSfarsitJoc(dtoSfarsitJoc);
        }

        try {
            repoJoc.update(joc.getId(), joc);
        } catch (IdNotFoundException e) {
            throw new RuntimeException(e);
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
            Jucator jucator;
            try {
                jucator = repoJucator.find(joc.getJucatorId());
            } catch (IdNotFoundException e) {
                throw new RuntimeException(e);
            }

            String indiciu = "";
            if (joc.isGhicit()) {
                Configuratie configuratie;
                try {
                    configuratie = repoConfiguratie.find(joc.getConfiguratieId());
                } catch (IdNotFoundException e) {
                    throw new RuntimeException(e);
                }
                indiciu = configuratie.getIndiciu();
            }

            DTOClasamentItem dtoClasamentItem = new DTOClasamentItem(jucator.getAlias(),
                    joc.getTimestampInceput(),
                    joc.getIncercari(),
                    indiciu);
            clasamentItemArrayList.add(dtoClasamentItem);
        }

        return clasamentItemArrayList.toArray(new DTOClasamentItem[0]);
    }
}
