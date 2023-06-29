package srv.protocol.event;

import srv.protocol.message.UpdateStartJoc;

@FunctionalInterface
public interface OnJocStarted {
    void update(UpdateStartJoc updateStartJoc);
}
