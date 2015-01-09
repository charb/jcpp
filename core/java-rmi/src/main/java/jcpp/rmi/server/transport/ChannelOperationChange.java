package jcpp.rmi.server.transport;

import java.nio.channels.ClosedChannelException;
import java.nio.channels.SelectionKey;
import java.nio.channels.Selector;
import java.nio.channels.SocketChannel;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;


public class ChannelOperationChange {
    private static Log log = LogFactory.getLog(ChannelOperationChange.class);


    public enum OperationType {
        DEREGISTER, REGISTER, CHANGEOPS
    }


    private ChannelConnection connection;
    private OperationType type;
    private int ops;


    public ChannelOperationChange() {
    }

    public ChannelOperationChange(ChannelConnection connection, OperationType type) {
        this.connection = connection;
        this.type = type;
    }

    public ChannelOperationChange(ChannelConnection connection, OperationType type, int ops) {
        this.connection = connection;
        this.type = type;
        this.ops = ops;
    }

    public ChannelOperationChange(ChannelConnection connection, int ops) {
        this.type = OperationType.REGISTER;
        this.connection = connection;
        this.ops = ops;
    }


    public void apply(Selector selector) {
        SelectionKey key = getChannel().keyFor(selector);

        switch (getType()) {

        case CHANGEOPS: {
            if ((key != null) && key.isValid()) {
                key.interestOps(getOps());
            }
            break;
        }

        case REGISTER: {
            try {
                getChannel().register(selector, getOps(), connection);
            } catch (ClosedChannelException e) {
                if (log.isDebugEnabled()) {
                    log.debug("error occured during channel registration", e);
                }
                if (key != null) {
                    key.cancel();
                }
            }
            break;
        }

        case DEREGISTER: {
            if (key != null) {
                key.cancel();
            }

            connection.onClose();
            break;
        }

        }
    }

    public SocketChannel getChannel() {
        return connection.getChannel();
    }

    public OperationType getType() {
        return type;
    }

    public int getOps() {
        return ops;
    }

    @Override
    public String toString() {
        return String.format("Channel Change [type %s, ops %s, channel %s]", type, "" + ops, getChannel());
    }

}
