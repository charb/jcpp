package jcpp.rmi.server.gateway;

import java.io.IOException;
import java.io.Serializable;

import java.net.InetSocketAddress;
import java.net.Socket;

import java.rmi.server.RMIClientSocketFactory;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import jcpp.rmi.server.transport.EndPoint;
import jcpp.rmi.server.transport.TransportRouter;


public class ClientSocketFactory implements RMIClientSocketFactory, Serializable {
    private static Log log = LogFactory.getLog(ClientSocketFactory.class);
    private static final long serialVersionUID = 1L;

    private String targetSite;
    private GatewayConfiguration gatewayConfiguration;


    public ClientSocketFactory(String targetSite, GatewayConfiguration gatewayConfiguration) {
        this.targetSite = targetSite;
        this.gatewayConfiguration = gatewayConfiguration;
    }


    @Override
    public Socket createSocket(String host, int port) throws IOException {
        TransportRouter transportRouter = SocketFactoryRegistry.getTransportRouter();
        Route route = transportRouter.findRoute(SocketFactoryRegistry.getLocalSite(), new EndPoint(host, port, targetSite));
        if (route != null) {
            try {
                return GatewaySocketFactory.createSocket(route.clone(), gatewayConfiguration);
            } catch (Exception e) {
                if (log.isDebugEnabled()) {
                    log.debug("Error while creating socket.", e);
                }
                throw new IOException(e);
            }
        }
        Socket socket = new Socket();
        InetSocketAddress socketAddress = new InetSocketAddress(host, port);
        int establishConnectionTimeout = (gatewayConfiguration != null) ? gatewayConfiguration.getEstablishConnectionInitialTimeout() : 0;
        socket.connect(socketAddress, establishConnectionTimeout);
        return socket;
    }

    public String getTargetSite() {
        return targetSite;
    }

    @Override
    public int hashCode() {
        return 0;
    }

    @Override
    public boolean equals(Object obj) {
        if ((getClass() == obj.getClass()) && (targetSite == null)) {
            if (((ClientSocketFactory) obj).getTargetSite() == null) {
                return true;
            } else {
                return false;
            }
        }
        return ((getClass() == obj.getClass()) && targetSite.equals(((ClientSocketFactory) obj).getTargetSite()));
    }
}
