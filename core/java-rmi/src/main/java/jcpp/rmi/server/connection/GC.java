package jcpp.rmi.server.connection;

import java.util.Hashtable;
import java.util.Map;
import java.util.Set;
import java.util.concurrent.Callable;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Future;
import java.util.concurrent.atomic.AtomicBoolean;

import edu.emory.mathcs.backport.java.util.concurrent.ScheduledExecutorService;
import edu.emory.mathcs.backport.java.util.concurrent.ScheduledFuture;
import edu.emory.mathcs.backport.java.util.concurrent.TimeUnit;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import jcpp.rmi.server.connection.invocation.InvocationQueueReader;
import jcpp.rmi.server.transport.EndPoint;


public class GC implements IGC {
    private static Log log = LogFactory.getLog(GC.class);

    private ConnectionConfiguration connectionConfiguration;
    private Map<EndPoint, EndPointInfo> endPointInfos;
    private ExecutorService executorService;
    private InvocationQueueReader invocationQueueReader;
    private ScheduledExecutorService scheduledExecutorService;


    public GC(ExecutorService executorService, ScheduledExecutorService scheduledExecutorService, InvocationQueueReader invocationQueueReader, ConnectionConfiguration connectionConfiguration) {
        this.endPointInfos = new Hashtable<EndPoint, EndPointInfo>();
        this.executorService = executorService;
        this.scheduledExecutorService = scheduledExecutorService;
        this.invocationQueueReader = invocationQueueReader;
        this.connectionConfiguration = connectionConfiguration;
    }


    /**
     * This function is for testing purposes.
     */
    @Override
    public synchronized EndPoint[] getExportedEndPoints() {
        return endPointInfos.keySet().toArray(new EndPoint[0]);
    }

    @Override
    public boolean[] ping(EndPoint endPoint, String[] ids) throws Throwable {
        boolean[] returnPing = new boolean[ids.length];
        EndPointInfo endPointInfo = endPointInfos.get(endPoint);
        if (endPointInfo != null) {
            endPointInfo.ping(returnPing, ids);
        }
        return returnPing;
    }

    public synchronized void export(Set<ObjectInformation> objInfoSet, EndPoint endPoint) {
        for (ObjectInformation objInfo : objInfoSet) {
            export(objInfo, endPoint);
        }
    }

    public void unexport(EndPoint endPoint) {
        EndPointInfo endPointInfo;
        synchronized (this) {
            endPointInfo = endPointInfos.get(endPoint);
        }
        if (endPointInfo != null) {
            endPointInfo.unexport();
        }
    }

    public void unexport() {
        EndPointInfo[] infos = null;
        synchronized (this) {
            infos = endPointInfos.values().toArray(new EndPointInfo[0]);
        }
        for (EndPointInfo epi : infos) {
            epi.unexport();
        }
        invocationQueueReader.unexport();
    }

    @Override
    public void endPointDead(EndPoint endPoint) throws Throwable {
        unexport(endPoint);
    }

    private void export(ObjectInformation objInfo, EndPoint endPoint) {
        EndPointInfo endPointInfo = endPointInfos.get(endPoint);
        if (endPointInfo == null) {
            endPointInfo = new EndPointInfo(endPoint);
            endPointInfos.put(endPoint, endPointInfo);
        }
        endPointInfo.export(objInfo);
    }


    protected class EndPointInfo implements Runnable {
        private Map<String, ObjectInformation> exportedObjects;
        private Future<?> future;
        private AtomicBoolean isRunning;
        private long lastPingId;
        private long previousPingId;
        private EndPoint remoteEndPoint;
        private ScheduledFuture scheduledFuture;


        public EndPointInfo(EndPoint remoteEndPoint) {
            this.exportedObjects = new Hashtable<String, ObjectInformation>();
            this.remoteEndPoint = remoteEndPoint;
            this.isRunning = new AtomicBoolean();
        }


        public synchronized boolean isUpdated() {
            if (log.isDebugEnabled()) {
                log.debug("Checking for update (previous ID: " + previousPingId + ", last ID: " + lastPingId + ") on " + remoteEndPoint);
            }
            return previousPingId != lastPingId;
        }

        public EndPoint getRemoteEndPoint() {
            return remoteEndPoint;
        }

        public void export(ObjectInformation objInfo) {
            if (exportedObjects.size() == 0) {
                scheduledFuture = scheduledExecutorService.scheduleAtFixedRate(this, connectionConfiguration.getGcTimeout(), connectionConfiguration.getGcTimeout(), TimeUnit.MILLISECONDS);
            }
            if (exportedObjects.get(objInfo.getId()) == null) {
                exportedObjects.put(objInfo.getId(), objInfo);
                objInfo.export(this);
            }
        }

        public void unexport(ObjectInformation objInfo) {
            ObjectInformation removedObjInfo;
            int size;
            synchronized (this) {
                removedObjInfo = exportedObjects.remove(objInfo.getId());
                size = exportedObjects.size();
            }
            if (removedObjInfo != null) {
                if (size == 0) {
                    unexport();
                }
            }
        }

        public void unexport() {
            ObjectInformation[] objInfos;
            synchronized (this) {
                objInfos = exportedObjects.values().toArray(new ObjectInformation[0]);
                endPointInfos.remove(remoteEndPoint);
                if (future != null) {
                    future.cancel(false);
                }
                scheduledFuture.cancel(false);
                scheduledFuture = null;
            }
            if (objInfos != null) {
                for (ObjectInformation objInfo : objInfos) {
                    objInfo.unexport(remoteEndPoint);
                }
            }
            invocationQueueReader.unexport(remoteEndPoint);
        }

        public synchronized void update() {
            long tmpOldValue = previousPingId;
            previousPingId = lastPingId;
            if (log.isDebugEnabled()) {
                log.debug("Updated previous ping ID to " + previousPingId + " (was: " + tmpOldValue + ") on " + remoteEndPoint);
            }
        }

        public synchronized void ping(boolean[] returnPing, String[] ids) {
            lastPingId = lastPingId + 1;
            if (log.isDebugEnabled()) {
                log.debug("Received ping (last ID: " + lastPingId + ") from " + remoteEndPoint);
            }
            for (int i = 0; i < ids.length; i++) {
                if (exportedObjects.containsKey(ids[i])) {
                    returnPing[i] = true;
                }
            }
        }

        @Override
        public void run() {

            if (!isRunning.get()) {
                future = executorService.submit(new Callable<Void>() {
                            @Override
                            public Void call() {
                                String oldName = Thread.currentThread().getName();
                                try {
                                    isRunning.set(true);
                                    Thread.currentThread().setName("GC.EndPointInfo Runnable Thread - " + this);
                                    if (isUpdated()) {
                                        update();
                                    } else {
                                        if (log.isWarnEnabled()) {
                                            String msg = "GC was not pinged on time by GC Client running on " + remoteEndPoint + ". All objects exported to this remote endpoint will be unexported";
                                            if (log.isDebugEnabled()) {
                                                msg += "\n" + EndPointInfo.this.toString();
                                                log.debug(msg);
                                            } else {
                                                log.warn(msg);
                                            }
                                        }
                                        unexport();
                                    }
                                } finally {
                                    Thread.currentThread().setName(oldName);
                                    isRunning.set(false);
                                }
                                return null;
                            }
                        });
            }
        }

        @Override
        public String toString() {
            return "GC.EndPointInfo[RemoteEndPoint: " + remoteEndPoint + ", # of exportedObjects: " + exportedObjects.size() + "]";
        }
    }

}
