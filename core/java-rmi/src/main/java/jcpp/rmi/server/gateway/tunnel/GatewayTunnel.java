package jcpp.rmi.server.gateway.tunnel;

import java.io.IOException;
import java.io.InputStream;
import java.io.ObjectOutputStream;
import java.io.OutputStream;

import java.net.Socket;
import java.net.UnknownHostException;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.Callable;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.ScheduledExecutorService;
import java.util.concurrent.TimeUnit;

import edu.emory.mathcs.backport.java.util.concurrent.atomic.AtomicInteger;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import jcpp.rmi.server.gateway.Address;
import jcpp.rmi.server.gateway.Gateway;
import jcpp.rmi.server.gateway.GatewayConfiguration;
import jcpp.rmi.server.gateway.GatewaySocket;
import jcpp.rmi.server.gateway.Route;
import jcpp.rmi.server.gateway.http.HttpRequestGatewaySocket;
import jcpp.rmi.server.transport.TransportConfiguration;


public class GatewayTunnel {
    private static Log log = LogFactory.getLog(GatewayTunnel.class);

    public static final int BUFFER_SIZE = 21 * 1024;
    public static final byte CREATE = 0x01;
    public static final byte WRITE = 0x02;
    public static final byte CLOSE = 0x04;
    public static final byte COMPLETE_CREATE = 0x08;
    public static final byte CREATE_CONTROL = 0x04;

    private AtomicInteger nextId;

    private final List<ControlSocketWrapper> controlSockets;
    private final Gateway gateway;
    private final Address tunnelAddress;
    private final GatewayConfiguration gatewayConfiguration;
    private final ExecutorService executorService;
    private final Map<Integer, VirtualSocket> virtualSockets;
    private final Map<Integer, BlockingQueue<Socket>> createPendingSockets;
    private ScheduledExecutorService scheduledExecutorService;

    private boolean isClosed;


    public GatewayTunnel(Gateway gateway, Address tunnelAddress, GatewayConfiguration gatewayConfiguration, ExecutorService executorService) {
        this.gateway = gateway;
        this.tunnelAddress = tunnelAddress;
        this.gatewayConfiguration = gatewayConfiguration;
        this.executorService = executorService;
        this.virtualSockets = new HashMap<Integer, VirtualSocket>();
        this.controlSockets = new ArrayList<ControlSocketWrapper>();
        this.createPendingSockets = new HashMap<Integer, BlockingQueue<Socket>>();
        this.nextId = new AtomicInteger();
        this.scheduledExecutorService = Executors.newScheduledThreadPool(1);
    }


    public ScheduledExecutorService getScheduledExecutorService() {
        return scheduledExecutorService;
    }

    public synchronized void openControlSocket() {
        int initialSize = controlSockets.size();
        while ((controlSockets.size() <= initialSize) && !isClosed) {
            Socket socket = null;
            try {
                socket = openTunnelSocket();
                ControlSocketWrapper socketWrapper = new ControlSocketWrapper(this, socket, true);
                OutputStream out = socket.getOutputStream();
                out.write(CREATE_CONTROL);
                out.flush();
                controlSockets.add(socketWrapper);
                if (log.isInfoEnabled()) {
                    log.info("Tunnel Control Socket opened " + socket);
                }
                executorService.submit(new GatewayTunnelControlReader(this, socketWrapper));
            } catch (Exception e) {
                if (log.isErrorEnabled()) {
                    log.error("Unable to open control socket. Retrying in 10 seconds", e);
                }
                if (socket != null) {
                    try {
                        socket.close();
                    } catch (IOException ioe) {
                        if (log.isWarnEnabled()) {
                            log.warn("Exception while trying to close the opened colntrol socket, after failing to send operation type. Socket: " + socket, e);
                        }
                    }
                }
                try {
                    int time = gatewayConfiguration.getGatewayTunnelReconnectTime();
                    Thread.sleep(time);
                } catch (InterruptedException e1) {
                    throw new RuntimeException(e1);
                }
            }
        }
    }

