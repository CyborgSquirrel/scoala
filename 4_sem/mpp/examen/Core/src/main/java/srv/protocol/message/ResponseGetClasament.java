package srv.protocol.message;

public class ResponseGetClasament extends Response {
    DTOClasamentItem[] clasamentItems;

    public ResponseGetClasament(DTOClasamentItem[] clasamentItems) {
        this.clasamentItems = clasamentItems;
    }

    public DTOClasamentItem[] getClasamentItems() {
        return clasamentItems;
    }

    public void setClasamentItems(DTOClasamentItem[] clasamentItems) {
        this.clasamentItems = clasamentItems;
    }
}
