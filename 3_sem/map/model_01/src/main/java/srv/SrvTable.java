package srv;

import domain.Table;
import repo.RepoTable;

public class SrvTable {
    RepoTable repoTable;

    public SrvTable(RepoTable repoTable) {
        this.repoTable = repoTable;
    }

    public Table[] getAll() {
        return repoTable.getAll();
    }
}
