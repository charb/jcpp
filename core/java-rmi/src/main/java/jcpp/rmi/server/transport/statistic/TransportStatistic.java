package jcpp.rmi.server.transport.statistic;

import java.io.Serializable;
import java.util.Collections;
import java.util.Hashtable;
import java.util.Map;
import java.util.concurrent.atomic.AtomicLong;

import jcpp.rmi.server.statistic.LimitedLinkedHashMap;
import jcpp.rmi.server.transport.EndPoint;
import jcpp.rmi.server.transport.TransportConfiguration;

public class TransportStatistic implements Serializable {
    private static final long serialVersionUID = -5827045915015075450L;
    private AtomicLong requestedConnection;
    private AtomicLong requestedConnectionKilled;
    private AtomicLong receivedConnection;
    private AtomicLong receivedConnectionKilled;
    private Map<EndPoint, EndPointStatistic> connectionsSnapshot;
    private Map<EndPoint, EndPointStatistic> connectionsHistory;
    private TransportConfiguration transportConfiguration;

    public TransportStatistic(TransportConfiguration transportConfiguration) {
        this.transportConfiguration = transportConfiguration;
        this.requestedConnection = new AtomicLong();
        this.requestedConnectionKilled = new AtomicLong();
        this.receivedConnection = new AtomicLong();
        this.receivedConnectionKilled = new AtomicLong();
        this.connectionsSnapshot = new Hashtable<EndPoint, EndPointStatistic>();
        this.connectionsHistory = Collections.synchronizedMap(new LimitedLinkedHashMap<EndPoint, EndPointStatistic>(transportConfiguration.getTransportStatisticHistorySize(), transportConfiguration.getTransportStatisticHistorySize()));
    }

    public SocketStatistic createConnectionStatistic(EndPoint endPoint) {
        EndPointStatistic endPointStatistic = getSnapshotEndPointStatistic(endPoint);
        return endPointStatistic.createSocketStatistic();
    }

    public synchronized EndPointStatistic getSnapshotEndPointStatistic(EndPoint endPoint) {
        EndPointStatistic endPointStatistic;
        if((endPointStatistic = connectionsSnapshot.get(endPoint)) == null) {
            endPointStatistic = new EndPointStatistic(this, endPoint);
            connectionsSnapshot.put(endPoint, endPointStatistic);
        }
        return endPointStatistic;
    }

    public synchronized void archiveEndPointStatistic(EndPointStatistic endPointStatistic) {
        connectionsSnapshot.remove(endPointStatistic.getEndPoint());
        EndPointStatistic prevEndPointStatistic = connectionsHistory.get(endPointStatistic.getEndPoint());
        if(prevEndPointStatistic != null) {
            prevEndPointStatistic.addStatistics(endPointStatistic);
        } else {
            connectionsHistory.put(endPointStatistic.getEndPoint(), endPointStatistic);
        }
    }

    public synchronized void archiveEndPoint(EndPoint endPoint) {
        EndPointStatistic endPointStatistic = connectionsSnapshot.remove(endPoint);
        if(endPointStatistic != null) {
            EndPointStatistic prevEndPointStatistic = connectionsHistory.get(endPoint);
            if(prevEndPointStatistic != null) {
                prevEndPointStatistic.addStatistics(endPointStatistic);
            } else {
                connectionsHistory.put(endPoint, endPointStatistic);
            }
        }
    }

    public long getTotalReceivedApplicationData() {
        EndPointStatistic historyStatistics[];
        EndPointStatistic snapshotStatistics[];
        synchronized (this) {
            historyStatistics = connectionsHistory.values().toArray(new EndPointStatistic[0]);
            snapshotStatistics = connectionsSnapshot.values().toArray(new EndPointStatistic[0]);
        }
        long byteCount = 0;
        for(EndPointStatistic endPointStatistic : historyStatistics) {
            byteCount += endPointStatistic.getTotalRecvApplicationData();
        }
        for(EndPointStatistic endPointStatistic : snapshotStatistics) {
            byteCount += endPointStatistic.getTotalRecvApplicationData();
        }
        return byteCount;
    }

    public long getTotalReceivedNetworkData() {
        EndPointStatistic historyStatistics[];
        EndPointStatistic snapshotStatistics[];
        synchronized (this) {
            historyStatistics = connectionsHistory.values().toArray(new EndPointStatistic[0]);
            snapshotStatistics = connectionsSnapshot.values().toArray(new EndPointStatistic[0]);
        }
        long byteCount = 0;
        for(EndPointStatistic endPointStatistic : historyStatistics) {
            byteCount += endPointStatistic.getTotalRecvNetworkData();
        }
        for(EndPointStatistic endPointStatistic : snapshotStatistics) {
            byteCount += endPointStatistic.getTotalRecvNetworkData();
        }
        return byteCount;
    }

    public long getTotalSentApplicationData() {
        EndPointStatistic historyStatistics[];
        EndPointStatistic snapshotStatistics[];
        synchronized (this) {
            historyStatistics = connectionsHistory.values().toArray(new EndPointStatistic[0]);
            snapshotStatistics = connectionsSnapshot.values().toArray(new EndPointStatistic[0]);
        }
        long byteCount = 0;
        for(EndPointStatistic endPointStatistic : historyStatistics) {
            byteCount += endPointStatistic.getTotalSentApplicationData();
        }
        for(EndPointStatistic endPointStatistic : snapshotStatistics) {
            byteCount += endPointStatistic.getTotalSentApplicationData();
        }
        return byteCount;
    }

    public long getTotalSentNetworkData() {
        EndPointStatistic historyStatistics[];
        EndPointStatistic snapshotStatistics[];
        synchronized (this) {
            historyStatistics = connectionsHistory.values().toArray(new EndPointStatistic[0]);
            snapshotStatistics = connectionsSnapshot.values().toArray(new EndPointStatistic[0]);
        }
        long byteCount = 0;
        for(EndPointStatistic endPointStatistic : historyStatistics) {
            byteCount += endPointStatistic.getTotalSentNetworkData();
        }
        for(EndPointStatistic endPointStatistic : snapshotStatistics) {
            byteCount += endPointStatistic.getTotalSentNetworkData();
        }
        return byteCount;
    }

    public AtomicLong getRequestedConnection() {
        return requestedConnection;
    }

    public AtomicLong getRequestedConnectionKilled() {
        return requestedConnectionKilled;
    }

    public AtomicLong getReceivedConnection() {
        return receivedConnection;
    }

    public AtomicLong getReceivedConnectionKilled() {
        return receivedConnectionKilled;
    }

    public Map<EndPoint, EndPointStatistic> getConnectionsSnapshot() {
        return connectionsSnapshot;
    }

    public Map<EndPoint, EndPointStatistic> getConnectionsHistory() {
        return connectionsHistory;
    }

    public TransportConfiguration getTransportConfiguration() {
        return transportConfiguration;
    }

}
