package jcpp.rmi.server.gateway.tunnel;

import java.io.IOException;
import java.io.OutputStream;

import java.net.Socket;

import java.util.concurrent.Future;
import java.util.concurrent.TimeUnit;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import jcpp.rmi.server.transport.TransportConfiguration;


public class ControlSocketWrapper {
    private static Log log = LogFactory.getLog(ControlSocketWrapper.class);

    private Socket controlSocket;
    private Future<?> pingingTask;
    private GatewayTunnel tunnel;


    public ControlSocketWrapper(GatewayTunnel tunnel, Socket controlSocket, boolean isTunnelOpener) {
        this.tunnel = tunnel;
        this.controlSocket = controlSocket;
        if (isTunnelOpener) {
            int time = tunnel.getGatewayConfiguration().getEstablishConnectionInitialTimeout() / 2;
            pingingTask = tunnel.getScheduledExecutorService().scheduleAtFixedRate(new Runnable() {

                        @Override
                        public void run() {
                            Socket controlSocket = getControlSocket();
                            synchronized (controlSocket) {
                                try {
                                    OutputStream out = controlSocket.getOutputStream();
                                    out.write(TransportConfiguration.MSG_TYPE_PING);
                                    out.flush();
                                } catch (IOException e) {
                                    close();
                                }
                            }
                        }
                    }, time, time, TimeUnit.MILLISECONDS);

        }
    }


    public Socket getControlSocket() {
        return controlSocket;
    }

    public void close() {
        try {
            if (pingingTask != null) {
                pingingTask.cancel(false);
            }
            if (!controlSocket.isClosed()) {
                controlSocket.close();
            }
        } catch (IOException e) {
            if (log.isWarnEnabled()) {
                log.warn("Error while closing control socket " + controlSocket, e);
            }
        } finally {
            tunnel.removeControlSocket(this);
        }
    }

}
