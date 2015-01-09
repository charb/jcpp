package jcpp.rmi.server.transport;

import java.io.IOException;

import java.nio.channels.ClosedChannelException;
import java.nio.channels.SelectionKey;
import java.nio.channels.Selector;

import java.util.Iterator;
import java.util.LinkedList;
import java.util.Queue;
import java.util.concurrent.Callable;
import java.util.concurrent.atomic.AtomicBoolean;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import jcpp.rmi.server.transport.ChannelOperationChange.OperationType;


public class ChannelDispatcher implements Callable<Void> {
    private static Log log = LogFactory.getLog(ChannelDispatcher.class);

    private Selector selector;
    private Queue<ChannelOperationChange> pendingChanges;
    private AtomicBoolean isClosed;
    private final int id;

    private Transport transport;


    public ChannelDispatcher(int id, Transport transport) throws IOException {
        this.id = id;
        this.transport = transport;
        this.pendingChanges = new LinkedList<ChannelOperationChange>();
        this.isClosed = new AtomicBoolean();
        this.selector = Selector.open();
    }


    @Override
    public Void call() throws Exception {
        Thread.currentThread().setName("Channel Dispatcher Thread [ID: " + id + "][" + transport.getLocalEndPoint() + "]");
        if (log.isDebugEnabled()) {
            log.debug("Starting " + Thread.currentThread().getName());
        }
        try {
            while (!isClosed.get()) {

                synchronized (this.pendingChanges) {
                    Iterator<ChannelOperationChange> changes = this.pendingChanges.iterator();
                    while (changes.hasNext()) {
                        ChannelOperationChange change = (ChannelOperationChange) changes.next();
                        change.apply(selector);
                    }
                    this.pendingChanges.clear();
                }

                // blocking, waiting for keys to become ready
                int numReady = selector.select(5000);

                if (numReady > 0) {
                    SelectionKey[] keys = selector.selectedKeys().toArray(new SelectionKey[0]);
                    for (SelectionKey key : keys) {
                        selector.selectedKeys().remove(key);
                        if (!key.isValid()) {
                            continue;
                        }

                        if (key.isConnectable()) {
                            this.finishConnection(key);
                        }
                        if (key.isReadable()) {
                            this.read(key);
                        }
                        if (key.isWritable()) {
                            this.write(key);
                        }
                    }
                }
            }

            transport.getChannelDispatcherProvider().removeDispatcher(this);
            for (SelectionKey key : selector.keys()) {
                ((ChannelConnection) key.attachment()).onClose();
                key.cancel();
            }
            selector.close();

        } catch (Exception e) {
            if (log.isDebugEnabled()) {
                log.debug("Error in channel dispatcher thread [ID: " + id + "]", e);
            }

        }
        return null;
    }

    public int getNumRegisteredChannels() {
        return selector.keys().size();
    }

    public void registerAndListen(ChannelConnection connection) throws ClosedChannelException {
        ChannelOperationChange change = new ChannelOperationChange(connection, SelectionKey.OP_READ);
        addPendingChange(change);
    }

    public void registerAndConnect(ChannelConnection connection) throws ClosedChannelException {
        ChannelOperationChange change = new ChannelOperationChange(connection, SelectionKey.OP_CONNECT);
        addPendingChange(change);
    }

    public void announceDisconnect(ChannelConnection connection) {
        ChannelOperationChange change = new ChannelOperationChange(connection, OperationType.DEREGISTER);
        addPendingChange(change);
    }

    public void announceWriteNeed(ChannelConnection connection) {
//        if (!isWriteable(connection)) {
        ChannelOperationChange change = new ChannelOperationChange(connection, OperationType.CHANGEOPS, SelectionKey.OP_WRITE);
        addPendingChange(change);
//        }
    }

    public void announceReadNeed(ChannelConnection connection) {
//        if (!isReadable(connection)) {
        ChannelOperationChange change = new ChannelOperationChange(connection, OperationType.CHANGEOPS, SelectionKey.OP_READ);
        addPendingChange(change);
//        }
    }

    public void close() throws IOException {
        if (!isClosed.getAndSet(true) && (selector != null)) {
            synchronized (pendingChanges) {
                selector.wakeup(); // necessary to get out of loop
            }
        }
    }

    private void addPendingChange(ChannelOperationChange change) {
        synchronized (pendingChanges) {
            pendingChanges.add(change);
            selector.wakeup();
        }
    }

    private void write(SelectionKey key) {
        ChannelConnection connection = (ChannelConnection) key.attachment();
        connection.onWriteEvent();
    }

    private void read(SelectionKey key) {
        ChannelConnection connection = (ChannelConnection) key.attachment();
        connection.onReadEvent();
    }

    private void finishConnection(SelectionKey key) {
        ChannelConnection connection = (ChannelConnection) key.attachment();
        try {
            connection.getChannel().finishConnect();
            connection.setSocketOptions();
        } catch (IOException e) {
            if (log.isDebugEnabled()) {
                log.debug("unable to finish the connection", e);
            }
            announceDisconnect(connection);
        }

    }

}