    public void addTunnelSocket(final Socket tunnelSocket) {
        executorService.submit(new GatewayTunnelReader(this, tunnelSocket));
        if (log.isInfoEnabled()) {
            log.info("Tunnel socket accepted " + tunnelSocket);
        }
    }

    public Socket openTunnelSocket() throws UnknownHostException, IOException {
        Route route = new Route(gateway.isHttpTunnel());
        route.addAddress(tunnelAddress);
        Socket tunnelSocket = null;
        if (gateway.isHttpTunnel()) {
            tunnelSocket = new HttpRequestGatewaySocket(route, true, gatewayConfiguration);
        } else {
            tunnelSocket = new GatewaySocket(route, true, gatewayConfiguration);
        }
        return tunnelSocket;
    }

    public void registerControlSocket(Socket socket) {
        final ControlSocketWrapper socketWrapper = new ControlSocketWrapper(this, socket, false);
        controlSockets.add(socketWrapper);
        if (log.isInfoEnabled()) {
            log.info("Tunnel Control Socket accepted " + socket);
        }
        executorService.submit(new Callable<Void>() {

                @Override
                public Void call() throws Exception {
                    Socket controlSocket = socketWrapper.getControlSocket();
                    String oldName = Thread.currentThread().getName();
                    try {
                        Thread.currentThread().setName("Gateway Control Socket Ping Handler: " + controlSocket);
                        while (!controlSocket.isClosed()) {
                            try {
                                InputStream in = controlSocket.getInputStream();
                                int opType = in.read();
                                if (opType == TransportConfiguration.MSG_TYPE_PING) {
                                    synchronized (controlSocket) {
                                        OutputStream out = controlSocket.getOutputStream();
                                        out.write(TransportConfiguration.MSG_TYPE_OK);
                                        out.flush();
                                    }
                                } else {
                                    throw new IOException("Stream is corrupted. Invalid virtual operation byte: 0x" + Integer.toHexString(opType));
                                }
                            } catch (IOException e) {
                                controlSockets.remove(socketWrapper);
                                controlSocket.close();
                            }
                        }
                    } finally {
                        Thread.currentThread().setName(oldName);
                    }
                    return null;
                }

            });
    }

    public Socket getControlSocket() {
        return controlSockets.get(0).getControlSocket(); // possibility to use multiple control sockets
    }

    public Address getTunnelAddress() {
        return tunnelAddress;
    }

    public Gateway getGateway() {
        return gateway;
    }

    public void addCreatedSocket(int socketId, Socket socket) {
        BlockingQueue<Socket> queue = createPendingSockets.get(socketId);
        if (queue == null) {
            queue = new ArrayBlockingQueue<Socket>(1);
            createPendingSockets.put(socketId, queue);
        }
        queue.add(socket);
    }

    public Socket create(Route route) throws IOException {
        int socketId = nextId.getAndIncrement();
        Socket controlSocket = getControlSocket();
        if (log.isInfoEnabled()) {
            log.info("Requesting socket creation ID " + socketId + " on tunnel " + controlSocket + ". Route: " + route);
        }
        BlockingQueue<Socket> queue = getCreatePendingQueue(socketId);
        try {
            Address address = route.popAddress(); // remove address of current gateway which would have otherwise been remove in GatewaySocket constructor

            synchronized (controlSocket) {
                OutputStream out = controlSocket.getOutputStream();
                out.write(CREATE);
                writeIntToStream(out, socketId);
                new ObjectOutputStream(out).writeObject(route);
                out.flush();
            }

            int timeout = gatewayConfiguration.getEstablishConnectionTimeout(address);
            Socket socket = null;
            try {
                socket = queue.poll(timeout, TimeUnit.MILLISECONDS);
            } catch (InterruptedException e) {
            }
            if (socket != null) {
                if (log.isInfoEnabled()) {
                    log.info("Socket creation request ID " + socketId + " completed successfully");
                }
                return socket; // no need for virtual socket here, since socket.getRoute() will not be used
            } else {
                int attempts = gatewayConfiguration.incrementFailedConnectionAttempts(address);
                if (timeout == gatewayConfiguration.getEstablishConnectionMinTimeout()) {
                    String message = "Endpoint " + address + " is still unaccessible (" + timeout + " msec timeout) after " + attempts + " attempts.";
                    IOException ex = new IOException(message);
                    if (log.isWarnEnabled()) {
                        log.warn(message, ex);
                    }
                    throw ex;
                }
                throw new IOException("Attempt to establish connection timed out. Timeout: " + timeout + " msec. Route: " + route);
            }
        } finally {
            createPendingSockets.remove(socketId);
        }
    }

