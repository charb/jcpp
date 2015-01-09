package jcpp.rmi.server.transport;

import java.io.IOException;

import java.util.ArrayList;
import java.util.List;


public class ChannelDispatcherProvider {
    private List<ChannelDispatcher> dispatchers;
    private Transport transport;
    private final int initialPoolSize;
    private final int maxChannelsPerDispatcher;
    private int nextId;
    private int nextChoice;


    public ChannelDispatcherProvider(Transport transport) {
        this.transport = transport;
        this.initialPoolSize = transport.getTransportConfiguration().getGatewayConfiguration().getNioDispatcherPoolSize();
        this.maxChannelsPerDispatcher = transport.getTransportConfiguration().getGatewayConfiguration().getNioDispatcherChannelsLimit();
    }


    public synchronized ChannelDispatcher getDispatcher() throws IOException {
        return getDispatcher(0);
    }

    public void export() throws IOException {
        dispatchers = new ArrayList<ChannelDispatcher>();
        for (int i = 0; i < initialPoolSize; i++) {
            addDispatcher();
        }
    }

    public void unexport() throws IOException {
        ChannelDispatcher[] array = dispatchers.toArray(new ChannelDispatcher[0]);
        for (ChannelDispatcher dispatcher : array) {
            dispatcher.close();
        }
    }

    protected synchronized void removeDispatcher(ChannelDispatcher dispatcher) {
        dispatchers.remove(dispatcher);
    }

    private ChannelDispatcher getDispatcher(int retry) throws IOException {
        ChannelDispatcher dispatcher = dispatchers.get(nextChoice);
        if (retry >= (dispatchers.size())) {
            addDispatcher();
        }
        if (++nextChoice >= dispatchers.size()) {
            nextChoice = 0;
        }
        if (dispatcher.getNumRegisteredChannels() >= maxChannelsPerDispatcher) {
            return getDispatcher(++retry);
        }
        return dispatcher;
    }

    private ChannelDispatcher addDispatcher() throws IOException {
        ChannelDispatcher dispatcher = new ChannelDispatcher(nextId++, transport);
        dispatchers.add(dispatcher);
        transport.getExecutorService().submit(dispatcher);
        return dispatcher;
    }

}
