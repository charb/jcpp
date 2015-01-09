package jcpp.rmi.server.transport;

import java.io.IOException;

import java.net.ServerSocket;
import java.net.Socket;

import java.nio.channels.ServerSocketChannel;
import java.nio.channels.SocketChannel;

import java.util.Collections;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;
import java.util.concurrent.Callable;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Future;

import edu.emory.mathcs.backport.java.util.concurrent.ScheduledExecutorService;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import jcpp.rmi.server.gateway.GatewaySocketFactory;
import jcpp.rmi.server.transport.statistic.TransportStatistic;


public class Transport {
    private static Log log = LogFactory.getLog(Transport.class);
    private Set<ConnectionHeaderReader> connectionReaders;
    private ExecutorService executorService;
    private Future<Void> future;
    private EndPoint localEndPoint;
    private Map<EndPoint, Connections> remoteConnectionsMap;
    private ScheduledExecutorService scheduledExecutorService;
    private ServerSocket serverSocket;
    private TransportConfiguration transportConfiguration;
    private ITransportDispatcher transportDispatcher;
    private ITransportRouter transportRouter;
    private TransportStatistic transportStatistic;
    private ServerSocketChannel serverChannel;
    private boolean unexported;

    private ChannelDispatcherProvider dispatcherProvider;


    public Transport(EndPoint localEndPoint, ITransportRouter transportRouter, ITransportDispatcher transportDispatcher, ExecutorService executorService, ScheduledExecutorService scheduledExecutorService,
        TransportConfiguration transportConfiguration) {
        this.localEndPoint = localEndPoint;
        this.transportRouter = transportRouter;
        this.transportDispatcher = transportDispatcher;
        this.scheduledExecutorService = scheduledExecutorService;
        this.remoteConnectionsMap = new HashMap<EndPoint, Connections>();
        this.executorService = executorService;
        this.transportConfiguration = transportConfiguration;
        this.transportStatistic = new TransportStatistic(transportConfiguration);
        this.connectionReaders = Collections.synchronizedSet(new HashSet<ConnectionHeaderReader>());
        this.dispatcherProvider = new ChannelDispatcherProvider(this);
    }


    public synchronized Connections getConnections(EndPoint remoteEndPoint) {
        Connections connections = remoteConnectionsMap.get(remoteEndPoint);
        if (connections == null) {
            connections = new Connections(remoteEndPoint, this);
            remoteConnectionsMap.put(remoteEndPoint, connections);
        }
        return connections;
    }

    public EndPoint getLocalEndPoint() {
        return localEndPoint;
    }

    public ScheduledExecutorService getScheduledExecutorService() {
        return scheduledExecutorService;
    }

    public TransportConfiguration getTransportConfiguration() {
        return transportConfiguration;
    }

    public ITransportDispatcher getTransportDispatcher() {
        return transportDispatcher;
    }

    public ITransportRouter getTransportRouter() {
        return transportRouter;
    }

    public TransportStatistic getTransportStatistic() {
        return transportStatistic;
    }

    public ChannelDispatcherProvider getChannelDispatcherProvider() {
        return dispatcherProvider;
    }

    public void export() throws IOException {
        final boolean nioEnabled = transportConfiguration.getGatewayConfiguration().isNioEnabled();
        if (nioEnabled) {
            serverChannel = GatewaySocketFactory.createServerSocketChannel(localEndPoint.getPort(), transportConfiguration.getGatewayConfiguration());
            localEndPoint.setPort(serverChannel.socket().getLocalPort());
            dispatcherProvider.export();
        } else {
            serverSocket = GatewaySocketFactory.createServerSocket(localEndPoint.getPort(), transportConfiguration.getGatewayConfiguration());
            localEndPoint.setPort(serverSocket.getLocalPort());
        }

        future = executorService.submit(new Callable<Void>() {
                    @Override
                    public Void call() {
                        String socketInfo = nioEnabled ? ("[ServerSocketChannel:" + serverChannel + "]") : ("[ServerSocket:" + serverSocket + "]");
                        Thread.currentThread().setName("Transport Accept Socket thread - [Port:" + localEndPoint.getPort() + "] " + socketInfo);
                        if (nioEnabled) {
                            while (!unexported) {
                                try {
                                    SocketChannel socketChannel = serverChannel.accept();
                                    socketChannel.configureBlocking(false);
                                    socketChannel.socket().setReceiveBufferSize(transportConfiguration.getGatewayConfiguration().getReceiveBufferSize());
                                    socketChannel.socket().setSendBufferSize(transportConfiguration.getGatewayConfiguration().getSendBufferSize());
                                    socketChannel.socket().setSoTimeout(transportConfiguration.getGatewayConfiguration().getReadTimeout());

                                    ChannelDispatcher dispatcher = dispatcherProvider.getDispatcher();
                                    ChannelConnection connection = new ChannelConnection(socketChannel, Transport.this, dispatcher);
                                    connection.start();

                                } catch (Throwable e) {
                                    if (serverChannel.isOpen() && log.isDebugEnabled()) {
                                        log.debug("Error while accepting on the server socket channel", e);
                                    }
                                }
                            }
                        } else {
                            while ((serverSocket != null) && !serverSocket.isClosed()) {
                                try {
                                    Socket socket = serverSocket.accept();
                                    ConnectionHeaderReader connectionHeaderReader = new ConnectionHeaderReader(socket, Transport.this);
                                    connectionReaders.add(connectionHeaderReader);
                                    executorService.submit(connectionHeaderReader);
                                } catch (Throwable throwable) {
                                    if (!serverSocket.isClosed() && log.isDebugEnabled()) {
                                        log.debug("Error while accepting socket.", throwable);
                                    }
                                }
                            }
                        }
                        return null;
                    }
                });
    }

    public void unexport() throws IOException {
        Connections[] connectionsArray;
        ConnectionHeaderReader[] readers;
        synchronized (this) {
            connectionsArray = remoteConnectionsMap.values().toArray(new Connections[0]);
            readers = connectionReaders.toArray(new ConnectionHeaderReader[0]);
        }
        try {
            if (serverSocket != null) {
                serverSocket.close();
            }
        } catch (IOException e) {
            log.debug("Unable to close serverSocket while unexport() in Transport: " + localEndPoint, e);
        }
        try {
            if (serverChannel != null) {
                serverChannel.close();
            }
        } catch (IOException e) {
            log.debug("Unable to close serverChannel while unexport() in Transport: " + localEndPoint, e);
        }
        unexported = true;
        future.cancel(false);
        for (ConnectionHeaderReader reader : readers) {
            reader.unexport();
        }
        for (Connections connections : connectionsArray) {
            connections.killAll();
        }
        if (transportConfiguration.getGatewayConfiguration().isNioEnabled()) {
            dispatcherProvider.unexport();
        }
        synchronized (this) {
            connectionReaders.clear();
            remoteConnectionsMap.clear();
        }
    }

    public ExecutorService getExecutorService() {
        return executorService;
    }

    protected synchronized void remove(ConnectionHeaderReader reader) throws IOException {
        connectionReaders.remove(reader);
    }

    protected synchronized void remove(Connections connections) throws IOException {
        remoteConnectionsMap.remove(connections.getRemoteEndPoint());
    }

}
