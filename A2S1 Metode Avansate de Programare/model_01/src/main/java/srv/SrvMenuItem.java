package srv;

import domain.MenuItem;
import repo.RepoMenuItem;

import java.util.Arrays;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;

public class SrvMenuItem {
    RepoMenuItem repoMenuItem;

    public SrvMenuItem(RepoMenuItem repoMenuItem) {
        this.repoMenuItem = repoMenuItem;
    }

    public Map<String, List<MenuItem>> getMenuItemsGroupedByCategory() {
        return Arrays.stream(this.repoMenuItem.getAll())
                .collect(Collectors.groupingBy(menuItem -> menuItem.getCategory()));
    }
}
