package jcpp.rmi.server.gateway;

import java.io.IOException;
import java.net.ServerSocket;
import java.rmi.server.RMIServerSocketFactory;

public class ServerSocketFactory implements RMIServerSocketFactory {
    private GatewayConfiguration gatewayConfiguration;
    private int lastPort;

    public ServerSocketFactory(GatewayConfiguration gatewayConfiguration) {
        this.gatewayConfiguration = gatewayConfiguration;
    }

    public ServerSocket createServerSocket(int port) throws IOException {
        ServerSocket serverSocket = GatewaySocketFactory.createServerSocket(port, gatewayConfiguration);
        lastPort = serverSocket.getLocalPort();
        return serverSocket;
    }

    public int getLastPort() {
        return lastPort;
    }
    
    public int hashCode() {
        return 0;
    }

    public boolean equals(Object obj) {
        return (getClass() == obj.getClass());
    }

}
