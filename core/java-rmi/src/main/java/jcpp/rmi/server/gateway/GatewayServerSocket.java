package jcpp.rmi.server.gateway;

import java.io.BufferedInputStream;
import java.io.IOException;

import java.net.ServerSocket;
import java.net.Socket;

import jcpp.rmi.server.gateway.http.HttpReplyGatewaySocket;


public class GatewayServerSocket extends ServerSocket {
    private boolean isGateway;
    private GatewayConfiguration gatewayConfiguration;


    public GatewayServerSocket(int port, boolean isGateway, GatewayConfiguration gatewayConfiguration) throws IOException {
        super(port, gatewayConfiguration.getBackLog());
        this.isGateway = isGateway;
        this.gatewayConfiguration = gatewayConfiguration;
    }


    @Override
    public Socket accept() throws IOException {
        Socket socket = super.accept();
        socket.setReceiveBufferSize(gatewayConfiguration.getReceiveBufferSize());
        socket.setSendBufferSize(gatewayConfiguration.getSendBufferSize());
        socket.setSoTimeout(gatewayConfiguration.getReadTimeout());
        BufferedInputStream bufferedInputStream = new BufferedInputStream(socket.getInputStream(), gatewayConfiguration.getReceiveBufferSize());
        bufferedInputStream.mark(4);
        boolean isHttp = (bufferedInputStream.read() == 'P') && (bufferedInputStream.read() == 'O') && (bufferedInputStream.read() == 'S') && (bufferedInputStream.read() == 'T');
        bufferedInputStream.reset();
        try {
            if (isHttp) {
                return new HttpReplyGatewaySocket(socket, bufferedInputStream, isGateway, gatewayConfiguration);
            }
            return new GatewaySocket(socket, bufferedInputStream, isGateway, gatewayConfiguration);
        } catch (ClassNotFoundException classNotFoundException) {
            throw new IOException(classNotFoundException);
        }
    }

    @Override
    public String toString() {
        return "GatewayServerSocket[ServerSocket:" + super.toString() + "]";
    }
}
