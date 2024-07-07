package srv;

import domain.Jucator;
import javafx.application.Platform;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import srv.protocol.event.OnJocSfarsit;
import srv.protocol.message.*;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.Socket;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingQueue;

public class SrvApplicationObjectProxy implements SrvApplication {
    private static final Logger logger = LogManager.getLogger();

    // connection parameters
    private String host;
    private int port;

    // connection
    private ObjectInputStream input;
    private ObjectOutputStream output;
    private Socket connection;


    // events
    ArrayList<OnJocSfarsit> onJocSfarsitArrayList;

    private BlockingQueue<Response> responsesQueue;

    private volatile boolean finished;


    public SrvApplicationObjectProxy(String host, int port) {
        this.onJocSfarsitArrayList = new ArrayList<>();

        this.host = host;
        this.port = port;
        this.responsesQueue = new LinkedBlockingQueue<>();
        this.finished = true;
        openConnection();
    }

    private class ReaderThread implements Runnable {
        public void run() {
            while (!finished) {
                try {
                    Object response = input.readObject();
                    logger.info("Response received " + response);
                    if (response instanceof ResponseUpdate response1){
                        handleUpdate(response1);
                    } else {
                        try {
                            responsesQueue.put((Response) response);
                        } catch (InterruptedException e) {
                            e.printStackTrace();
                        }
                    }
                } catch (IOException | ClassNotFoundException e) {
                    logger.error("Reading error " + e);
                }
            }
        }
    }

    private void openConnection() {
        if (finished) {
            try {
                connection = new Socket(host, port);
                output = new ObjectOutputStream(connection.getOutputStream());
                output.flush();
                input = new ObjectInputStream(connection.getInputStream());

                Thread readerThread = new Thread(new ReaderThread());
                readerThread.start();
            } catch (IOException e) {
                e.printStackTrace();
            }
            finished = false;
        }
    }

    private void sendRequest(Request request) {
        try {
            output.writeObject(request);
            output.flush();
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    private Response readResponse() {
        Response response = null;
        try {
            response = responsesQueue.take();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        return response;
    }

    private void handleUpdate(ResponseUpdate updateResponse) {
        if (updateResponse instanceof ResponseUpdateSfarsitJoc responseUpdateSfarsitJoc) {
            for (OnJocSfarsit onJocSfarsit : onJocSfarsitArrayList) {
                Platform.runLater(() -> {
                    onJocSfarsit.update();
                });
            }
        } else {
            throw new RuntimeException();
        }
    }

    @Override
    public ResponseStartJoc startJoc(String alias) throws CredentialeNevalideException {
        RequestStartJoc requestStartJoc = new RequestStartJoc(alias);
        sendRequest(requestStartJoc);
        Response response = readResponse();
        if (response instanceof ResponseStartJoc responseStartJoc) {
            return responseStartJoc;
        }
        return null;
    }

    @Override
    public ResponseAlegePozitie alegePozitie(int jocId, int linie, int coloana) {
        RequestAlegePozitie requestAlegePozitie = new RequestAlegePozitie(jocId, linie, coloana);
        sendRequest(requestAlegePozitie);
        Response response = readResponse();
        if (response instanceof ResponseAlegePozitie responseAlegePozitie) {
            return responseAlegePozitie;
        }
        throw new RuntimeException();
    }

    @Override
    public DTOClasamentItem[] getClasament() {
        RequestGetClasament requestGetClasament = new RequestGetClasament();
        sendRequest(requestGetClasament);
        Response response = readResponse();
        if (response instanceof ResponseGetClasament responseGetClasament) {
            return responseGetClasament.getClasamentItems();
        }
        throw new RuntimeException();
    }

    @Override
    public void subscribeOnJocSfarsit(OnJocSfarsit onJocSfarsit) {
        onJocSfarsitArrayList.add(onJocSfarsit);
    }
}
