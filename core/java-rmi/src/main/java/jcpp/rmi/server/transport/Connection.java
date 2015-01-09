package jcpp.rmi.server.transport;

import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

import java.net.Socket;
import java.net.SocketException;
import java.net.UnknownHostException;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import jcpp.rmi.server.gateway.GatewayConfiguration;
import jcpp.rmi.server.gateway.Route;
import jcpp.rmi.server.statistic.StatisticInputStream;
import jcpp.rmi.server.statistic.StatisticOutputStream;
import jcpp.rmi.server.transport.statistic.SocketStatistic;


public abstract class Connection {
    private static Log log = LogFactory.getLog(Connection.class);
    private static int globalId;

    protected int id;
    protected long lastUsed;
    protected Connections connections;
    protected DataOutputStream out;
    protected DataInputStream in;
    protected boolean opened;
    protected Transport transport;
    protected SocketStatistic socketStatistic;
    protected GatewayConfiguration gatewayConfiguration;
    protected Route route;


    public Connection(Route route, Connections connections, SocketStatistic socketStatistic, GatewayConfiguration gatewayConfiguration) throws UnknownHostException, IOException, ClassNotFoundException {
        this.route = route;
        this.connections = connections;
        synchronized (Connection.class) {
            this.id = globalId++;
        }
        setSocketStatistic(socketStatistic);
        this.gatewayConfiguration = gatewayConfiguration;
    }

    public Connection(Transport transport, SocketStatistic socketStatistic, GatewayConfiguration gatewayConfiguration) {
        this.transport = transport;
        this.gatewayConfiguration = gatewayConfiguration;
        synchronized (Connection.class) {
            this.id = globalId++;
        }
        setSocketStatistic(socketStatistic);
        transport.getTransportStatistic().getReceivedConnection().incrementAndGet();
    }


    public void free() {
        if (connections != null) {
            if (isReusable()) {
                connections.free(this);
            } else {
                try {
                    kill();
                } catch (IOException e) {
                    if (log.isDebugEnabled()) {
                        log.debug("Error killing the non-reusable connection: " + this, e);
                    }
                }
            }
        }
    }

    public void kill() throws IOException {
        if (connections != null) {
            connections.kill(this);
            connections.getTransport().getTransportStatistic().getRequestedConnectionKilled().incrementAndGet();
        } else {
            transport.getTransportStatistic().getReceivedConnectionKilled().incrementAndGet();
        }
        socketStatistic.archive();
        killInternal();
    }

    public boolean openConnection() throws IOException {
        if (!opened) {
            sendConnectionHeader();
            out.flush();

            if (isReusable()) {
                int oldTimeout = 0;
                try {
                    oldTimeout = getSocketInternal().getSoTimeout();
                } catch (IOException e) {
                    if (log.isDebugEnabled()) {
                        log.debug("Error getting socket timeout during openConnection(). Socket - " + getSocketInternal(), e);
                    }
                    return false;
                }

                try {
                    if (connections == null) {
                        setSoTimeout(transport.getTransportConfiguration().getPingTimeout());
                    } else {
                        setSoTimeout(connections.getTransport().getTransportConfiguration().getPingTimeout());
                    }
                    return readOk();
                } catch (IOException e) {
                    if (log.isDebugEnabled()) {
                        log.debug("Error setting socket timeout and reading OK during openConnection(). Socket - " + getSocketInternal(), e);
                    }
                    return false;
                } finally {
                    try {
                        setSoTimeout(oldTimeout);
                    } catch (IOException e) {
                        if (log.isDebugEnabled()) {
                            log.debug("Error setting socket timeout during openConnection(). Socket - " + getSocketInternal(), e);
                        }
                        return false;
                    }
                }
            } else {
                return true;
            }
        }
        return true;
    }

    public void startCall() throws IOException {
        getOutputStream();
        out.writeByte((int) TransportConfiguration.MSG_TYPE_CALL);
    }

    public void finishCall() throws IOException {
        getOutputStream();
        out.flush();
    }

    public void sendOk() throws IOException {
        getOutputStream();
        out.writeByte((int) TransportConfiguration.MSG_TYPE_OK);
        if (isReusable()) {
            out.flush();
        }
    }

