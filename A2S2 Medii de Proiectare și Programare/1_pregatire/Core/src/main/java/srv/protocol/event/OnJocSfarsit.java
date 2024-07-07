package srv.protocol.event;

import srv.protocol.message.UpdateSfarsitJoc;

@FunctionalInterface
public interface OnJocSfarsit {
    void update(UpdateSfarsitJoc updateSfarsitJoc);
}
