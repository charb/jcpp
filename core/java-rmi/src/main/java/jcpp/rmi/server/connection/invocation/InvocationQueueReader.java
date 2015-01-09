package jcpp.rmi.server.connection.invocation;

import java.util.Hashtable;
import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.concurrent.Callable;
import java.util.concurrent.Future;
import java.util.concurrent.atomic.AtomicBoolean;

import edu.emory.mathcs.backport.java.util.concurrent.ScheduledFuture;
import edu.emory.mathcs.backport.java.util.concurrent.TimeUnit;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import jcpp.rmi.server.connection.ConnectionTransportDispatcher.InvocationResult;
import jcpp.rmi.server.connection.ObjectInformation;
import jcpp.rmi.server.connection.Server;
import jcpp.rmi.server.connection.statistic.InvocationStatistic;
import jcpp.rmi.server.connection.statistic.ObjectStatistic.MethodType;
import jcpp.rmi.server.transport.EndPoint;


public class InvocationQueueReader {
    private static Log log = LogFactory.getLog(InvocationQueueReader.class);
    private Map<EndPoint, EndPointInfo> endPointInfos;
    private IInvocationQueueListener invocationQueueListener;
    private Server localServer;


    public InvocationQueueReader(Server localServer, IInvocationQueueListener invocationQueueListener) {
        this.localServer = localServer;
        this.endPointInfos = new Hashtable<EndPoint, EndPointInfo>();
        this.invocationQueueListener = invocationQueueListener;
    }


    public synchronized void add(Set<ObjectInformation> objInfos, EndPoint remoteEndPoint) {
        for (ObjectInformation objInfo : objInfos) {
            EndPointInfo endPointInfo = endPointInfos.get(remoteEndPoint);
            if (endPointInfo == null) {
                endPointInfo = new EndPointInfo(remoteEndPoint);
                endPointInfos.put(remoteEndPoint, endPointInfo);
            }
            endPointInfo.export(objInfo.getId(), objInfo);
        }
    }

    public void unexport() {
        EndPointInfo[] epis = null;
        synchronized (this) {
            epis = endPointInfos.keySet().toArray(new EndPointInfo[0]);
        }
        for (EndPointInfo epi : epis) {
            epi.unexport();
        }
    }

    public synchronized void unexport(EndPoint endPoint) {
        EndPointInfo endPointInfo = endPointInfos.get(endPoint);
        if (endPointInfo != null) {
            endPointInfo.unexport();
        }
    }


    private class EndPointInfo implements Runnable {
        private Map<String, ObjectInformation> exportedObjects;
        private Future<?> future;
        private IInvocationQueue invocationQueue;
        private AtomicBoolean isRunning;
        private EndPoint remoteEndPoint;
        private ScheduledFuture scheduledFuture;


        public EndPointInfo(EndPoint remoteEndPoint) {
            this.remoteEndPoint = remoteEndPoint;
            this.exportedObjects = new Hashtable<String, ObjectInformation>();
            this.invocationQueue = localServer.lookup(remoteEndPoint, IInvocationQueue.class);
            this.isRunning = new AtomicBoolean();
        }


        public void export(String id, ObjectInformation objInfo) {
            if (exportedObjects.size() == 0) {
                scheduledFuture = localServer.getScheduledExecutorService().scheduleAtFixedRate(this, localServer.getConnectionConfiguration().getQueueReaderTimeout(),
                        localServer.getConnectionConfiguration().getQueueReaderTimeout(), TimeUnit.MILLISECONDS);
            }
            exportedObjects.put(id, objInfo);
        }

        public synchronized void unexport() {
            endPointInfos.remove(remoteEndPoint);
            if (future != null) {
                future.cancel(false);
            }
            scheduledFuture.cancel(false);
            scheduledFuture = null;
        }

        @Override
        public void run() {
            if (!isRunning.get()) {
                future = localServer.getExecutorService().submit(new Callable<Void>() {
                            @Override
                            public Void call() {
                                String oldName = Thread.currentThread().getName();
                                try {
                                    isRunning.set(true);
                                    Thread.currentThread().setName("GC.EndPointInfo Runnable Thread - " + this);
                                    List<InvocationItem> itemsList = invocationQueue.pop(localServer.getEndPoint(), localServer.getConnectionConfiguration().getQueuePopTimeout());

                                    if (itemsList != null) {
                                        for (InvocationItem item : itemsList) {
                                            InvocationResult invocationResult = null;
                                            try {
                                                invocationResult = localServer.getConnectionTransportDispatcher().invokeMethod(item.getId(), item.getDigest(), item.getArgs(), remoteEndPoint, MethodType.LOCAL_METHOD);
                                                Object result = invocationResult.getResult();
                                                InvocationStatistic invocationStatistic = invocationResult.getInvocationStatistic();
                                                if (!invocationResult.isExceptionThrown()) {
                                                    if (invocationStatistic != null) {
                                                        Object statResult = localServer.getObjectInformations().getInvocationStatisticObject(result);
                                                        invocationResult.getInvocationStatistic().callSucceeded(statResult);
                                                    }
                                                    invocationQueueListener.invocationSucceded(remoteEndPoint, invocationResult.getObject(), invocationResult.getMethod().getName(), item.getArgs(),
                                                        invocationResult.getResult());
                                                } else {
                                                    if (invocationStatistic != null) {
                                                        invocationStatistic.callFailed(result);
                                                    }
                                                    throw (Throwable) result;
                                                }
                                            } catch (Exception e) {
                                                if (log.isDebugEnabled()) {
                                                    log.debug("Error while reading invocation queue of: " + localServer.getEndPoint() + " at Remote EndPoint: " + remoteEndPoint, e);
                                                }
                                                invocationQueueListener.invocationFailed(remoteEndPoint, item.getId(), item.getDigest(), item.getArgs(), (Throwable) invocationResult.getResult());
                                            }
                                        }
                                    }
                                    String[] ids = exportedObjects.keySet().toArray(new String[0]);
                                    localServer.getGC().ping(remoteEndPoint, ids);
                                } catch (Throwable e) {
                                    if (log.isDebugEnabled()) {
                                        log.debug("Error trying to pop on invocation queue of: " + localServer.getEndPoint() + " at Remote EndPoint: " + remoteEndPoint);
                                    }
                                    invocationQueueListener.pollingFailed(remoteEndPoint, e);
                                } finally {
                                    Thread.currentThread().setName(oldName);
                                    isRunning.set(false);
                                }
                                return null;
                            }
                        });
            }
        }
    }

}
