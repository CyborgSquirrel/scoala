package srv;

import domain.Jucator;
import srv.protocol.event.OnJocSfarsit;
import srv.protocol.event.OnJocStarted;
import srv.protocol.event.OnRundaSfarsit;

public interface SrvApplication {
    Jucator logIn(String nume, String parola) throws CredentialeNevalideException;
    void logOut(int jucatorId);
    int getJocId();

    void jucatorStart(int jucatorId, String cuvant);
    void registerOnJocStarted(int jocId, OnJocStarted onJocStarted);

    void jucatorGhiceste(int jocId,
                         int ghicitorJucatorId,
                         int propunatorJucatorId,
                         char litera);
    void registerOnRundaSfarsit(int jocId, OnRundaSfarsit onRundaSfarsit);
    void registerOnJocSfarsit(int jocId, OnJocSfarsit onJocSfarsit);
}
