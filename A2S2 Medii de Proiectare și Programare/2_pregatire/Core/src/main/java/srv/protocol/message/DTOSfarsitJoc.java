package srv.protocol.message;

public class DTOSfarsitJoc {
    String indiciu;
    int linieIndiciu;
    int coloanaIndiciu;
    int numarIncercariSau10;
    int pozitieClasament;

    public DTOSfarsitJoc() {

    }

    public String getIndiciu() {
        return indiciu;
    }

    public void setIndiciu(String indiciu) {
        this.indiciu = indiciu;
    }

    public int getLinieIndiciu() {
        return linieIndiciu;
    }

    public void setLinieIndiciu(int linieIndiciu) {
        this.linieIndiciu = linieIndiciu;
    }

    public int getColoanaIndiciu() {
        return coloanaIndiciu;
    }

    public void setColoanaIndiciu(int coloanaIndiciu) {
        this.coloanaIndiciu = coloanaIndiciu;
    }

    public int getNumarIncercariSau10() {
        return numarIncercariSau10;
    }

    public void setNumarIncercariSau10(int numarIncercariSau10) {
        this.numarIncercariSau10 = numarIncercariSau10;
    }

    public int getPozitieClasament() {
        return pozitieClasament;
    }

    public void setPozitieClasament(int pozitieClasament) {
        this.pozitieClasament = pozitieClasament;
    }
}
