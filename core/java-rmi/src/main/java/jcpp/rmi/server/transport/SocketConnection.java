package jcpp.rmi.server.transport;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

import java.net.Socket;
import java.net.SocketException;
import java.net.UnknownHostException;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import jcpp.rmi.server.gateway.GatewayConfiguration;
import jcpp.rmi.server.gateway.GatewaySocketFactory;
import jcpp.rmi.server.gateway.IGatewaySocket;
import jcpp.rmi.server.gateway.Route;
import jcpp.rmi.server.transport.statistic.SocketStatistic;


public class SocketConnection extends Connection {
    private static Log log = LogFactory.getLog(SocketConnection.class);
    private Socket socket;


    public SocketConnection(Route route, Connections connections, SocketStatistic socketStatistic, GatewayConfiguration gatewayConfiguration) throws UnknownHostException, IOException, ClassNotFoundException {
        super(route, connections, socketStatistic, gatewayConfiguration);
        this.socket = GatewaySocketFactory.createSocket(route, connections.getTransport().getTransportConfiguration().getGatewayConfiguration());
        this.socket.setSoTimeout(connections.getTransport().getTransportConfiguration().getSocketTimeout());
        this.socket.setTcpNoDelay(true);
        this.socket.setKeepAlive(true);
    }

    public SocketConnection(Socket socket, Transport transport, SocketStatistic socketStatistic, GatewayConfiguration gatewayConfiguration) {
        super(transport, socketStatistic, gatewayConfiguration);
        this.socket = socket;
    }


    @Override
    public void setSoTimeout(int timeout) throws SocketException {
        socket.setSoTimeout(timeout);
    }

    @Override
    public boolean isReusable() {
        return ((IGatewaySocket) socket).isReausable();
    }

    public Socket getSocket() {
        return socket;
    }

    @Override
    public String toString() {
        return "Connection[" + connections + ", " + socket + "]";
    }

    @Override
    protected void killInternal() throws IOException {
        socket.close();
    }

    @Override
    protected boolean isSocketClosed() {
        return socket.isClosed();
    }

    @Override
    protected Socket getSocketInternal() {
        return socket;
    }

    @Override
    protected OutputStream getOuputStreamInternal() throws IOException {
        return socket.getOutputStream();
    }

    @Override
    protected InputStream getInputStreamInternal() throws IOException {
        return socket.getInputStream();
    }
}
