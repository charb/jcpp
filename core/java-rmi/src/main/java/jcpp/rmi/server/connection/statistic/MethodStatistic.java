package jcpp.rmi.server.connection.statistic;

import java.io.Serializable;
import java.util.Collections;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;
import java.util.concurrent.atomic.AtomicLong;

import jcpp.rmi.server.statistic.LimitedLinkedHashMap;
import jcpp.rmi.server.transport.EndPoint;

public class MethodStatistic implements Serializable {
    private static final long serialVersionUID = 2084350334182306716L;
    private ObjectStatistic objectStatistic;
    private String name;
    private AtomicLong numInvocation;
    private AtomicLong duration;
    private Set<InvocationStatistic> snapshotStatistics;
    private Map<Long, InvocationStatistic> historyStatistics;

    public MethodStatistic(ObjectStatistic objectStatistic, String name) {
        this.objectStatistic = objectStatistic;
        this.name = name;
        this.snapshotStatistics = Collections.synchronizedSet(new HashSet<InvocationStatistic>());
        int historySize = objectStatistic.getConnectionStatistic().getConnectionConfiguration().getMethodStatisticHistorySize();
        this.historyStatistics = Collections.synchronizedMap(new LimitedLinkedHashMap<Long, InvocationStatistic>(historySize, historySize));
        this.numInvocation = new AtomicLong();
        this.duration = new AtomicLong();
    }

    public synchronized InvocationStatistic createInvocationStatistic(EndPoint callerEndPoint, Object[] args) {
        InvocationStatistic invocationStatistic = new InvocationStatistic(this, callerEndPoint, args);
        snapshotStatistics.add(invocationStatistic);
        incrementNumInvocation();
        return invocationStatistic;
    }

    public void incrementInvocation(InvocationStatistic invocationStatistic) {
        addToDuration(invocationStatistic.getDuration().get());
        snapshotStatistics.remove(invocationStatistic);
        historyStatistics.put(Long.valueOf(invocationStatistic.getId()), invocationStatistic);
    }

    private void incrementNumInvocation() {
        numInvocation.incrementAndGet();
        objectStatistic.incrementNumInvocation();
    }

    private void addToDuration(long duration) {
        this.duration.addAndGet(duration);
        objectStatistic.addToDuration(duration);
    }

    public ObjectStatistic getObjectStatistic() {
        return objectStatistic;
    }

    public String getName() {
        return name;
    }

    public AtomicLong getNumInvocation() {
        return numInvocation;
    }

    public AtomicLong getDuration() {
        return duration;
    }

    public Set<InvocationStatistic> getSnapshotStatistics() {
        return snapshotStatistics;
    }

    public Map<Long, InvocationStatistic> getHistoryStatistics() {
        return historyStatistics;
    }

}
