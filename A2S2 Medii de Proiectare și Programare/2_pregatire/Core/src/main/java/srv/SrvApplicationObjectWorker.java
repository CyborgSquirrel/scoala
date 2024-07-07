//package srv;
//
//import domain.Jucator;
//import org.apache.logging.log4j.LogManager;
//import org.apache.logging.log4j.Logger;
//import srv.protocol.message.*;
//
//import java.io.IOException;
//import java.io.ObjectInputStream;
//import java.io.ObjectOutputStream;
//import java.net.Socket;
//import java.util.HashSet;
//import java.util.Set;
//
//public class SrvApplicationObjectWorker implements Runnable {
//    private static final Logger logger = LogManager.getLogger();
//
//    private SrvApplication srvApplication;
//
//    // connection
//    private ObjectInputStream input;
//    private ObjectOutputStream output;
//    private Socket connection;
//
//    // event
//    private Set<Integer> startJocRegistered;
//    private Set<Integer> sfarsitRundaRegistered;
//    private Set<Integer> sfarsitJocRegistered;
//
//    private volatile boolean connected;
//
//    public SrvApplicationObjectWorker(SrvApplication srvApplication, Socket connection) {
//        this.startJocRegistered = new HashSet<>();
//        this.sfarsitRundaRegistered = new HashSet<>();
//        this.sfarsitJocRegistered = new HashSet<>();
//
//        this.srvApplication = srvApplication;
//        this.connection = connection;
//        try {
//            output = new ObjectOutputStream(connection.getOutputStream());
//            output.flush();
//            input = new ObjectInputStream(connection.getInputStream());
//            connected = true;
//        } catch (IOException e) {
//            e.printStackTrace();
//        }
//    }
//
//    public void run() {
//        while (connected) {
//            try {
//                Object request = input.readObject();
//                Response response = handleRequest((Request) request);
//                if (response != null){
//                    sendResponse(response);
//                }
//            } catch (IOException | ClassNotFoundException e) {
//                e.printStackTrace();
//            }
//            try {
//                Thread.sleep(1000);
//            } catch (InterruptedException e) {
//                e.printStackTrace();
//            }
//        }
//        try {
//            input.close();
//            output.close();
//            connection.close();
//        } catch (IOException e) {
//            logger.error(e);
//        }
//    }
//    private Response handleRequest(Request request) {
//        Response response = null;
//
//        if (request instanceof RequestLogIn requestLogIn) {
//            try {
//                Jucator jucator = srvApplication.logIn(requestLogIn.getNume(), requestLogIn.getParola());
//                response = new ResponseLogIn(jucator);
//            } catch (CredentialeNevalideException e) {
//                throw new RuntimeException(e);
//            }
//        } else if (request instanceof RequestLogOut requestLogOut) {
//            srvApplication.logOut(requestLogOut.getJucatorId());
//        } else if (request instanceof RequestGetJocId requestGetJocId) {
//            int jocId = srvApplication.getJocId();
//            response = new ResponseGetJocId(jocId);
//        } else if (request instanceof RequestJucatorStart requestJucatorStart) {
//            srvApplication.jucatorStart(requestJucatorStart.getJucatorId(), requestJucatorStart.getCuvant());
//        } else if (request instanceof RequestJucatorGhiceste requestJucatorGhiceste) {
//            srvApplication.jucatorGhiceste(requestJucatorGhiceste.getJocId(),
//                    requestJucatorGhiceste.getGhicitorJucatorId(),
//                    requestJucatorGhiceste.getPropunatorJucatorId(),
//                    requestJucatorGhiceste.getLitera());
//        } else if (request instanceof RequestRegisterStartJoc requestRegisterStartJoc) {
//            int jocId = requestRegisterStartJoc.getJocId();
//            if (!this.startJocRegistered.contains(jocId)) {
//                this.startJocRegistered.add(jocId);
//                srvApplication.registerOnJocStarted(
//                        jocId,
//                        updateStartJoc -> {
//                            ResponseUpdateStartJoc responseUpdateStartJoc = new ResponseUpdateStartJoc(jocId, updateStartJoc);
//                            try {
//                                sendResponse(responseUpdateStartJoc);
//                            } catch (IOException e) {
//                                throw new RuntimeException(e);
//                            }
//                        }
//                );
//            }
//        } else if (request instanceof RequestRegisterSfarsitRunda requestRegisterSfarsitRunda) {
//            int jocId = requestRegisterSfarsitRunda.getJocId();
//            if (!this.sfarsitRundaRegistered.contains(jocId)) {
//                this.sfarsitRundaRegistered.add(jocId);
//                srvApplication.registerOnRundaSfarsit(
//                        jocId,
//                        updateSfarsitRunda -> {
//                            ResponseUpdateSfarsitRunda responseUpdateSfarsitRunda = new ResponseUpdateSfarsitRunda(jocId, updateSfarsitRunda);
//                            try {
//                                sendResponse(responseUpdateSfarsitRunda);
//                            } catch (IOException e) {
//                                throw new RuntimeException(e);
//                            }
//                        }
//                );
//            }
//        } else if (request instanceof RequestRegisterSfarsitJoc requestRegisterSfarsitJoc) {
//            int jocId = requestRegisterSfarsitJoc.getJocId();
//            if (!this.sfarsitJocRegistered.contains(jocId)) {
//                this.sfarsitJocRegistered.add(jocId);
//                srvApplication.registerOnJocSfarsit(
//                        jocId,
//                        updateSfarsitJoc -> {
//                            ResponseUpdateSfarsitJoc responseUpdateSfarsitJoc = new ResponseUpdateSfarsitJoc(jocId, updateSfarsitJoc);
//                            try {
//                                sendResponse(responseUpdateSfarsitJoc);
//                            } catch (IOException e) {
//                                throw new RuntimeException(e);
//                            }
//                        }
//                );
//            }
//        } else {
//            throw new RuntimeException();
//        }
//
//        return response;
//    }
//
//    private void sendResponse(Response response) throws IOException {
//        synchronized (output) {
//            output.writeObject(response);
//            output.flush();
//        }
//    }
//}
