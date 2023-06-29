package srv.protocol.event;

import srv.protocol.message.UpdateSfarsitRunda;

@FunctionalInterface
public interface OnRundaSfarsit {
    void update(UpdateSfarsitRunda updateSfarsitRunda);
}
