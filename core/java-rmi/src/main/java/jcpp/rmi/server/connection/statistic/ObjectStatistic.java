package jcpp.rmi.server.connection.statistic;

import java.io.Serializable;
import java.util.Hashtable;
import java.util.Map;
import java.util.concurrent.atomic.AtomicLong;

public class ObjectStatistic implements Serializable {
    private static final long serialVersionUID = 6505517697861549854L;
    
    public static enum MethodType {
        REMOTE_METHOD, LOCAL_METHOD, CLIENT_METHOD;
    }

    private ConnectionStatistic connectionStatistic;
    private String id;
    private AtomicLong numInvocation;
    private AtomicLong duration;
    private Map<String, MethodStatistic> remoteMethods;
    private Map<String, MethodStatistic> localMethods;
    private Map<String, MethodStatistic> clientMethods;

    public ObjectStatistic(ConnectionStatistic connectionStatistic, String id) {
        this.connectionStatistic = connectionStatistic;
        this.id = id;
        this.numInvocation = new AtomicLong();
        this.duration = new AtomicLong();
        this.remoteMethods = new Hashtable<String, MethodStatistic>();
        this.localMethods = new Hashtable<String, MethodStatistic>();
        this.clientMethods = new Hashtable<String, MethodStatistic>();
    }

    public synchronized MethodStatistic getMethodStatistic(String name, MethodType methodType) {
        MethodStatistic methodStatistic = null;
        switch (methodType) {
            case REMOTE_METHOD:
                methodStatistic = remoteMethods.get(name);
                break;
            case LOCAL_METHOD:
                methodStatistic = localMethods.get(name);
                break;
            case CLIENT_METHOD:
                methodStatistic = clientMethods.get(name);
                break;
        }
        if(methodStatistic == null) {
            methodStatistic = createMethodStatistic(name, methodType);
        }
        return methodStatistic;
    }

    private MethodStatistic createMethodStatistic(String name, MethodType methodType) {
        MethodStatistic methodStatistic = new MethodStatistic(this, name);
        switch (methodType) {
            case REMOTE_METHOD:
                remoteMethods.put(name, methodStatistic);
                break;
            case LOCAL_METHOD:
                localMethods.put(name, methodStatistic);
                break;
            case CLIENT_METHOD:
                clientMethods.put(name, methodStatistic);
                break;
        }
        return methodStatistic;
    }

    protected void incrementNumInvocation() {
        this.numInvocation.incrementAndGet();
        connectionStatistic.incrementNumInvocation();
    }

    protected void addToDuration(long duration) {
        this.duration.addAndGet(duration);
        connectionStatistic.addToDuration(duration);
    }

    public ConnectionStatistic getConnectionStatistic() {
        return connectionStatistic;
    }

    public String getId() {
        return id;
    }

    public AtomicLong getNumInvocation() {
        return numInvocation;
    }

    public AtomicLong getDuration() {
        return duration;
    }

    public Map<String, MethodStatistic> getRemoteMethods() {
        return remoteMethods;
    }

    public Map<String, MethodStatistic> getLocalMethods() {
        return localMethods;
    }
    
    public Map<String, MethodStatistic> getClientMethods() {
        return clientMethods;
    }
}
