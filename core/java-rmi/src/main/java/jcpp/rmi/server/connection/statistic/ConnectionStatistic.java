package jcpp.rmi.server.connection.statistic;

import java.io.Serializable;
import java.util.Collections;
import java.util.HashSet;
import java.util.Hashtable;
import java.util.Map;
import java.util.Set;
import java.util.concurrent.atomic.AtomicLong;

import jcpp.rmi.server.connection.ConnectionConfiguration;
import jcpp.rmi.server.statistic.LimitedLinkedHashMap;
import jcpp.rmi.server.transport.EndPoint;
import jcpp.rmi.server.transport.statistic.TransportStatistic;

public class ConnectionStatistic implements Serializable {
    private static final long serialVersionUID = 3430847020866273722L;
    private TransportStatistic transportStatistic;
    private AtomicLong numInvocation;
    private AtomicLong duration;
    private Map<String, ObjectStatistic> snapshotStatistics;
    private Map<String, ObjectStatistic> historyStatistics;
    private Map<EndPoint, Set<String>> endPointObjectStatistics;
    private ConnectionConfiguration connectionConfiguration;

    public ConnectionStatistic(TransportStatistic transportStatistic, ConnectionConfiguration connectionConfiguration) {
        this.transportStatistic = transportStatistic;
        this.connectionConfiguration = connectionConfiguration;
        this.numInvocation = new AtomicLong();
        this.duration = new AtomicLong();
        this.snapshotStatistics = new Hashtable<String, ObjectStatistic>();
        this.historyStatistics = Collections.synchronizedMap(new LimitedLinkedHashMap<String, ObjectStatistic>(connectionConfiguration.getConnectionStatisticHistorySize(), connectionConfiguration.getConnectionStatisticHistorySize()));
        this.endPointObjectStatistics = new Hashtable<EndPoint, Set<String>>();
    }

    public synchronized ObjectStatistic getObjectStatistic(String objectId, EndPoint endPoint) {
        ObjectStatistic objectStatistic = snapshotStatistics.get(objectId);
        if(objectStatistic == null) {
            objectStatistic = createObjectStatistic(objectId, endPoint);
        }
        return objectStatistic;

    }

    private ObjectStatistic createObjectStatistic(String objectId, EndPoint endPoint) {
        ObjectStatistic objectStatistic = new ObjectStatistic(this, objectId);
        snapshotStatistics.put(objectId, objectStatistic);
        Set<String> set = endPointObjectStatistics.get(endPoint);
        if(set == null) {
            set = new HashSet<String>();
            endPointObjectStatistics.put(endPoint, set);
        }
        set.add(objectId);
        return objectStatistic;
    }

    public void archiveObjectStatistic(String objectId) {
        ObjectStatistic objectStatistic = snapshotStatistics.remove(objectId);
        if(objectStatistic != null) {
            historyStatistics.put(objectId, objectStatistic);
        }
    }

    protected void incrementNumInvocation() {
        this.numInvocation.incrementAndGet();
    }

    protected void addToDuration(long duration) {
        this.duration.addAndGet(duration);
    }

    public TransportStatistic getTransportStatistic() {
        return transportStatistic;
    }

    public AtomicLong getNumInvocation() {
        return numInvocation;
    }

    public AtomicLong getDuration() {
        return duration;
    }

    public Map<String, ObjectStatistic> getSnapshotStatistics() {
        return snapshotStatistics;
    }

    public Map<String, ObjectStatistic> getHistoryStatistics() {
        return historyStatistics;
    }

    public Map<EndPoint, Set<String>> getEndPointObjectStatistics() {
        return endPointObjectStatistics;
    }

    public ConnectionConfiguration getConnectionConfiguration() {
        return connectionConfiguration;
    }
}