    public boolean readOk() throws IOException {
        getInputStream();
        byte okByte = in.readByte();
        if (okByte != TransportConfiguration.MSG_TYPE_OK) {
            if (log.isDebugEnabled()) {
                log.debug("Reading: MSG_TYPE_OK expected, received: " + okByte + ". Socket - " + getSocketInternal());
            }
            return false;
        }
        return true;
    }

    public boolean isDead() {
        boolean isDead = false;
        int oldTimeout = 0;
        try {
            oldTimeout = getSocketInternal().getSoTimeout();
        } catch (IOException e) {
            if (log.isDebugEnabled()) {
                log.debug("Error getting socket timeout during isDead(). Considering socket as dead. Socket - " + getSocketInternal(), e);
            }
            return true;
        }
        try {
            sendPing();
            if (connections == null) {
                setSoTimeout(transport.getTransportConfiguration().getPingTimeout());
            } else {
                setSoTimeout(connections.getTransport().getTransportConfiguration().getPingTimeout());
            }
            if (!readOk()) {
                isDead = true;
            }
        } catch (IOException e) {
            if (log.isDebugEnabled()) {
                log.debug("Error while ping during isDead(). Considering socket as dead. Socket - " + getSocketInternal(), e);
            }
            isDead = true;
        } finally {
            if (isDead && !isSocketClosed()) {
                try {
                    killInternal();
                } catch (IOException e) {
                    if (log.isDebugEnabled()) {
                        log.debug("Error closing socket of dead connection. Socket - " + getSocketInternal(), e);
                    }
                }
            }
            try {
                setSoTimeout(oldTimeout);
            } catch (IOException e) {
                if (log.isDebugEnabled()) {
                    log.debug("Error setting socket timeout during isDead(). Socket - " + getSocketInternal(), e);
                }
                return true;
            }
        }
        return isDead;
    }

    public DataOutputStream getOutputStream() throws IOException {
        if (out == null) {
            OutputStream outputStream = getOuputStreamInternal();
            ((StatisticOutputStream) outputStream).setApplicationByteCounter(socketStatistic.getSentApplicationData());
            ((StatisticOutputStream) outputStream).setNetworkByteCounter(socketStatistic.getSentNetworkData());
            out = new DataOutputStream(new BufferedOutputStream(outputStream, gatewayConfiguration.getSendBufferSize()));
        }
        return out;
    }

    public DataInputStream getInputStream() throws IOException {
        if (in == null) {
            InputStream inputStream = getInputStreamInternal();
            ((StatisticInputStream) inputStream).setApplicationDataCounter(socketStatistic.getRecvApplicationData());
            ((StatisticInputStream) inputStream).setNetworkDataCounter(socketStatistic.getRecvNetworkData());
            in = new DataInputStream(new BufferedInputStream(inputStream, gatewayConfiguration.getReceiveBufferSize()));
        }
        return in;
    }

    public GatewayConfiguration getGatewayConfiguration() {
        return gatewayConfiguration;
    }

    public void setLastUsed() {
        this.lastUsed = System.currentTimeMillis();
    }

    public boolean isReusable() {
        return true;
    }

    public void setSoTimeout(int timeout) throws SocketException {
    }

    public long getLastUsed() {
        return lastUsed;
    }

    public Connections getConnections() {
        return connections;
    }

    @Override
    public String toString() {
        return "Connection[" + connections + ", " + getSocketInternal() + "]";
    }

    protected abstract boolean isSocketClosed();

    protected abstract OutputStream getOuputStreamInternal() throws IOException;

    protected abstract InputStream getInputStreamInternal() throws IOException;

    protected abstract void killInternal() throws IOException;

    protected abstract Socket getSocketInternal();

    protected void sendConnectionHeader() throws IOException {
        opened = true;
        getOutputStream();
        out.writeInt(TransportConfiguration.getMagicNumber());
        connections.getTransport().getLocalEndPoint().write(out);
    }

    protected void setSocketStatistic(SocketStatistic socketStatistic) {
        if (socketStatistic != null) {
            this.socketStatistic = socketStatistic;
            this.socketStatistic.setId(id);
        }
    }

    protected void sendPing() throws IOException {
        out.writeByte((int) TransportConfiguration.MSG_TYPE_PING);
        out.flush();
    }
}
