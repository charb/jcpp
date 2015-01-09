package jcpp.rmi.server.gateway;

import java.io.IOException;

import java.net.ServerSocket;
import java.net.Socket;

import java.util.concurrent.Callable;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.apache.log4j.Appender;
import org.apache.log4j.ConsoleAppender;
import org.apache.log4j.Level;
import org.apache.log4j.Logger;
import org.apache.log4j.PatternLayout;

import jcpp.rmi.server.gateway.tunnel.GatewayTunnel;


public class Gateway {
    private static Log log = LogFactory.getLog(Gateway.class);
    private int port;
    private ServerSocket serverSocket;
    private boolean valid;
    private ExecutorService executorService;
    private GatewayConfiguration gatewayConfiguration;
    private ServerSocket tunnelServerSocket;
    private GatewayTunnel gatewayTunnel;
    private IGatewayListener listener;
    private Address remoteTunnelAddress;
    private boolean isTunnelOpener;
    private boolean isHttpTunnel;
    private boolean isTunnelUsed;


    public Gateway(int port, GatewayConfiguration gatewayConfiguration) {
        this(port, gatewayConfiguration, null, false, false);
    }

    public Gateway(int port, GatewayConfiguration gatewayConfiguration, Address remoteTunnelAddress, boolean isHttpTunnel, boolean isTunnelOpener) {
        this.port = port;
        this.gatewayConfiguration = gatewayConfiguration;
        this.remoteTunnelAddress = remoteTunnelAddress;
        this.isHttpTunnel = isHttpTunnel;
        this.isTunnelOpener = isTunnelOpener;
        this.isTunnelUsed = remoteTunnelAddress != null;
    }


    public static void main(String[] args) throws Exception {
        final Logger logger = Logger.getRootLogger();
        logger.setLevel(Level.INFO);
        Appender consoleAppender = new ConsoleAppender(new PatternLayout(), ConsoleAppender.SYSTEM_ERR);
        logger.addAppender(consoleAppender);

        int port = Integer.parseInt(args[0]);
        Address remoteTunnelAddress = new Address(args[1], Integer.parseInt(args[2]));
        boolean isTunnelOpener = Boolean.parseBoolean(args[3]);
        Gateway gateway = new Gateway(port, new GatewayConfiguration(), remoteTunnelAddress, false, isTunnelOpener);
        gateway.start();
        System.out.println("Gateway started");
    }

    public boolean isTunnelOpener() {
        return isTunnelOpener;
    }

    public void setListener(IGatewayListener listener) {
        this.listener = listener;
    }

    public void start() throws Exception {
        serverSocket = new GatewayServerSocket(port, true, gatewayConfiguration);
        port = serverSocket.getLocalPort();
        valid = true;
        executorService = Executors.newCachedThreadPool();
        executorService.submit(new Callable<Void>() {
                @Override
                public Void call() {
                    Thread.currentThread().setName("Gateway Accept socket thread - [Port:" + port + "] [ServerSocket:" + serverSocket + "]");
                    if (log.isInfoEnabled()) {
                        log.info("Gateway accepting connections on: [Port:" + port + "] [ServerSocket:" + serverSocket + "]");
                    }
                    while (isValid() && !serverSocket.isClosed()) {
                        try {
                            Socket socket = serverSocket.accept();
                            if (isTunnelUsed && !isTunnelOpener) {
                                gatewayTunnel.addTunnelSocket(socket);

                                if (listener != null) {
                                    executorService.submit(new Callable<Void>() {
                                            @Override
                                            public Void call() {
                                                String oldName = Thread.currentThread().getName();
                                                Thread.currentThread().setName("Tunnel Opened Notifier");
                                                try {
                                                    listener.tunnelOpened();
                                                } finally {
                                                    Thread.currentThread().setName(oldName);
                                                }
                                                return null;
                                            }
                                        });
                                }
                            } else {
                                handleAcceptedSocket(socket);
                            }
                        } catch (Throwable throwable) {
                            if (!serverSocket.isClosed() && log.isWarnEnabled()) {
                                log.warn("Error while accepting socket.", throwable);
                            }
                        }
                    }
                    return null;
                }
            });

        if (isTunnelUsed) {

            gatewayTunnel = new GatewayTunnel(this, remoteTunnelAddress, gatewayConfiguration, executorService);

            if (isTunnelOpener) {
                gatewayTunnel.openControlSocket();
                if (listener != null) {
                    executorService.submit(new Callable<Void>() {
                            @Override
                            public Void call() {
                                String oldName = Thread.currentThread().getName();
                                Thread.currentThread().setName("Tunnel Opened Notifier");
                                try {
                                    listener.tunnelOpened();
                                } finally {
                                    Thread.currentThread().setName(oldName);
                                }
                                return null;
                            }
                        });
                }
            }

        }
    }

    public void handleAcceptedSocket(Socket socket) throws IOException {
        if (((IGatewaySocket) socket).isReausable()) {
            GatewayForwarder sourceToTargetGatewayForwarder = new GatewayForwarder(socket, gatewayConfiguration, gatewayTunnel);
            executorService.submit(sourceToTargetGatewayForwarder);
            GatewayForwarder targetToSourceGatewayForwarder = new GatewayForwarder(sourceToTargetGatewayForwarder);
            executorService.submit(targetToSourceGatewayForwarder);
        } else {
            GatewayForwarder gatewayForwarder = new GatewayForwarder(socket, gatewayConfiguration, gatewayTunnel);
            executorService.submit(gatewayForwarder);
        }
    }

    public void stop() throws IOException {
        setValid(false);
        try {
            serverSocket.close();
        } catch (Exception e) {
            if (log.isDebugEnabled()) {
                log.debug("Error while closing server socket.", e);
            }
        }
        try {
            if (tunnelServerSocket != null) {
                tunnelServerSocket.close();
            }
        } catch (Exception e) {
            if (log.isDebugEnabled()) {
                log.debug("Error while closing tunnel server socket.", e);
            }
        }
        if (gatewayTunnel != null) {
            gatewayTunnel.close();
        }
        executorService.shutdown();
    }

    public int getPort() {
        return port;
    }

    public boolean isHttpTunnel() {
        return isHttpTunnel;
    }

    private synchronized boolean isValid() {
        return valid;
    }

    private synchronized void setValid(boolean valid) {
        this.valid = valid;
    }

}
