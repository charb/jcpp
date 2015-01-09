package jcpp.rmi.server.connection.statistic;

import java.io.Serializable;
import java.util.concurrent.atomic.AtomicLong;

import jcpp.rmi.server.transport.EndPoint;

public class InvocationStatistic implements Serializable {
    private static final long serialVersionUID = -2863201292423952384L;
    private static long globalId;
    private MethodStatistic methodStatistic;
    private long id;
    private EndPoint callerEndPoint;
    private long startTime;
    private AtomicLong duration;
    private Object[] args;
    private boolean exceptionThrown;
    private Object result;

    public InvocationStatistic(MethodStatistic methodStatistic, EndPoint callerEndPoint, Object[] args) {
        this.id = globalId++;
        this.methodStatistic = methodStatistic;
        this.callerEndPoint = callerEndPoint;
        this.args = args;
        this.startTime = System.currentTimeMillis();
        this.duration = new AtomicLong();
    }

    public void callSucceeded(Object result) {
        this.result = result;
        this.duration.addAndGet(System.currentTimeMillis() - startTime);
        this.methodStatistic.incrementInvocation(this);
    }

    public void callFailed(Object throwable) {
        this.exceptionThrown = true;
        this.result = throwable;
        this.duration.addAndGet(System.currentTimeMillis() - startTime);
        this.methodStatistic.incrementInvocation(this);
    }

    public MethodStatistic getMethodStatistic() {
        return methodStatistic;
    }

    public long getId() {
        return id;
    }

    public EndPoint getCallerEndPoint() {
        return callerEndPoint;
    }

    public long getStartTime() {
        return startTime;
    }

    public AtomicLong getDuration() {
        return duration;
    }

    public Object[] getArgs() {
        return args;
    }

    public boolean isExceptionThrown() {
        return exceptionThrown;
    }

    public Object getResult() {
        return result;
    }

}