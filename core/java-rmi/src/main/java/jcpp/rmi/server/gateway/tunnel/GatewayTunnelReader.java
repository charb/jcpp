package jcpp.rmi.server.gateway.tunnel;

import java.io.IOException;
import java.io.InputStream;

import java.net.Socket;

import java.util.concurrent.Callable;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;


public class GatewayTunnelReader implements Callable<Void> {
    private static Log log = LogFactory.getLog(GatewayTunnelReader.class);

    private GatewayTunnel tunnel;
    private Socket tunnelSocket;


    public GatewayTunnelReader(GatewayTunnel tunnel, Socket tunnelSocket) {
        this.tunnel = tunnel;
        this.tunnelSocket = tunnelSocket;
    }


    @Override
    public Void call() throws Exception {
        String oldName = Thread.currentThread().getName();
        Thread.currentThread().setName("Gateway Tunnel Reader; Tunnel Socket: " + tunnelSocket);
        try {
            InputStream in = tunnelSocket.getInputStream();
            in.mark(1);
            int opType = in.read();
            if (opType == GatewayTunnel.COMPLETE_CREATE) {
                int socketId = GatewayTunnel.readIntFromStream(in);
                tunnel.addCreatedSocket(socketId, tunnelSocket);
            } else if (opType == GatewayTunnel.CREATE_CONTROL) {
                tunnel.registerControlSocket(tunnelSocket);
            } else {
                in.reset();
                tunnel.getGateway().handleAcceptedSocket(tunnelSocket);
            }
        } catch (IOException e) {
            // TODO review this
            tunnelSocket.close();
        } finally {
            Thread.currentThread().setName(oldName);
        }
        return null;
    }

}
