package jcpp.rmi.server.transport.statistic;

import java.io.Serializable;
import java.util.concurrent.atomic.AtomicLong;

public class SocketStatistic implements Serializable {
    private static final long serialVersionUID = -3699739190777948151L;
    private int id;
    private EndPointStatistic endPointStatistic;
    private AtomicLong recvApplicationData;
    private AtomicLong recvNetworkData;
    private AtomicLong sentApplicationData;
    private AtomicLong sentNetworkData;

    public SocketStatistic(EndPointStatistic endPointStatistic) {
        this.recvApplicationData = new AtomicLong();
        this.recvNetworkData = new AtomicLong();
        this.sentApplicationData = new AtomicLong();
        this.sentNetworkData = new AtomicLong();
        this.endPointStatistic = endPointStatistic;
    }

    public void setId(int id) {
        this.id = id;
    }

    public int getId() {
        return id;
    }

    public void archive() {
        endPointStatistic.archiveSocketStatistic(this);
    }

    public EndPointStatistic getEndPointStatistic() {
        return endPointStatistic;
    }

    public AtomicLong getRecvApplicationData() {
        return recvApplicationData;
    }

    public AtomicLong getRecvNetworkData() {
        return recvNetworkData;
    }

    public AtomicLong getSentApplicationData() {
        return sentApplicationData;
    }

    public AtomicLong getSentNetworkData() {
        return sentNetworkData;
    }

    public void setRecvApplicationData(AtomicLong recvApplicationData) {
        this.recvApplicationData = recvApplicationData;
    }

    public void setRecvNetworkData(AtomicLong recvNetworkData) {
        this.recvNetworkData = recvNetworkData;
    }

    public void setSentApplicationData(AtomicLong sentApplicationData) {
        this.sentApplicationData = sentApplicationData;
    }

    public void setSentNetworkData(AtomicLong sentNetworkData) {
        this.sentNetworkData = sentNetworkData;
    }

}
