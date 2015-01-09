package jcpp.rmi.server.gateway.tunnel;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

import java.net.InetAddress;
import java.net.Socket;
import java.net.SocketException;

import jcpp.rmi.server.gateway.IGatewaySocket;
import jcpp.rmi.server.gateway.Route;


public class VirtualSocket extends Socket implements IGatewaySocket {
    private int id;
    private Route route;
    private Socket tunnelSocket;


    public VirtualSocket(int id, Socket tunnelSocket) {
        this.id = id;
        this.tunnelSocket = tunnelSocket;
    }


    public int getId() {
        return id;
    }

    public void setRoute(Route route) {
        this.route = route;
    }

    @Override
    public Route getRoute() {
        return route;
    }

    @Override
    public boolean isReausable() {
        return ((IGatewaySocket) tunnelSocket).isReausable();
    }

    @Override
    public InputStream getInputStream() throws IOException {
        return tunnelSocket.getInputStream();
    }

    @Override
    public OutputStream getOutputStream() throws IOException {
        return tunnelSocket.getOutputStream();
    }

    @Override
    public void close() throws IOException {
        tunnelSocket.close();
    }

    @Override
    public InetAddress getInetAddress() {
        return tunnelSocket.getInetAddress();
    }

    @Override
    public InetAddress getLocalAddress() {
        return tunnelSocket.getLocalAddress();
    }

    @Override
    public int getPort() {
        return tunnelSocket.getPort();
    }

    @Override
    public int getLocalPort() {
        return tunnelSocket.getLocalPort();
    }

    @Override
    public void setTcpNoDelay(boolean on) throws SocketException {
        tunnelSocket.setTcpNoDelay(on);
    }

    @Override
    public boolean getTcpNoDelay() throws SocketException {
        return tunnelSocket.getTcpNoDelay();
    }

    @Override
    public void setSoLinger(boolean on, int val) throws SocketException {
        tunnelSocket.setSoLinger(on, val);
    }

    @Override
    public int getSoLinger() throws SocketException {
        return tunnelSocket.getSoLinger();
    }

    @Override
    public void setSoTimeout(int timeout) throws SocketException {
        tunnelSocket.setSoTimeout(timeout);
    }

    @Override
    public int getSoTimeout() throws SocketException {
        return tunnelSocket.getSoTimeout();
    }

    @Override
    public String toString() {
        String strSocketType = "Virtual Socket";
        strSocketType += " [Tunnel Socket: " + tunnelSocket + "]";
        return strSocketType;
    }

}
