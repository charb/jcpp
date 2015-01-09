package jcpp.rmi.server.transport.statistic;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Map;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.concurrent.atomic.AtomicLong;

import jcpp.rmi.server.statistic.LimitedLinkedHashMap;
import jcpp.rmi.server.transport.EndPoint;

public class EndPointStatistic implements Serializable {
    private static final long serialVersionUID = 4709822026332970111L;
    private TransportStatistic transportStatistic;
    private EndPoint endPoint;
    private AtomicInteger freeConnections;
    private AtomicInteger takenConnections;
    private Map<Integer, SocketStatistic> historySocketStatistics;
    private List<SocketStatistic> snapshotSocketStatistics;//TODO snchronizedSet() c'est mieux
    // The following AtomicLongs contain the byte count of all previously disregarded SocketStatistics + those in historySocketStatistics
    private AtomicLong oldRecvApplicationData;
    private AtomicLong oldRecvNetworkData;
    private AtomicLong oldSentApplicationData;
    private AtomicLong oldSentNetworkData;

    public EndPointStatistic(TransportStatistic transportStatistic, EndPoint endPoint) {
        this.transportStatistic = transportStatistic;
        this.endPoint = endPoint;
        this.freeConnections = new AtomicInteger();
        this.takenConnections = new AtomicInteger();
        int historySize = transportStatistic.getTransportConfiguration().getEndPointStatisticHistorySize();
        this.historySocketStatistics = Collections.synchronizedMap(new LimitedLinkedHashMap<Integer, SocketStatistic>(historySize, historySize));
        this.snapshotSocketStatistics = new ArrayList<SocketStatistic>();
        this.oldRecvApplicationData = new AtomicLong();
        this.oldRecvNetworkData = new AtomicLong();
        this.oldSentApplicationData = new AtomicLong();
        this.oldSentNetworkData = new AtomicLong();
    }

    public synchronized SocketStatistic createSocketStatistic() {
        SocketStatistic socketStatistic = new SocketStatistic(this);
        snapshotSocketStatistics.add(socketStatistic);
        return socketStatistic;
    }

    public synchronized void archiveSocketStatistic(SocketStatistic socketStatistic) {
        snapshotSocketStatistics.remove(socketStatistic);
        historySocketStatistics.put(Integer.valueOf(socketStatistic.getId()), socketStatistic);
        oldRecvApplicationData.addAndGet(socketStatistic.getRecvApplicationData().get());
        oldRecvNetworkData.addAndGet(socketStatistic.getRecvNetworkData().get());
        oldSentApplicationData.addAndGet(socketStatistic.getSentApplicationData().get());
        oldSentNetworkData.addAndGet(socketStatistic.getSentNetworkData().get());
    }

    protected void addStatistics(EndPointStatistic endPointStatistic) {
        oldRecvApplicationData.addAndGet(endPointStatistic.getOldRecvApplicationData().get());
        oldRecvNetworkData.addAndGet(endPointStatistic.getOldRecvNetworkData().get());
        oldSentApplicationData.addAndGet(endPointStatistic.getOldSentApplicationData().get());
        oldSentNetworkData.addAndGet(endPointStatistic.getOldSentNetworkData().get());
        historySocketStatistics.putAll(endPointStatistic.getHistorySocketStatistics());
    }

    public EndPoint getEndPoint() {
        return endPoint;
    }
    public AtomicInteger getFreeConnections() {
        return freeConnections;
    }
    public AtomicInteger getTakenConnections() {
        return takenConnections;
    }

    public Map<Integer, SocketStatistic> getHistorySocketStatistics() {
        return historySocketStatistics;
    }

    public SocketStatistic[] getSnapshotSocketStatistics() {
        return snapshotSocketStatistics.toArray(new SocketStatistic[0]);
    }

    public AtomicLong getOldRecvApplicationData() {
        return oldRecvApplicationData;
    }
    public long getTotalRecvApplicationData() {
        long byteCount = 0;
        SocketStatistic socketStatistics[];
        synchronized (this) {
            socketStatistics = snapshotSocketStatistics.toArray(new SocketStatistic[0]);
        }
        for(SocketStatistic socketStatistic : socketStatistics) {
            byteCount += socketStatistic.getRecvApplicationData().get();
        }
        return byteCount + oldRecvApplicationData.get();
    }

    public AtomicLong getOldRecvNetworkData() {
        return oldRecvNetworkData;
    }
    public long getTotalRecvNetworkData() {
        long byteCount = 0;
        SocketStatistic socketStatistics[];
        synchronized (this) {
            socketStatistics = snapshotSocketStatistics.toArray(new SocketStatistic[0]);
        }
        for(SocketStatistic socketStatistic : socketStatistics) {
            byteCount += socketStatistic.getRecvNetworkData().get();
        }
        return byteCount + oldRecvNetworkData.get();
    }

    public AtomicLong getOldSentApplicationData() {
        return oldSentApplicationData;
    }
    public long getTotalSentApplicationData() {
        long byteCount = 0;
        SocketStatistic socketStatistics[];
        synchronized (this) {
            socketStatistics = snapshotSocketStatistics.toArray(new SocketStatistic[0]);
        }
        for(SocketStatistic socketStatistic : socketStatistics) {
            byteCount += socketStatistic.getSentApplicationData().get();
        }
        return byteCount + oldSentApplicationData.get();
    }

    public AtomicLong getOldSentNetworkData() {
        return oldSentNetworkData;
    }
    public long getTotalSentNetworkData() {
        long byteCount = 0;
        SocketStatistic socketStatistics[];
        synchronized (this) {
            socketStatistics = snapshotSocketStatistics.toArray(new SocketStatistic[0]);
        }
        for(SocketStatistic socketStatistic : socketStatistics) {
            byteCount += socketStatistic.getSentNetworkData().get();
        }
        return byteCount + oldSentNetworkData.get();
    }
}