package jcpp.rmi.server.gateway.tunnel;

import java.io.IOException;
import java.io.InputStream;
import java.io.ObjectInputStream;

import java.net.Socket;

import java.util.concurrent.Callable;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import jcpp.rmi.server.gateway.Route;
import jcpp.rmi.server.transport.TransportConfiguration;


public class GatewayTunnelControlReader implements Callable<Void> {
    private static Log log = LogFactory.getLog(GatewayTunnelControlReader.class);

    private GatewayTunnel tunnel;
    private ControlSocketWrapper controlSocketWrapper;


    public GatewayTunnelControlReader(GatewayTunnel tunnel, ControlSocketWrapper tunnelControlSocket) {
        this.tunnel = tunnel;
        this.controlSocketWrapper = tunnelControlSocket;
    }


    @Override
    public Void call() throws Exception {

        Socket tunnelControlSocket = this.controlSocketWrapper.getControlSocket();
        while (!tunnelControlSocket.isClosed()) {
            try {
                InputStream in = tunnelControlSocket.getInputStream();
                int opType = in.read();
                if (opType == GatewayTunnel.CREATE) {
                    int socketId = GatewayTunnel.readIntFromStream(in);
                    if (log.isInfoEnabled()) {
                        log.info("Control socket received CREATE request ID " + socketId);
                    }
                    Route route = (Route) new ObjectInputStream(in).readObject();
                    Socket tunnelSocket = null;
                    synchronized (tunnel) {
                        tunnelSocket = tunnel.openTunnelSocket();
                    }
                    tunnel.accept(socketId, route, tunnelSocket);
                } else if (opType == TransportConfiguration.MSG_TYPE_OK) {

                } else {
                    throw new IOException("Stream is corrupted. Invalid tunnel control operation byte: 0x" + Integer.toHexString(opType));
                }
            } catch (IOException e) {
                controlSocketWrapper.close();
            }

        }
        return null;
    }

}
