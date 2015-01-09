package jcpp.rmi.server.gateway;

import java.io.IOException;

import java.net.InetSocketAddress;
import java.net.ServerSocket;
import java.net.Socket;
import java.net.SocketTimeoutException;
import java.net.UnknownHostException;

import java.nio.channels.ServerSocketChannel;
import java.nio.channels.SocketChannel;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import jcpp.rmi.server.gateway.http.HttpRequestGatewaySocket;


public class GatewaySocketFactory {
    private static Log log = LogFactory.getLog(GatewaySocketFactory.class);


    public GatewaySocketFactory() {
    }


    public static Socket createSocket(Route route, GatewayConfiguration gatewayConfiguration) throws UnknownHostException, IOException, ClassNotFoundException {
        if ((route != null) && route.isHttp()) {
            return new HttpRequestGatewaySocket(route, false, gatewayConfiguration);
        }
        return new GatewaySocket(route, false, gatewayConfiguration);
    }

    public static ServerSocket createServerSocket(int port, GatewayConfiguration gatewayConfiguration) throws IOException {
        return new GatewayServerSocket(port, false, gatewayConfiguration);
    }

    public static ServerSocketChannel createServerSocketChannel(int port, GatewayConfiguration gatewayConfiguration) throws IOException {
        ServerSocketChannel serverChannel = ServerSocketChannel.open();
        serverChannel.configureBlocking(true);
        serverChannel.socket().bind(new InetSocketAddress(port), gatewayConfiguration.getBackLog());
        return serverChannel;
    }

    public static SocketChannel createSocketChannel(Route route, GatewayConfiguration gatewayConfiguration) throws IOException {
        Address address = route.popAddress();
        InetSocketAddress socketAddress = new InetSocketAddress(address.getHostName(), address.getPort());
        SocketChannel socketChannel = SocketChannel.open();
        socketChannel.configureBlocking(true);
        connectSocket(socketChannel.socket(), gatewayConfiguration, address, socketAddress);
        socketChannel.socket().setReceiveBufferSize(gatewayConfiguration.getReceiveBufferSize());
        socketChannel.socket().setSendBufferSize(gatewayConfiguration.getSendBufferSize());
        socketChannel.configureBlocking(false);
        return socketChannel;
    }

    public static void connectSocket(Socket socket, GatewayConfiguration gatewayConfiguration, Address address, InetSocketAddress socketAddress) throws IOException, SocketTimeoutException {
        int timeout = gatewayConfiguration.getEstablishConnectionTimeout(address);
        try {
            socket.connect(socketAddress, timeout);
            gatewayConfiguration.connectionSucceeded(address);
        } catch (SocketTimeoutException e) {
            int attempts = gatewayConfiguration.incrementFailedConnectionAttempts(address);
            if (timeout == gatewayConfiguration.getEstablishConnectionMinTimeout()) {
                String message = e.getMessage() + " - " + address + " is still unaccessible (" + timeout + " msec timeout) after " + attempts + " attempts.";
                IOException ex = new IOException(message);
                if (log.isWarnEnabled()) {
                    log.warn(message, ex);
                }
                throw ex;
            }
            throw e;
        }
    }

}
