package srv;

public class SrvManager {
    SrvMenuItem srvMenuItem;
    SrvTable srvTable;
    SrvOrder srvOrder;

    public SrvManager(SrvMenuItem srvMenuItem, SrvTable srvTable, SrvOrder srvOrder) {
        this.srvMenuItem = srvMenuItem;
        this.srvTable = srvTable;
        this.srvOrder = srvOrder;
    }

    public SrvTable getSrvTable() {
        return srvTable;
    }

    public SrvMenuItem getSrvMenuItem() {
        return srvMenuItem;
    }

    public SrvOrder getSrvOrder() {
        return srvOrder;
    }
}
