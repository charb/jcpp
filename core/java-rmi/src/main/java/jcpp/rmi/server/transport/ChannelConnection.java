package jcpp.rmi.server.transport;

import java.io.DataInputStream;
import java.io.EOFException;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

import java.net.Socket;
import java.net.SocketException;
import java.net.UnknownHostException;

import java.nio.ByteBuffer;
import java.nio.channels.ClosedChannelException;
import java.nio.channels.SelectionKey;
import java.nio.channels.Selector;
import java.nio.channels.SocketChannel;

import java.util.Collections;
import java.util.LinkedList;
import java.util.List;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.Callable;
import java.util.concurrent.Future;
import java.util.concurrent.LinkedBlockingQueue;
import java.util.concurrent.atomic.AtomicBoolean;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import jcpp.rmi.server.compression.CompressionInputStream;
import jcpp.rmi.server.compression.CompressionOutputStream;
import jcpp.rmi.server.gateway.GatewayCompressionInputStream;
import jcpp.rmi.server.gateway.GatewayCompressionOutputStream;
import jcpp.rmi.server.gateway.GatewayConfiguration;
import jcpp.rmi.server.gateway.GatewaySocketFactory;
import jcpp.rmi.server.gateway.Route;
import jcpp.rmi.server.statistic.StatisticInputStream;
import jcpp.rmi.server.statistic.StatisticOutputStream;
import jcpp.rmi.server.transport.statistic.SocketStatistic;


public class ChannelConnection extends Connection {
    private static Log log = LogFactory.getLog(ChannelConnection.class);

    private SocketChannel channel;

    private BlockingQueue<ReadQueueEntry> readQueue;
    private List<ByteBuffer> writeQueue;
    private ChannelDispatcher dispatcher;
    private InputStream channelInputStream;
    private OutputStream internalOutputStream;
    private DataInputStream dataInputStream;

    private final boolean initiator;
    private AtomicBoolean magicNumberReaderStarted;
    private AtomicBoolean msgTypeReceived;
    private EndPoint remoteEndPoint;

    private ChannelOutputStream channelOutputStream;

    private Future<Void> magicNumberReader;
    private Object readQueueLock;


    public ChannelConnection(Route route, Connections connections, SocketStatistic socketStatistic, GatewayConfiguration gatewayConfiguration, ChannelDispatcher dispatcher) throws UnknownHostException, IOException,
        ClassNotFoundException {
        super(route, connections, socketStatistic, gatewayConfiguration);
        this.dispatcher = dispatcher;
        channel = GatewaySocketFactory.createSocketChannel(route, gatewayConfiguration);
        channel.socket().setSoTimeout(connections.getTransport().getTransportConfiguration().getSocketTimeout());
        setSocketOptions();
        this.initiator = true;
        init();
        dispatcher.registerAndConnect(this);
    }

    public ChannelConnection(SocketChannel channel, Transport transport, ChannelDispatcher dispatcher) {
        super(transport, null, transport.getTransportConfiguration().getGatewayConfiguration());
        this.channel = channel;
        this.dispatcher = dispatcher;
        this.initiator = false;
        init();

    }


    @Override
    public boolean readOk() throws IOException {
        try {
            return super.readOk();
        } catch (Throwable t) {
            throw new IOException(t);
        }
    }

    public void start() throws ClosedChannelException {
        dispatcher.registerAndListen(this);
    }

    public SocketChannel getChannel() {
        return channel;
    }

    public BlockingQueue<ReadQueueEntry> getReadQueue() {
        return readQueue;
    }

    public SelectionKey getKey(Selector selector) {
        return getChannel().keyFor(selector);
    }

    public void write(ByteBuffer buffer) {
        if (buffer != null) {
            writeQueue.add(buffer);
            dispatcher.announceWriteNeed(this);
        }
    }

    public void close() {
        dispatcher.announceDisconnect(this);
    }

    protected void setSocketOptions() throws SocketException {
        channel.socket().setTcpNoDelay(true);
        channel.socket().setKeepAlive(true);
    }

