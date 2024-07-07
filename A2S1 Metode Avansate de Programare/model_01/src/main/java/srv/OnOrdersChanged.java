package srv;

import domain.MenuItem;
import domain.Order;

import java.util.ArrayList;

@FunctionalInterface
public interface OnOrdersChanged {
    void apply(Order[] orders);
}