    public VirtualSocket accept(int socketId, Route route, Socket tunnelSocket) throws IOException {
        OutputStream out = tunnelSocket.getOutputStream();
        out.write(COMPLETE_CREATE);
        writeIntToStream(out, socketId);
        out.flush();

        VirtualSocket virtualSocket = null;
        synchronized (this) {
            if (log.isInfoEnabled()) {
                log.info("Accepting new virtual socket on tunnel " + getControlSocket());
            }
            virtualSocket = new VirtualSocket(socketId, tunnelSocket);
            virtualSocket.setRoute(route); // virtual socket is needed for the route
        }
        gateway.handleAcceptedSocket(virtualSocket);
        return virtualSocket;
    }

    public void close() {
        isClosed = true;
        scheduledExecutorService.shutdown();
        for (ControlSocketWrapper socketWrapper : controlSockets) {
            socketWrapper.close();
        }
    }

    @Deprecated
    public synchronized void write(byte[] data, int length, int socketId) throws IOException {
        OutputStream out = getControlSocket().getOutputStream();
        writeIntToStream(out, socketId);
        out.write(WRITE);
        writeIntToStream(out, length);
        out.write(data, 0, length);
        out.flush();
    }

    @Deprecated
    public synchronized void flush(int socketId) throws IOException {
        if (virtualSockets.containsKey(socketId)) {
            OutputStream out = getControlSocket().getOutputStream();
            out.flush();
        }
    }

    @Deprecated
    public synchronized void close(int socketId) throws IOException {
        if (log.isInfoEnabled()) {
            log.info("Closing to tunnel (socketId==" + socketId + ") " + getControlSocket());
        }
        if (virtualSockets.containsKey(socketId)) {
            OutputStream out = getControlSocket().getOutputStream();
            writeIntToStream(out, socketId);
            out.write(CLOSE);
            out.flush();
            virtualSockets.remove(socketId);
        }
    }

    public GatewayConfiguration getGatewayConfiguration() {
        return gatewayConfiguration;
    }

    static int readIntFromStream(InputStream in) throws IOException {
        int[] len = new int[4];
        for (int i = 0; i < 4; i++) {
            len[i] = in.read();
            if (len[i] == -1) {
                throw new IOException("Could not read integer from stream. End of stream reached");
            }
        }
        int integer = (len[0] << 24) ^ (len[1] << 16) ^ (len[2] << 8) ^ len[3];
        return integer;
    }

    void removeControlSocket(ControlSocketWrapper socketWrapper) {
        controlSockets.remove(socketWrapper);
        openControlSocket();
    }

    private synchronized BlockingQueue<Socket> getCreatePendingQueue(int socketId) {
        BlockingQueue<Socket> queue;
        queue = createPendingSockets.get(socketId);
        if (queue == null) {
            queue = new ArrayBlockingQueue<Socket>(1);
            createPendingSockets.put(socketId, queue);
        }
        return queue;
    }

    private void writeIntToStream(OutputStream out, int value) throws IOException {
        out.write(value >> 24);
        out.write(value >> 16);
        out.write(value >> 8);
        out.write(value);
    }

}
