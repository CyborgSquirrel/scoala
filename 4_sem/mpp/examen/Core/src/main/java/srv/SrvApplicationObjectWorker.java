package srv;

import domain.Jucator;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import srv.protocol.message.*;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.Socket;
import java.util.HashSet;
import java.util.Set;

public class SrvApplicationObjectWorker implements Runnable {
    private static final Logger logger = LogManager.getLogger();

    private SrvApplication srvApplication;

    // connection
    private ObjectInputStream input;
    private ObjectOutputStream output;
    private Socket connection;

    private volatile boolean connected;

    public SrvApplicationObjectWorker(SrvApplication srvApplication, Socket connection) {
        this.srvApplication = srvApplication;
        this.connection = connection;

        this.srvApplication.subscribeOnJocSfarsit(() -> {
            ResponseUpdateSfarsitJoc responseUpdateSfarsitJoc = new ResponseUpdateSfarsitJoc();
            try {
                sendResponse(responseUpdateSfarsitJoc);
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        });

        try {
            output = new ObjectOutputStream(connection.getOutputStream());
            output.flush();
            input = new ObjectInputStream(connection.getInputStream());
            connected = true;
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void run() {
        while (connected) {
            try {
                Object request = input.readObject();
                Response response = handleRequest((Request) request);
                if (response != null){
                    sendResponse(response);
                }
            } catch (IOException | ClassNotFoundException e) {
                e.printStackTrace();
            }
            try {
                Thread.sleep(1000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
        try {
            input.close();
            output.close();
            connection.close();
        } catch (IOException e) {
            logger.error(e);
        }
    }
    private Response handleRequest(Request request) {
        Response response = null;

        if (request instanceof RequestStartJoc requestStartJoc) {
            try {
                ResponseStartJoc responseStartJoc = srvApplication.startJoc(requestStartJoc.getAlias());
                response = responseStartJoc;
            } catch (CredentialeNevalideException e) {
                throw new RuntimeException(e);
            }
        } else if (request instanceof RequestAlegePozitie requestAlegePozitie) {
            ResponseAlegePozitie responseAlegePozitie = srvApplication.alegePozitie(requestAlegePozitie.getJocId(), requestAlegePozitie.getLinie(), requestAlegePozitie.getColoana());
            response = responseAlegePozitie;
        } else if (request instanceof RequestGetClasament requestGetClasament) {
            DTOClasamentItem[] clasament = srvApplication.getClasament();
            response = new ResponseGetClasament(clasament);
        } else {
            throw new RuntimeException();
        }

        return response;
    }

    private void sendResponse(Response response) throws IOException {
        synchronized (output) {
            output.writeObject(response);
            output.flush();
        }
    }
}
