package srv;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.rmi.ServerException;

public class SrvApplicationConcurrentObjectServer {
    private int port;
    private ServerSocket server = null;
    private SrvApplication srvApplication;

    public SrvApplicationConcurrentObjectServer(int port, SrvApplication srvApplication){
        this.port = port;
        this.srvApplication = srvApplication;
    }

    public void start() throws ServerException {
        try {
            server = new ServerSocket(port);
            while (true) {
                System.out.println("Waiting for clients ...");
                Socket client = server.accept();
                System.out.println("Client connected ...");
                processRequest(client);
            }
        } catch (IOException e) {
            throw new ServerException("Starting server errror ", e);
        } finally {
            stop();
        }
    }

    private void processRequest(Socket client) {
        SrvApplicationObjectWorker worker = new SrvApplicationObjectWorker(srvApplication, client);
        Thread thread = new Thread(worker);
        thread.start();
    }

    public void stop() throws ServerException {
        try {
            server.close();
        } catch (IOException e) {
            throw new ServerException("Closing server error ", e);
        }
    }
}
