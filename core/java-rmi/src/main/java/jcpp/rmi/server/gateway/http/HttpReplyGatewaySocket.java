package jcpp.rmi.server.gateway.http;

import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.InetAddress;
import java.net.Socket;

import jcpp.rmi.server.compression.CompressionOutputStream;
import jcpp.rmi.server.gateway.GatewayConfiguration;
import jcpp.rmi.server.gateway.IGatewaySocket;
import jcpp.rmi.server.gateway.Route;
import jcpp.rmi.server.statistic.StatisticInputStream;
import jcpp.rmi.server.statistic.StatisticOutputStream;

public class HttpReplyGatewaySocket extends Socket implements IGatewaySocket {
    private Socket socket;
    private InputStream replyInputStream;
    private OutputStream replyOutputStream;
    private boolean headerSent;
    private Route route;
    private boolean isGateway;
    private GatewayConfiguration gatewayConfiguration;

    public HttpReplyGatewaySocket(Socket socket, InputStream in, boolean isGateway, GatewayConfiguration gatewayConfiguration) throws IOException, ClassNotFoundException {
        this.socket = socket;
        this.isGateway = isGateway;
        this.gatewayConfiguration = gatewayConfiguration;
        replyInputStream = new HttpReplyGatewayInputStream(in, isGateway, gatewayConfiguration);
        route = ((HttpReplyGatewayInputStream) replyInputStream).getGatewayCompressionInputStream().getRoute();
        replyInputStream = new StatisticInputStream(replyInputStream);
        socket.setSoTimeout(gatewayConfiguration.getReadTimeout());
    }

    public Route getRoute() {
        return route;
    }

    public boolean isReausable() {
        return false;
    }

    public InetAddress getInetAddress() {
        return null;
    }

    public InputStream getInputStream() {
        return replyInputStream;
    }

    public OutputStream getOutputStream() throws IOException {
        if(replyOutputStream == null) {
            replyOutputStream = socket.getOutputStream();
        }
        if(!headerSent) {
            DataOutputStream dataOutputStream = new DataOutputStream(replyOutputStream);
            String response = "HTTP/1.0 200 OK\r\n";
            dataOutputStream.writeBytes(response);
            dataOutputStream.flush();
            headerSent = true;
            replyOutputStream = new HttpReplyGatewayOutputStream(replyOutputStream);
            if(gatewayConfiguration.isCompressionEnabled() && !isGateway) {
                replyOutputStream = new CompressionOutputStream(replyOutputStream, gatewayConfiguration.getSendBufferSize(), 2 * gatewayConfiguration.getSendBufferSize(), gatewayConfiguration.getCompressionThreshold(), gatewayConfiguration.getCompressionLevel());
            }
            replyOutputStream = new StatisticOutputStream(replyOutputStream);
        }
        return replyOutputStream;
    }

    public void close() throws IOException {
        getOutputStream().close();
        socket.close();
    }

    public String toString() {
        return "HttpReplyGatewaySocket[" + socket + "]";
    }
}