    protected void onWriteEvent() {
        try {
            while (!writeQueue.isEmpty()) {
                ByteBuffer buffer = writeQueue.get(0);
                channel.write(buffer);
                if (buffer.remaining() > 0) {
                    break;
                }
                writeQueue.remove(0);
            }

            synchronized (writeQueue) {
                if (writeQueue.isEmpty()) {
                    // synchronized is needed in case write() is called and executes before next line executes
                    dispatcher.announceReadNeed(this);
                }
            }
        } catch (Exception e) {
            if (log.isDebugEnabled()) {
                log.debug(e, e);
            }
            dispatcher.announceDisconnect(this);
        }
    }

    protected void onReadEvent() {
        ByteBuffer buffer = ByteBuffer.allocate(gatewayConfiguration.getReceiveBufferSize()); // TODO cache?
        int read = 0;
        try {
            for (int r = 1; (r > 0) && (buffer.remaining() > 0);) {
                r = channel.read(buffer);
                if (r == -1) {
                    if (read > 0) {
                        break;
                    } else {
                        read = -1;
                    }
                } else {
                    read += r;
                }
            }

        } catch (Exception e) {
            if (log.isDebugEnabled()) {
                log.debug("Unable to process read event on channel " + channel, e);
            }
            synchronized (readQueueLock) {
                readQueue.add(new ReadQueueEntry(null));
                dispatcher.announceDisconnect(this);
                return;
            }
        }

        if (read < 0) {
            synchronized (readQueueLock) {
                readQueue.add(new ReadQueueEntry(null));
                dispatcher.announceDisconnect(this);
            }
        } else {
            // Note: ChannelInputStream modified so as to render
            //       slice buffer useless
            // ByteBuffer readBuffer = sliceReadBuffer(buffer, read);
            synchronized (readQueueLock) {
                readQueue.add(new ReadQueueEntry(buffer));
            }

            if (!initiator) {
                if (!magicNumberReaderStarted.getAndSet(true)) {
                    magicNumberReader = transport.getExecutorService().submit(new Callable<Void>() {
                                @Override
                                public Void call() throws Exception {
                                    String oldName = Thread.currentThread().getName();
                                    Thread.currentThread().setName("Magic Number Reader " + transport.getLocalEndPoint());
                                    try {
                                        int magicNumber = getDataInputStream().readInt();
                                        if (magicNumber == TransportConfiguration.getMagicNumber()) {
                                            remoteEndPoint = new EndPoint(getDataInputStream());
                                            SocketStatistic statistic = transport.getTransportStatistic().createConnectionStatistic(remoteEndPoint);
                                            setSocketStatistic(statistic);
                                            sendOk();
                                        } else {
                                            if (log.isDebugEnabled()) {
                                                log.debug("Incorrect Magic Number (" + magicNumber + "). Socket - " + getSocketInternal());
                                            }
                                            dispatcher.announceDisconnect(ChannelConnection.this);
                                        }
                                    } catch (IOException e) {
                                        if (log.isDebugEnabled()) {
                                            log.debug("Unable to process read event on channel " + channel, e);
                                        }
                                        dispatcher.announceDisconnect(ChannelConnection.this);

                                    } finally {
                                        Thread.currentThread().setName(oldName);
                                    }
                                    return null;
                                }
                            });
                } else if (!msgTypeReceived.getAndSet(true)) {
                    transport.getExecutorService().submit(new Callable<Void>() {
                            @Override
                            public Void call() throws Exception {
                                String oldName = Thread.currentThread().getName();
                                Thread.currentThread().setName("Channel Connection Reader " + transport.getLocalEndPoint());

                                try {
                                    magicNumberReader.get();
                                    do {
                                        byte msgType = getDataInputStream().readByte();
                                        if (msgType == TransportConfiguration.MSG_TYPE_PING) {
                                            sendOk();
                                        } else if (msgType == TransportConfiguration.MSG_TYPE_CALL) {
                                            try {
                                                transport.getTransportDispatcher().dispatch(remoteEndPoint, transport.getLocalEndPoint(), ChannelConnection.this);
                                                getOutputStream().flush();
                                            } catch (Throwable throwable) {
                                                if (log.isDebugEnabled()) {
                                                    log.debug("Error in transport dispatcher while dispatching from: " + remoteEndPoint, throwable);
                                                }
                                                throw new Exception(throwable); // dispatch throws Throwable, but Void call() can only throw Exception
                                            }

                                        } else {
                                            if (log.isDebugEnabled()) {
                                                log.debug("Unknown message type: " + msgType + ". Socket: " + getSocketInternal());
                                            }
                                            throw new EOFException("Unknown message type: " + msgType + ". Socket: " + getSocketInternal());
                                        }
                                    } while (continueRequest());

                                } catch (IOException e) {
                                    if (log.isDebugEnabled()) {
                                        log.debug("Unable to process read event on channel " + channel, e);
                                    }
                                    dispatcher.announceDisconnect(ChannelConnection.this);

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

    @Override
    protected void sendConnectionHeader() throws IOException {
        super.sendConnectionHeader();
    }

    protected void onClose() {
        try {
            if (channel.isOpen()) {
                channel.close();
            }
        } catch (Exception e) {
            if (log.isDebugEnabled()) {
                log.debug("error occured by closing socket channel", e);
            }
        }
    }

    @Override
    protected OutputStream getOuputStreamInternal() throws IOException {
        if (internalOutputStream == null) {
            channelOutputStream = new ChannelOutputStream(this);
            boolean isGateway = false;
            if (initiator) {
                internalOutputStream = new StatisticOutputStream(new GatewayCompressionOutputStream(channelOutputStream, route, gatewayConfiguration.isCompressionEnabled() && !isGateway,
                        gatewayConfiguration.getSendBufferSize(), 2 * gatewayConfiguration.getSendBufferSize(), gatewayConfiguration.getCompressionThreshold(), gatewayConfiguration.getCompressionLevel()));
            } else {
                if (gatewayConfiguration.isCompressionEnabled() && !isGateway) {
                    internalOutputStream = new StatisticOutputStream(new CompressionOutputStream(channelOutputStream, gatewayConfiguration.getReceiveBufferSize(), 2 * gatewayConfiguration.getReceiveBufferSize(),
                            gatewayConfiguration.getCompressionThreshold(), gatewayConfiguration.getCompressionLevel()));
                } else {
                    internalOutputStream = new StatisticOutputStream(channelOutputStream);
                }
            }
        }
        return internalOutputStream;

    }

    @Override
    protected InputStream getInputStreamInternal() throws IOException {
        if (channelInputStream == null) {
            channelInputStream = new ChannelInputStream(this);
            boolean isGateway = false;
            if (initiator) {
                if (gatewayConfiguration.isCompressionEnabled()) {
                    channelInputStream = new StatisticInputStream(new CompressionInputStream(channelInputStream, gatewayConfiguration.getSendBufferSize()));
                } else {
                    channelInputStream = new StatisticInputStream(channelInputStream);
                }
            } else {
                try {
                    channelInputStream = new GatewayCompressionInputStream(channelInputStream, gatewayConfiguration.isCompressionEnabled() && !isGateway, gatewayConfiguration);
                } catch (ClassNotFoundException e) {
                    throw new RuntimeException(e);
                }
                this.route = ((GatewayCompressionInputStream) channelInputStream).getRoute();
                this.channelInputStream = new StatisticInputStream(channelInputStream);
            }
        }
        return channelInputStream;
    }

    @Override
    protected void killInternal() throws IOException {
        dispatcher.announceDisconnect(this);
    }

    @Override
    protected boolean isSocketClosed() {
        return !channel.isOpen();
    }

    @Override
    protected Socket getSocketInternal() {
        return channel.socket();
    }

    private boolean continueRequest() {
        synchronized (readQueueLock) {
            boolean b = readQueue.size() > 0;
            if (b) {
                msgTypeReceived.set(true);
                return true;
            } else {
                msgTypeReceived.set(false);
                return false;
            }
        }
    }

    private DataInputStream getDataInputStream() throws IOException {
        if (dataInputStream == null) {
            dataInputStream = new DataInputStream(getInputStreamInternal());
        }
        return dataInputStream;
    }

    private ByteBuffer sliceReadBuffer(ByteBuffer buffer, int read) {
        ByteBuffer readData = null;
        if (read > 0) {
            buffer.limit(buffer.position());
            buffer.position(buffer.position() - read);
            readData = buffer.slice();
        } else {
            readData = ByteBuffer.allocate(0);
        }
        return readData;
    }

    private void init() {
        this.readQueue = new LinkedBlockingQueue<ReadQueueEntry>();
        this.writeQueue = Collections.synchronizedList(new LinkedList<ByteBuffer>());
        this.msgTypeReceived = new AtomicBoolean();
        this.magicNumberReaderStarted = new AtomicBoolean();
        this.readQueueLock = new Object();
    }
}
