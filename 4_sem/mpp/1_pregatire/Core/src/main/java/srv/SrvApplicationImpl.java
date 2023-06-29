package srv;

import domain.GhicireLitera;
import domain.GhicireLiteraId;
import domain.Joc;
import domain.Jucator;
import repo.*;
import srv.protocol.event.OnJocSfarsit;
import srv.protocol.event.OnJocStarted;
import srv.protocol.event.OnRundaSfarsit;
import srv.protocol.message.*;

import java.util.*;

public class SrvApplicationImpl implements SrvApplication {
    RepoJucator repoJucator;
    RepoJoc repoJoc;
    RepoGhicireLitera repoGhicireLitera;

    Joc joc;
    Map<Integer, ArrayList<OnJocStarted>> onJocStartedMap;
    Map<Integer, ArrayList<OnRundaSfarsit>> onRundaSfarsitMap;
    Map<Integer, ArrayList<OnJocSfarsit>> onJocSfarsitMap;

    Map<Integer, Integer> jocIdToRunda;

    public SrvApplicationImpl(RepoJucator repoJucator,
                              RepoJoc repoJoc,
                              RepoGhicireLitera repoGhicireLitera) {
        this.repoJucator = repoJucator;
        this.repoJoc = repoJoc;
        this.repoGhicireLitera = repoGhicireLitera;

        this.onJocStartedMap = new HashMap<>();
        this.onRundaSfarsitMap = new HashMap<>();
        this.onJocSfarsitMap = new HashMap<>();
        this.jocIdToRunda = new HashMap<>();

        // TODO: Get empty joc from repo, if it exists.
        this.joc = new Joc();
        try {
            repoJoc.store(joc);
        } catch (IdAlreadyExistsException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    public Jucator logIn(String nume, String parola) throws CredentialeNevalideException {
        Jucator jucator = repoJucator.findByNume(nume);

        if (jucator == null) {
            throw new CredentialeNevalideException();
        }

        if (Objects.equals(jucator.getParola(), parola)) {
            return jucator;
        } else {
            throw new CredentialeNevalideException();
        }
    }

    @Override
    public void logOut(int jucatorId) {
        Integer jucatorIndex = joc.getJucatorIndexById(jucatorId);
        if (jucatorIndex != null) {
            joc.removeJucatorByIndex(jucatorIndex);
        }
    }

    @Override
    public int getJocId() {
        return joc.getId();
    }

    @Override
    public void jucatorStart(int jucatorId, String cuvant) {
        joc.addJucator(jucatorId, cuvant);
        try {
            repoJoc.update(joc.getId(), joc);
        } catch (IdNotFoundException e) {
            throw new RuntimeException(e);
        }

        // start joc
        if (joc.getJucatoriCount() >= 3) {
            jocIdToRunda.put(joc.getId(), 0);

            // trimite update-uri
            ArrayList<DTOStartJocJucator> jucatori = new ArrayList<>();
            for (int i = 0; i < 3; ++i) {
                try {
                    jucatori.add(new DTOStartJocJucator(
                            joc.getJucatorId(i),
                            joc.getJucatorCuvant(i).length(),
                            repoJucator.find(joc.getJucatorId(i)).getNume()));
                } catch (IdNotFoundException e) {
                    throw new RuntimeException(e);
                }
            }
            UpdateStartJoc updateStartJoc = new UpdateStartJoc(jucatori.toArray(new DTOStartJocJucator[0]));

            ArrayList<OnJocStarted> onJocStarteds = onJocStartedMap.get(joc.getId());
            if (onJocStarteds != null) {
                for (OnJocStarted onJocStarted : onJocStarteds) {
                    onJocStarted.update(updateStartJoc);
                }
            }
            onJocStartedMap.remove(joc.getId());

            this.joc = new Joc();
            try {
                repoJoc.store(joc);
            } catch (IdAlreadyExistsException e) {
                throw new RuntimeException(e);
            }
        }
    }

    @Override
    public void registerOnJocStarted(int jocId, OnJocStarted onJocStarted) {
        if (!onJocStartedMap.containsKey(jocId)) {
            onJocStartedMap.put(jocId, new ArrayList<>());
        }
        onJocStartedMap.get(jocId).add(onJocStarted);
    }

    @Override
    public void jucatorGhiceste(int jocId,
                                int ghicitorJucatorId,
                                int propunatorJucatorId,
                                char litera) {
        // TODO: Nu lasa sa ghiceasca aceeasi litera.
        Joc joc;
        try {
            joc = repoJoc.find(jocId);
        } catch (IdNotFoundException e) {
            throw new RuntimeException(e);
        }

        int punctaj = 0;
        String cuvant = joc.getJucatorCuvant(joc.getJucatorIndexById(propunatorJucatorId));
        for (int i = 0; i < cuvant.length(); ++i) {
            if (cuvant.charAt(i) == litera) {
                punctaj += 1;
            }
        }

        int runda = jocIdToRunda.get(jocId);
        GhicireLiteraId ghicireLiteraId = new GhicireLiteraId(jocId, runda, ghicitorJucatorId);
        GhicireLitera ghicireLitera = new GhicireLitera(ghicireLiteraId, propunatorJucatorId, litera, punctaj);
        try {
            repoGhicireLitera.store(ghicireLitera);
        } catch (IdAlreadyExistsException e) {
            throw new RuntimeException(e);
        }

        GhicireLitera[] ghiciriRunda = repoGhicireLitera.findByJocIdAndRunda(jocId, runda);
        if (ghiciriRunda.length >= 3) {
            runda += 1;
            jocIdToRunda.put(jocId, runda);

            if (runda >= 3) {
                // fa update
                ArrayList<DTOClasamentItem> clasament = new ArrayList<>();
                for (int i = 0; i < 3; ++i) {
                    int jucatorId = joc.getJucatorId(i);
                    int jucatorPunctaj = Arrays.stream(repoGhicireLitera.findByJocIdAndGhicitorJucatorId(jocId, jucatorId))
                            .mapToInt(ghicireLitera1 -> ghicireLitera1.getPunctaj())
                            .sum();
                    String jucatorNume;
                    try {
                        jucatorNume = repoJucator.find(jucatorId).getNume();
                    } catch (IdNotFoundException e) {
                        throw new RuntimeException(e);
                    }
                    DTOClasamentItem DTOClasamentItem = new DTOClasamentItem(jucatorId, jucatorNume, jucatorPunctaj);
                    clasament.add(DTOClasamentItem);
                }
                clasament.sort(Comparator.comparing(DTOClasamentItem -> DTOClasamentItem.getPunctaj(), Comparator.reverseOrder()));
                UpdateSfarsitJoc updateSfarsitJoc = new UpdateSfarsitJoc(clasament.toArray(new DTOClasamentItem[0]));

                // trimite update
                var onJocSfarsits = onJocSfarsitMap.get(jocId);
                if (onJocSfarsits != null) {
                    for (OnJocSfarsit onJocSfarsit : onJocSfarsits) {
                        onJocSfarsit.update(updateSfarsitJoc);
                    }
                }

                // sterge chestii
                jocIdToRunda.remove(jocId);
                onJocSfarsitMap.remove(jocId);
                onJocStartedMap.remove(jocId);
                onRundaSfarsitMap.remove(jocId);
            } else {
                // fa update
                ArrayList<DTOJucatorUpdate> jucatorIdToUpdate = new ArrayList<>();
                for (GhicireLitera ghicireLitera1 : ghiciriRunda) {
                    ArrayList<Integer> positions = new ArrayList<>();

                    char litera1 = ghicireLitera1.getLitera();
                    String cuvant1 = joc.getJucatorCuvant(joc.getJucatorIndexById(ghicireLitera1.getPropunatorJucatorId()));
                    for (int i = 0; i < cuvant1.length(); ++i) {
                        if (cuvant1.charAt(i) == litera1) {
                            positions.add(i);
                        }
                    }

                    DTOJucatorUpdate DTOJucatorUpdate = new DTOJucatorUpdate(
                            ghicireLitera1.getId().getGhicitorJucatorId(),
                            ghicireLitera1.getPropunatorJucatorId(),
                            ghicireLitera1.getPunctaj(),
                            litera1,
                            positions.toArray(new Integer[0]));
                    jucatorIdToUpdate.add(DTOJucatorUpdate);
                }
                UpdateSfarsitRunda updateSfarsitRunda = new UpdateSfarsitRunda(jucatorIdToUpdate.toArray(new DTOJucatorUpdate[0]));

                // trimite update
                var onRundaSfarsits = onRundaSfarsitMap.get(jocId);
                if (onRundaSfarsits != null) {
                    for (OnRundaSfarsit onRundaSfarsit : onRundaSfarsits) {
                        onRundaSfarsit.update(updateSfarsitRunda);
                    }
                }
            }
        }
    }

    @Override
    public void registerOnRundaSfarsit(int jocId, OnRundaSfarsit onRundaSfarsit) {
        if (!onRundaSfarsitMap.containsKey(jocId)) {
            onRundaSfarsitMap.put(jocId, new ArrayList<>());
        }
        onRundaSfarsitMap.get(jocId).add(onRundaSfarsit);
    }

    @Override
    public void registerOnJocSfarsit(int jocId, OnJocSfarsit onJocSfarsit) {
        if (!onJocSfarsitMap.containsKey(jocId)) {
            onJocSfarsitMap.put(jocId, new ArrayList<>());
        }
        onJocSfarsitMap.get(jocId).add(onJocSfarsit);
    }
}
