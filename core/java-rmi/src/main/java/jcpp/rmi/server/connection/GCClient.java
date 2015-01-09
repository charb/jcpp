package jcpp.rmi.server.connection;

import java.util.Hashtable;
import java.util.Map;
import java.util.Map.Entry;
import java.util.Random;
import java.util.concurrent.Callable;
import java.util.concurrent.Future;
import java.util.concurrent.atomic.AtomicBoolean;

import edu.emory.mathcs.backport.java.util.concurrent.ScheduledFuture;
import edu.emory.mathcs.backport.java.util.concurrent.TimeUnit;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import jcpp.rmi.server.transport.Connections;
import jcpp.rmi.server.transport.EndPoint;


public class GCClient implements IGCClient {
    private static Log log = LogFactory.getLog(GCClient.class);

    private Map<EndPoint, EndPointInfo> endPointInfos;
    private IGCClientListener gcClientListener;
    private Server localServer;
    private Random random;


    public GCClient(Server localServer, IGCClientListener gcClientListener) {
        this.localServer = localServer;
        this.endPointInfos = new Hashtable<EndPoint, EndPointInfo>();
        this.gcClientListener = gcClientListener;
        this.random = new Random();
    }


    @Override
    public synchronized EndPoint[] getEndPoints() {
        return endPointInfos.keySet().toArray(new EndPoint[0]);
    }

    public synchronized void add(Map<ObjectPointer, Object> objectPointers) throws Exception {
        for (Entry<ObjectPointer, Object> entry : objectPointers.entrySet()) {
            EndPoint remoteEndPoint = entry.getKey().getEndPoint();
            EndPointInfo endPointInfo = endPointInfos.get(remoteEndPoint);
            if (endPointInfo == null) {
                endPointInfo = new EndPointInfo(remoteEndPoint);
                endPointInfos.put(remoteEndPoint, endPointInfo);
            }
            endPointInfo.export(entry.getKey().getId(), entry.getValue());
        }
    }

    public void unexport() {
        EndPointInfo[] epis = null;
        synchronized (this) {
            epis = endPointInfos.values().toArray(new EndPointInfo[0]);
        }
        for (EndPointInfo epi : epis) {
            epi.unexport();
        }
    }


    private class EndPointInfo implements Runnable {
        private Future<?> future;
        private IGC gc;
        private int gcExceptionCount;
        private AtomicBoolean isRunning;
        private Map<String, Object> objects;
        private EndPoint remoteEndPoint;
        private ScheduledFuture scheduledFuture;
        private Throwable throwable;
        private Connections connections;


        public EndPointInfo(EndPoint remoteEndPoint) throws Exception {
            this.remoteEndPoint = remoteEndPoint;
            this.objects = new Hashtable<String, Object>();
            this.gc = localServer.lookup(remoteEndPoint, IGC.class);
            this.isRunning = new AtomicBoolean();
            this.connections = localServer.getObjectInformations().getTransport().getConnections(remoteEndPoint);
        }


        public void export(String id, Object object) {
            if (objects.size() == 0) {

                // range = random value between (-initialRange/2) and (+initialRange/2)
                double range = (double) ConnectionConfiguration.getGcClientInitialDelayRange();
                range = (random.nextDouble() * range) - (range / 2.0);

                scheduledFuture = localServer.getScheduledExecutorService().scheduleAtFixedRate(this, localServer.getConnectionConfiguration().getGcClientTimeout() + (long) range,
                        localServer.getConnectionConfiguration().getGcClientTimeout(), TimeUnit.MILLISECONDS);
            }
            objects.put(id, object);
        }

        public void unexport(String id) {
            objects.remove(id);
            if (objects.size() == 0) {
                unexport();
            }
        }

        public boolean ping() {
            throwable = null;
            String[] idsArray = objects.keySet().toArray(new String[0]);
            boolean[] ping = null;
            long t1 = 0;
            try {
                t1 = System.currentTimeMillis();
                if (log.isDebugEnabled()) {
                    log.debug("Invoking ping - " + EndPointInfo.this.toString());
                }
                connections.setInvocationTimeLimit();
                ping = gc.ping(localServer.getEndPoint(), idsArray);
            } catch (Throwable e) {
                throwable = e;
                if (log.isDebugEnabled()) {
                    log.debug("Error while pinging the GC at " + remoteEndPoint, e);
                }
                if (++gcExceptionCount >= localServer.getConnectionConfiguration().getGcClientExceptionThreshold()) {
                    if (log.isDebugEnabled()) {
                        log.debug("Pinging the GC at " + remoteEndPoint + " failed after " + gcExceptionCount + " attempts. The remote endpoint will no longer be pinged. The last received exception follows", e);
                    }
                    if (log.isDebugEnabled()) {
                        log.debug(EndPointInfo.this.toString());
                    }
                    unexport();
                    return false;
                }
                return true;
            } finally {
                connections.removeInvocationTimeLimit();
                if (log.isDebugEnabled()) {
                    long rtt = System.currentTimeMillis() - t1;
                    log.debug("Ping RTT: " + rtt + "ms - " + EndPointInfo.this.toString());
                }
            }
            gcExceptionCount = 0;
            for (int i = 0; i < ping.length; i++) {
                if (!ping[i]) {
                    if (log.isDebugEnabled()) {
                        log.debug("Negative ping returned from " + remoteEndPoint + ", unexporting object of ID: " + idsArray[i]);
                    }
                    unexport(idsArray[i]);
                }
            }
            if (objects.size() == 0) {
                return false;
            }
            return true;
        }

        public void unexport() {
            synchronized (this) {
                endPointInfos.remove(remoteEndPoint);
                if (future != null) {
                    future.cancel(false);
                }
                scheduledFuture.cancel(false);
                scheduledFuture = null;
            }
            localServer.getObjectInformations().getInvocationQueue().unexport(remoteEndPoint);
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
                                    Thread.currentThread().setName("GCClient.EndPointInfo Runnable Thread - " + EndPointInfo.this.toString());
                                    boolean ping = ping();
                                    Object[] values = null;
                                    synchronized (EndPointInfo.this) {
                                        values = objects.values().toArray(new Object[0]);
                                    }
                                    if (!ping) {
                                        if (gcExceptionCount == 0) {
                                            gcClientListener.objectDead(remoteEndPoint, values);
                                        } else {
                                            gcClientListener.objectDead(remoteEndPoint, values, throwable);
                                        }
                                    } else {
                                        if (gcExceptionCount == 0) {
                                            gcClientListener.objectAlive(remoteEndPoint, values);
                                        } else {
                                            gcClientListener.objectMaybeDead(remoteEndPoint, values, throwable);
                                        }
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
            return "GCClient.EndPointInfo[RemoteEndPoint: " + remoteEndPoint + ", Num Exported Objects: " + objects.size() + "]";
        }

    }
}
