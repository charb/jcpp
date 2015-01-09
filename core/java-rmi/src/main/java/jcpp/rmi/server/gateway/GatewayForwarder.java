package jcpp.rmi.server.gateway;

import java.io.IOException;

import java.net.Socket;

import java.util.concurrent.Callable;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import jcpp.rmi.server.gateway.http.HttpRequestGatewaySocket;
import jcpp.rmi.server.gateway.tunnel.GatewayTunnel;


public class GatewayForwarder implements Callable<Void> {
    private static Log log = LogFactory.getLog(GatewayForwarder.class);
    private GatewayForwarder gatewayForwarder;
    private Socket srcSocket;
    private Socket targetSocket;
    private boolean valid;
    private GatewayConfiguration gatewayConfiguration;


    public GatewayForwarder(Socket srcSocket, GatewayConfiguration gatewayConfiguration) throws IOException, ClassNotFoundException {
        this(srcSocket, gatewayConfiguration, null);
    }

    public GatewayForwarder(Socket srcSocket, GatewayConfiguration gatewayConfiguration, GatewayTunnel tunnel) throws IOException {
        this.srcSocket = srcSocket;
        this.gatewayConfiguration = gatewayConfiguration;
        Route route = ((IGatewaySocket) srcSocket).getRoute();
        Address nextAddress = (route != null) ? route.peakAddress() : null;
        if (log.isInfoEnabled()) {
            log.info("Gateway Forwarder created with next addess: " + nextAddress);

        }
        if ((tunnel != null) && !tunnel.getGateway().isTunnelOpener() && (nextAddress != null) && nextAddress.equals(tunnel.getTunnelAddress())) {
            this.targetSocket = tunnel.create(route);
        } else {
            if ((route != null) && route.isHttp()) {
                this.targetSocket = new HttpRequestGatewaySocket(route, true, gatewayConfiguration);
            } else {
                this.targetSocket = new GatewaySocket(route, true, gatewayConfiguration);
            }
            if (log.isInfoEnabled()) {
                log.info("Gateway Forwarder's target socket created: " + targetSocket);
            }
        }
        this.valid = true;
    }

    public GatewayForwarder(GatewayForwarder gatewayForwarder) throws IOException {
        this.gatewayForwarder = gatewayForwarder;
        this.srcSocket = gatewayForwarder.getTargetGatewaySocket();
        this.targetSocket = gatewayForwarder.getSourceGatewaySocket();
        this.gatewayConfiguration = gatewayForwarder.getGatewayConfiguration();
        this.valid = true;
    }


    public GatewayConfiguration getGatewayConfiguration() {
        return gatewayConfiguration;
    }

    public Socket getSourceGatewaySocket() {
        return srcSocket;
    }

    public Socket getTargetGatewaySocket() {
        return targetSocket;
    }

    @Override
    public Void call() throws Exception {
        String oldName = Thread.currentThread().getName();
        Thread.currentThread().setName("Gateway Connection Socket Thread - " + srcSocket);
        try {
            byte[] buffer = new byte[gatewayConfiguration.getReceiveBufferSize()];
            int length;

            try {
                if (((IGatewaySocket) srcSocket).isReausable()) {
                    while (isValid()) {
                        length = srcSocket.getInputStream().read(buffer);
                        while (length != -1) {
                            targetSocket.getOutputStream().write(buffer, 0, length);
                            targetSocket.getOutputStream().flush();
                            length = srcSocket.getInputStream().read(buffer);
                        }
                        setValid(false);
                    }
                } else {
                    if (isValid()) {
                        length = srcSocket.getInputStream().read(buffer);
                        while (length != -1) {
                            targetSocket.getOutputStream().write(buffer, 0, length);
                            length = srcSocket.getInputStream().read(buffer);
                        }

                        length = targetSocket.getInputStream().read(buffer);
                        while (length != -1) {
                            srcSocket.getOutputStream().write(buffer, 0, length);
                            length = targetSocket.getInputStream().read(buffer);
                        }
                        srcSocket.getOutputStream().flush();
                        srcSocket.getOutputStream().close();
                    }
                }
            } catch (Throwable e) {
                if (!srcSocket.isClosed() && !targetSocket.isClosed() && log.isWarnEnabled()) {
                    log.warn("Exception caught in GatewayForwarder while forwarding from " + srcSocket + " to " + targetSocket, e);
                }
                setValid(false);
            }
        } finally {
            stop();
            Thread.currentThread().setName(oldName);
        }
        return null;
    }

    public synchronized void setValid(boolean valid) {
        this.valid = valid;
    }

    public void stop() {
        setValid(false);
        try {
            if (!targetSocket.isClosed()) {
                targetSocket.close();
            }
        } catch (IOException e) {
            if (log.isDebugEnabled()) {
                log.debug("Error closing target socket", e);
            }
        }
        try {
            if (!srcSocket.isClosed()) {
                srcSocket.close();
            }
        } catch (IOException e) {
            if (log.isDebugEnabled()) {
                log.debug("Error closing source socket", e);
            }
        }

        if (gatewayForwarder != null) {
            gatewayForwarder.stop();
        }
    }

    private synchronized boolean isValid() {
        return valid && !srcSocket.isClosed() && !targetSocket.isClosed();
    }
}
