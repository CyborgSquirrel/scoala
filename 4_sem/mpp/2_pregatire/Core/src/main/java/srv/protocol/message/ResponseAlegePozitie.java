package srv.protocol.message;

public class ResponseAlegePozitie {
    Float distanta;
    DTOSfarsitJoc dtoSfarsitJoc;

    public ResponseAlegePozitie() {
    }

    public Float getDistanta() {
        return distanta;
    }

    public void setDistanta(Float distanta) {
        this.distanta = distanta;
    }

    public DTOSfarsitJoc getDtoSfarsitJoc() {
        return dtoSfarsitJoc;
    }

    public void setDtoSfarsitJoc(DTOSfarsitJoc dtoSfarsitJoc) {
        this.dtoSfarsitJoc = dtoSfarsitJoc;
    }
}
