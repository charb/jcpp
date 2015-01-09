package jcpp.rmi.server.gateway;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

import java.net.InetAddress;
import java.net.InetSocketAddress;
import java.net.Socket;
import java.net.SocketException;
import java.net.UnknownHostException;

import jcpp.rmi.server.compression.CompressionInputStream;
import jcpp.rmi.server.compression.CompressionOutputStream;
import jcpp.rmi.server.statistic.StatisticInputStream;
import jcpp.rmi.server.statistic.StatisticOutputStream;


public class GatewaySocket extends Socket implements IGatewaySocket {
    private Socket socket;
    private InputStream input;
    private OutputStream output;
    private boolean bSendSocket;
    private Route route;
    private GatewayConfiguration gatewayConfiguration;


    public GatewaySocket(Route route, boolean isGateway, GatewayConfiguration gatewayConfiguration) throws UnknownHostException, IOException {
        Address address = route.popAddress();
        this.gatewayConfiguration = gatewayConfiguration;
        InetSocketAddress socketAddress = new InetSocketAddress(address.getHostName(), address.getPort());
        this.socket = new Socket();
        GatewaySocketFactory.connectSocket(socket, gatewayConfiguration, address, socketAddress);
        this.output = new StatisticOutputStream(new GatewayCompressionOutputStream(socket.getOutputStream(), route, gatewayConfiguration.isCompressionEnabled() && !isGateway, gatewayConfiguration.getSendBufferSize(),
                2 * gatewayConfiguration.getSendBufferSize(), gatewayConfiguration.getCompressionThreshold(), gatewayConfiguration.getCompressionLevel()));
        if (gatewayConfiguration.isCompressionEnabled() && !isGateway) {
            this.input = new StatisticInputStream(new CompressionInputStream(socket.getInputStream(), gatewayConfiguration.getSendBufferSize()));
        } else {
            this.input = new StatisticInputStream(socket.getInputStream());
        }
        this.bSendSocket = true;
        this.route = route;
        setSocketSetting();
    }

    public GatewaySocket(Socket socket, InputStream in, boolean isGateway, GatewayConfiguration gatewayConfiguration) throws UnknownHostException, IOException, ClassNotFoundException {
        this.socket = socket;
        this.gatewayConfiguration = gatewayConfiguration;
        if (gatewayConfiguration.isCompressionEnabled() && !isGateway) {
            this.output = new StatisticOutputStream(new CompressionOutputStream(socket.getOutputStream(), gatewayConfiguration.getReceiveBufferSize(), 2 * gatewayConfiguration.getReceiveBufferSize(),
                    gatewayConfiguration.getCompressionThreshold(), gatewayConfiguration.getCompressionLevel()));
        } else {
            this.output = new StatisticOutputStream(socket.getOutputStream());
        }
        this.input = new GatewayCompressionInputStream(in, gatewayConfiguration.isCompressionEnabled() && !isGateway, gatewayConfiguration);
        this.bSendSocket = false;
        this.route = ((GatewayCompressionInputStream) input).getRoute();
        this.input = new StatisticInputStream(input);
        setSocketSetting();
    }


    @Override
    public Route getRoute() {
        return route;
    }

    @Override
    public boolean isReausable() {
        return true;
    }

    @Override
    public InputStream getInputStream() throws IOException {
        return input;
    }

    @Override
    public OutputStream getOutputStream() throws IOException {
        return output;
    }

    @Override
    public void close() throws IOException {
        try {
            output.close();
        } catch (IOException e) {
        }
        try {
            input.close();
        } catch (IOException e) {
        }
        try {
            socket.close();
        } catch (IOException e) {
        }
        try {
            super.close();
        } catch (IOException e) {
        }
    }

    @Override
    public InetAddress getInetAddress() {
        return socket.getInetAddress();
    }

    @Override
    public InetAddress getLocalAddress() {
        return socket.getLocalAddress();
    }

    @Override
    public int getPort() {
        return socket.getPort();
    }

    @Override
    public int getLocalPort() {
        return socket.getLocalPort();
    }

    @Override
    public void setTcpNoDelay(boolean on) throws SocketException {
        socket.setTcpNoDelay(on);
    }

    @Override
    public boolean getTcpNoDelay() throws SocketException {
        return socket.getTcpNoDelay();
    }

    @Override
    public void setSoLinger(boolean on, int val) throws SocketException {
        socket.setSoLinger(on, val);
    }

    @Override
    public int getSoLinger() throws SocketException {
        return socket.getSoLinger();
    }

    @Override
    public void setSoTimeout(int timeout) throws SocketException {
        socket.setSoTimeout(timeout);
    }

    @Override
    public int getSoTimeout() throws SocketException {
        return socket.getSoTimeout();
    }

    @Override
    public String toString() {
        String strSocketType = "GatewaySocket";
        strSocketType += bSendSocket ? "(SendSocket)" : "(ReceiveSocket)";
        return strSocketType + "[socket:" + socket + "]";
    }

    private void setSocketSetting() throws SocketException {
        socket.setSoTimeout(gatewayConfiguration.getReadTimeout());
    }
}
