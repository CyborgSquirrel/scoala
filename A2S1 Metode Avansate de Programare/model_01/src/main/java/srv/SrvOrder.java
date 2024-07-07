package srv;

import domain.MenuItem;
import domain.Order;
import domain.OrderStatus;
import domain.Table;
import repo.ItemAlreadyExistsException;
import repo.RepoOrder;

import java.time.LocalDateTime;
import java.util.ArrayList;

public class SrvOrder {
    RepoOrder repoOrder;

    ArrayList<OnOrdersChanged> onOrdersChangedCallbacks = new ArrayList<>();

    public SrvOrder(RepoOrder repoOrder) {
        this.repoOrder = repoOrder;
    }

    public void addOnOrdersChangedCallback(OnOrdersChanged callback) {
        onOrdersChangedCallbacks.add(callback);
    }

    private void onOrdersChanged() {
        Order[] orders = repoOrder.getAll();
        for (OnOrdersChanged onOrdersChangedCallback : onOrdersChangedCallbacks) {
            onOrdersChangedCallback.apply(orders);
        }
    }

    public void makeOrder(Table table, ArrayList<MenuItem> menuItems) {
        if (!menuItems.isEmpty()) {
            try {
                repoOrder.store(new Order(0, table, menuItems, LocalDateTime.now(), OrderStatus.PLACED));
            } catch (ItemAlreadyExistsException e) {
                throw new RuntimeException(e);
            }
            onOrdersChanged();
        }
    }

    public Order[] getOrders() {
        return repoOrder.getAll();
    }
}
