//package srv;
//
//import domain.Jucator;
//import javafx.application.Platform;
//import org.apache.logging.log4j.LogManager;
//import org.apache.logging.log4j.Logger;
//import srv.protocol.event.OnJocSfarsit;
//import srv.protocol.event.OnJocStarted;
//import srv.protocol.event.OnRundaSfarsit;
//import srv.protocol.message.*;
//
//import java.io.IOException;
//import java.io.ObjectInputStream;
//import java.io.ObjectOutputStream;
//import java.net.Socket;
//import java.util.ArrayList;
//import java.util.HashMap;
//import java.util.Map;
//import java.util.concurrent.BlockingQueue;
//import java.util.concurrent.LinkedBlockingQueue;
//
//public class SrvApplicationObjectProxy implements SrvApplication {
//    private static final Logger logger = LogManager.getLogger();
//
//    // connection parameters
//    private String host;
//    private int port;
//
//    // connection
//    private ObjectInputStream input;
//    private ObjectOutputStream output;
//    private Socket connection;
//
//    // events
//    Map<Integer, ArrayList<OnJocStarted>> onJocStartedMap;
//    Map<Integer, ArrayList<OnRundaSfarsit>> onRundaSfarsitMap;
//    Map<Integer, ArrayList<OnJocSfarsit>> onJocSfarsitMap;
//
//    private BlockingQueue<Response> responsesQueue;
//
//    private volatile boolean finished;
//
//
//    public SrvApplicationObjectProxy(String host, int port) {
//        this.onJocStartedMap = new HashMap<>();
//        this.onRundaSfarsitMap = new HashMap<>();
//        this.onJocSfarsitMap = new HashMap<>();
//
//        this.host = host;
//        this.port = port;
//        this.responsesQueue = new LinkedBlockingQueue<>();
//        this.finished = true;
//        openConnection();
//    }
//
//    private class ReaderThread implements Runnable {
//        public void run() {
//            while (!finished) {
//                try {
//                    Object response = input.readObject();
//                    logger.info("Response received " + response);
//                    if (response instanceof ResponseUpdate response1){
//                        handleUpdate(response1);
//                    } else {
//                        try {
//                            responsesQueue.put((Response) response);
//                        } catch (InterruptedException e) {
//                            e.printStackTrace();
//                        }
//                    }
//                } catch (IOException | ClassNotFoundException e) {
//                    logger.error("Reading error " + e);
//                }
//            }
//        }
//    }
//
//    private void openConnection() {
//        if (finished) {
//            try {
//                connection = new Socket(host, port);
//                output = new ObjectOutputStream(connection.getOutputStream());
//                output.flush();
//                input = new ObjectInputStream(connection.getInputStream());
//
//                Thread readerThread = new Thread(new ReaderThread());
//                readerThread.start();
//            } catch (IOException e) {
//                e.printStackTrace();
//            }
//            finished = false;
//        }
//    }
//
//    private void sendRequest(Request request) {
//        try {
//            output.writeObject(request);
//            output.flush();
//        } catch (IOException e) {
//            throw new RuntimeException(e);
//        }
//    }
//
//    private Response readResponse() {
//        Response response = null;
//        try {
//            response = responsesQueue.take();
//        } catch (InterruptedException e) {
//            e.printStackTrace();
//        }
//        return response;
//    }
//
//    private void handleUpdate(ResponseUpdate updateResponse) {
//        if (updateResponse instanceof ResponseUpdateStartJoc responseUpdateStartJoc) {
//            ArrayList<OnJocStarted> onJocStarteds = onJocStartedMap.get(responseUpdateStartJoc.getJocId());
//            if (onJocStarteds != null) {
//                for (OnJocStarted onJocStarted : onJocStarteds) {
//                    Platform.runLater(() -> {
//                        onJocStarted.update(responseUpdateStartJoc.getUpdateStartJoc());
//                    });
//                }
//            }
//        } else if (updateResponse instanceof ResponseUpdateSfarsitRunda responseUpdateSfarsitRunda) {
//            ArrayList<OnRundaSfarsit> onRundaSfarsits = onRundaSfarsitMap.get(responseUpdateSfarsitRunda.getJocId());
//            if (onRundaSfarsits != null) {
//                for (OnRundaSfarsit onRundaSfarsit : onRundaSfarsits) {
//                    Platform.runLater(() -> {
//                        onRundaSfarsit.update(responseUpdateSfarsitRunda.getUpdateSfarsitRunda());
//                    });
//                }
//            }
//        } else if (updateResponse instanceof ResponseUpdateSfarsitJoc updateSfarsitJoc) {
//            ArrayList<OnJocSfarsit> onJocSfarsits = onJocSfarsitMap.get(updateSfarsitJoc.getJocId());
//            if (onJocSfarsits != null) {
//                for (OnJocSfarsit onJocSfarsit : onJocSfarsits) {
//                    Platform.runLater(() -> {
//                        onJocSfarsit.update(updateSfarsitJoc.getUpdateSfarsitJoc());
//                    });
//                }
//            }
//        } else {
//            throw new RuntimeException();
//        }
//    }
//
//    @Override
//    public Jucator logIn(String nume, String parola) throws CredentialeNevalideException {
//        RequestLogIn request = new RequestLogIn(nume, parola);
//        sendRequest(request);
//        Response response = readResponse();
//        if (response instanceof ResponseLogIn response1) {
//            return response1.getJucator();
//        }
//        return null;
//    }
//
//    @Override
//    public void logOut(int jucatorId) {
//        RequestLogOut request = new RequestLogOut(jucatorId);
//        sendRequest(request);
//    }
//
//    @Override
//    public int getJocId() {
//        RequestGetJocId request = new RequestGetJocId();
//        sendRequest(request);
//        Response response = readResponse();
//        if (response instanceof ResponseGetJocId response1) {
//            return response1.getJocId();
//        }
//        throw new RuntimeException();
//    }
//
//    @Override
//    public void jucatorStart(int jucatorId, String cuvant) {
//        RequestJucatorStart request = new RequestJucatorStart(jucatorId, cuvant);
//        sendRequest(request);
//    }
//
//    @Override
//    public void registerOnJocStarted(int jocId, OnJocStarted onJocStarted) {
//        RequestRegisterStartJoc request = new RequestRegisterStartJoc(jocId);
//        sendRequest(request);
//        if (!onJocStartedMap.containsKey(jocId)) {
//            onJocStartedMap.put(jocId, new ArrayList<>());
//        }
//        onJocStartedMap.get(jocId).add(onJocStarted);
//    }
//
//    @Override
//    public void jucatorGhiceste(int jocId, int ghicitorJucatorId, int propunatorJucatorId, char litera) {
//        RequestJucatorGhiceste request = new RequestJucatorGhiceste(jocId, ghicitorJucatorId, propunatorJucatorId, litera);
//        sendRequest(request);
//    }
//
//    @Override
//    public void registerOnRundaSfarsit(int jocId, OnRundaSfarsit onRundaSfarsit) {
//        RequestRegisterSfarsitRunda request = new RequestRegisterSfarsitRunda(jocId);
//        sendRequest(request);
//        if (!onRundaSfarsitMap.containsKey(jocId)) {
//            onRundaSfarsitMap.put(jocId, new ArrayList<>());
//        }
//        onRundaSfarsitMap.get(jocId).add(onRundaSfarsit);
//    }
//
//    @Override
//    public void registerOnJocSfarsit(int jocId, OnJocSfarsit onJocSfarsit) {
//        RequestRegisterSfarsitJoc request = new RequestRegisterSfarsitJoc(jocId);
//        sendRequest(request);
//        if (!onJocSfarsitMap.containsKey(jocId)) {
//            onJocSfarsitMap.put(jocId, new ArrayList<>());
//        }
//        onJocSfarsitMap.get(jocId).add(onJocSfarsit);
//    }
//}
