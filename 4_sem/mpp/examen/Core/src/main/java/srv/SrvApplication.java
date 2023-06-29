package srv;

import srv.protocol.event.OnJocSfarsit;
import srv.protocol.message.DTOClasamentItem;
import srv.protocol.message.ResponseAlegePozitie;
import srv.protocol.message.ResponseStartJoc;

public interface SrvApplication {
    ResponseStartJoc startJoc(String alias) throws CredentialeNevalideException;
    ResponseAlegePozitie alegePozitie(int jocId, int linie, int coloana);
    DTOClasamentItem[] getClasament();
    void subscribeOnJocSfarsit(OnJocSfarsit onJocSfarsit);
}
