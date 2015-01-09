package jcpp.rmi.server.connection;

import java.io.IOException;

import java.lang.management.ManagementFactory;
import java.lang.reflect.InvocationHandler;
import java.lang.reflect.Method;
import java.lang.reflect.Proxy;

import java.util.*;
import java.util.Collection;
import java.util.Collections;
import java.util.Hashtable;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.Map;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.SynchronousQueue;
import java.util.concurrent.ThreadPoolExecutor;
import java.util.concurrent.TimeUnit;

import javax.management.MalformedObjectNameException;
import javax.management.ObjectName;

import edu.emory.mathcs.backport.java.util.concurrent.ScheduledExecutorService;

import jcpp.rmi.server.connection.invocation.IInvocationQueue;
import jcpp.rmi.server.connection.invocation.IInvocationQueueListener;
import jcpp.rmi.server.connection.invocation.IInvocationRouter;
import jcpp.rmi.server.connection.invocation.InvocationQueue;
import jcpp.rmi.server.connection.invocation.InvocationQueueReader;
import jcpp.rmi.server.connection.invocation.InvocationRouter;
import jcpp.rmi.server.connection.serialization.INotSerializableObjectHandler;
import jcpp.rmi.server.connection.statistic.ConnectionStatistic;
import jcpp.rmi.server.transport.EndPoint;
import jcpp.rmi.server.transport.ITransportRouter;
import jcpp.rmi.server.transport.Transport;
import jcpp.rmi.server.transport.TransportRouter;
import jcpp.rmi.server.util.MRMIConfigurator;
import jcpp.rmi.server.util.NamedThreadFactory;
import jcpp.rmi.server.util.PriorityThreadFactory;


public class Server implements IServer {
    private static final String NANO_TIMER_PROVIDER_PROP = "edu.emory.mathcs.backport.java.util.concurrent.NanoTimerProvider";
    private static Map<Integer, Server> servers = Collections.synchronizedMap(new LinkedHashMap<Integer, Server>());
    private static int globalId;

    private EndPoint endPoint;
    private int id;
    private IRegistry registry;
    private Transport transport;
    private ObjectInformations objectInformations;
    private LifecycleImpl lifecycleImpl;
    private List<ILifecycle> lifecycles;
    private InvocationQueueListenerImpl invocationQueueListenerImpl;
    private List<IInvocationQueueListener> invocationQueueListeners;
    private GCClientListenerImpl gcClientListenerImpl;
    private List<IGCClientListener> gcClientListeners;
    private InvocationListenerImpl invocationListenerImpl;
    private List<IInvocationListener> invocationListeners;
    private INotExportedObjectListener notExportedObjectListener;
    private INotSerializableObjectHandler notSerializableObjectHandler;
    private GC gc;
    private GCClient gcClient;
    private ScheduledExecutorService scheduledExecutorService;
    private ExecutorService executorService;
    private InvocationQueue invocationQueue;
    private InvocationQueueReader invocationQueueReader;
    private IInvocationRouter invocationRouter;
    private ConnectionTransportDispatcher connectionTransportDispatcher;
    private ConnectionConfiguration connectionConfiguration;
    private ConnectionStatistic connectionStatistic;
    private IClassLoaderProvider classLoaderProvider;
    private IInvocationExceptionHandler invocationExceptionHandler;
    private ObjectName mBeanName;


    protected Server(EndPoint endPoint, ITransportRouter transportRouter, IInvocationRouter invocationRouter, ConnectionConfiguration connectionConfiguration) throws Exception {
        this.endPoint = endPoint;
        synchronized (Server.class) {
            this.id = globalId++;
        }
        this.connectionConfiguration = connectionConfiguration;
        this.lifecycles = new ArrayList<ILifecycle>();
        this.lifecycleImpl = new LifecycleImpl();
        this.invocationQueueListeners = new ArrayList<IInvocationQueueListener>();
        this.invocationQueueListenerImpl = new InvocationQueueListenerImpl();
        this.gcClientListeners = new ArrayList<IGCClientListener>();
        this.gcClientListenerImpl = new GCClientListenerImpl();
        this.invocationQueueReader = new InvocationQueueReader(this, invocationQueueListenerImpl);
        this.invocationListeners = new ArrayList<IInvocationListener>();
        this.invocationListenerImpl = new InvocationListenerImpl();

        // Executor created with 30 seconds keep alive time, to reduce number of threads:
        this.executorService = new ThreadPoolExecutor(0, Integer.MAX_VALUE, 30L, TimeUnit.SECONDS, new SynchronousQueue<Runnable>(), new NamedThreadFactory("MRMI Cached Thread "));

        // Using the backport-util-concurrent package with a NanoTimerProvider that performs System.currentTimeMillis(),
        // due to a bug on some SunOS machines affecting System.nanoTime(), and SunPerfProvider.nanoTime()
        System.setProperty(NANO_TIMER_PROVIDER_PROP, "edu.emory.mathcs.backport.java.util.concurrent.helpers.Utils$MillisProvider");
        this.scheduledExecutorService = edu.emory.mathcs.backport.java.util.concurrent.Executors.newScheduledThreadPool(connectionConfiguration.getExecutorCorePoolSize(), new PriorityThreadFactory());

        this.invocationQueue = new InvocationQueue();
        this.gc = new GC(executorService, scheduledExecutorService, invocationQueueReader, connectionConfiguration);
        this.gcClient = new GCClient(this, gcClientListenerImpl);
        this.invocationRouter = invocationRouter;
        this.objectInformations = new ObjectInformations(lifecycleImpl, this, gc, gcClient, invocationQueue, invocationQueueReader, invocationRouter, invocationListenerImpl);
        this.connectionTransportDispatcher = new ConnectionTransportDispatcher(objectInformations);
        this.transport = new Transport(endPoint, transportRouter, connectionTransportDispatcher, executorService, scheduledExecutorService, connectionConfiguration.getTransportConfiguration());
        this.connectionStatistic = new ConnectionStatistic(transport.getTransportStatistic(), connectionConfiguration);
        this.objectInformations.setTransport(transport);
        this.objectInformations.setConnectionStatistic(connectionStatistic);
        this.registry = new Registry(objectInformations);
        this.registry.bind(IRegistry.class.getName(), registry, Arrays.asList(IRegistry.class));
        this.registry.bind(IServer.class.getName(), this, Arrays.asList( IServer.class ));
        this.registry.bind(IGC.class.getName(), gc, Arrays.asList( IGC.class));
        this.registry.bind(IGCClient.class.getName(), gcClient, Arrays.asList( IGCClient.class ));
        this.registry.bind(IInvocationQueue.class.getName(), invocationQueue, Arrays.asList(IInvocationQueue.class ));
        servers.put(id, this);
        mBeanName = getObjectName();
        ManagementFactory.getPlatformMBeanServer().registerMBean(new MRMIConfigurator(connectionConfiguration), mBeanName);
    }


    public static Server create(EndPoint endPoint) throws Exception {
        return create(endPoint, new ConnectionConfiguration());
    }

    public static Server create(EndPoint endPoint, ConnectionConfiguration connectionConfiguration) throws Exception {
        return create(endPoint, new TransportRouter(), new InvocationRouter(), connectionConfiguration);
    }

    public static Server create(EndPoint endPoint, ITransportRouter transportRouter, IInvocationRouter invocationRouter, ConnectionConfiguration connectionConfiguration) throws Exception {
        ConnectionConfiguration.getGcClientInitialDelayRange(); // init static value
        return new Server(endPoint, transportRouter, invocationRouter, connectionConfiguration);
    }

    public static IServer getRemoteServer(Object object) throws Exception {
        if (Proxy.isProxyClass(object.getClass())) {
            ObjectHandler objectHandler = getObjectHandlerFromProxy(object);
            ObjectPointer objectPointer = objectHandler.getInvoker().getObjectPointer();
            return objectHandler.getInvoker().getObjectInformations().getServer().lookup(objectPointer.getEndPoint(), IServer.class);
        }
        return getServerFromExportedObject(object);
    }

    public static IServer getLocalServer(Object object) throws Exception {
        ObjectHandler objectHandler = getObjectHandlerFromProxy(object);
        return objectHandler.getInvoker().getObjectInformations().getServer();
    }

    public static Server[] getServers() {
        return servers.values().toArray(new Server[0]);
    }

    public static Server getServer(int id) {
        return servers.get(id);
    }

    public static String getHost(Object object) throws Exception {
        return getEndPoint(object).getHost();
    }

    public static int getPort(Object object) throws Exception {
        return getEndPoint(object).getPort();
    }

    public static String getSite(Object object) throws Exception {
        return getEndPoint(object).getSite();
    }

    public static EndPoint getEndPoint(Object object) throws Exception {
        if (Proxy.isProxyClass(object.getClass())) {
            ObjectPointer objectPointer = getObjectHandlerFromProxy(object).getInvoker().getObjectPointer();
            return objectPointer.getEndPoint();
        }
        return getServerFromExportedObject(object).getEndPoint();
    }

    public static String getId(Object object) throws Exception {
        ObjectPointer objectPointer = null;
        if (Proxy.isProxyClass(object.getClass())) {
            objectPointer = getObjectHandlerFromProxy(object).getInvoker().getObjectPointer();
        } else {
            Server server = getServerFromExportedObject(object);
            ObjectHandler objectHandler = server.getObjectInformations().getObjectInformation(object).getObjectHandler();
            objectPointer = objectHandler.getInvoker().getObjectPointer();
        }
        return objectPointer.getId();
    }

    @Override
    public <T> T lookup(EndPoint endPoint, Class<T> clazz) {
        return clazz.cast(lookup(clazz.getName(), endPoint, clazz.getClassLoader(), Arrays.asList(clazz)));
    }

    public Object lookup(String id, EndPoint endPoint, ClassLoader classLoader, List interfaces) {
        ObjectHandler objectHandler = new ObjectHandler(objectInformations, classLoader, interfaces, new ObjectPointer(endPoint, id));
        return objectHandler.getProxy();
    }

    @Override
    public IRegistry getRegistry() {
        return registry;
    }

    public EndPoint getEndPoint() {
        return endPoint;
    }

    @Override
    public IGC getGC() {
        return gc;
    }

    @Override
    public IGCClient getGCClient() {
        return gcClient;
    }

    public IInvocationRouter getInvocationRouter() {
        return invocationRouter;
    }

    public ExecutorService getExecutorService() {
        return executorService;
    }

    public ScheduledExecutorService getScheduledExecutorService() {
        return scheduledExecutorService;
    }

    public ObjectInformations getObjectInformations() {
        return objectInformations;
    }

    public ConnectionTransportDispatcher getConnectionTransportDispatcher() {
        return connectionTransportDispatcher;
    }

    public ConnectionConfiguration getConnectionConfiguration() {
        return connectionConfiguration;
    }

    @Override
    public ConnectionStatistic getConnectionStatistic() {
        return connectionStatistic;
    }

    public INotExportedObjectListener getNotExportedObjectListener() {
        return notExportedObjectListener;
    }

    public void setNotExportedObjectListener(INotExportedObjectListener notExportedObjectListener) {
        this.notExportedObjectListener = notExportedObjectListener;
    }

    public INotSerializableObjectHandler getNotSerializableObjectHandler() {
        return notSerializableObjectHandler;
    }

    public void setNotSerializableObjectHandler(INotSerializableObjectHandler notSerializableObjectHandler) {
        this.notSerializableObjectHandler = notSerializableObjectHandler;
    }

    public void setClassLoaderProvider(IClassLoaderProvider classLoaderProvider) {
        this.classLoaderProvider = classLoaderProvider;
    }

    public IClassLoaderProvider getClassLoaderProvider() {
        return classLoaderProvider;
    }

    public IInvocationExceptionHandler getInvocationExceptionHandler() {
        return invocationExceptionHandler;
    }

    public void setInvocationExceptionHandler(IInvocationExceptionHandler invocationExceptionHandler) {
        this.invocationExceptionHandler = invocationExceptionHandler;
    }

    public void unexport() throws IOException {
        servers.remove(this.id);
        gcClient.unexport();
        gc.unexport();
        objectInformations.unexport();
        scheduledExecutorService.shutdownNow();
        executorService.shutdownNow();
        try {
            ManagementFactory.getPlatformMBeanServer().unregisterMBean(mBeanName);
        } catch (Exception e) {
        }
    }

    @Override
    public void startRecordingStats(int methodStatisticHistorySize) throws Exception {
        this.connectionConfiguration.setRecordStats(true);
        this.connectionConfiguration.setMethodStatisticHistorySize(methodStatisticHistorySize);
    }

    @Override
    public void stopRecordingStats() throws Exception {
        this.connectionConfiguration.setRecordStats(false);
    }

    @Override
    public String toString() {
        return "Server[" + endPoint + ", " + transport + "]";
    }

    public void addLifecycle(ILifecycle lifecycle) {
        lifecycles.add(lifecycle);
    }

    public void removeLifecycle(ILifecycle lifecycle) {
        lifecycles.remove(lifecycle);
    }

    public void addInvocationQueueListener(IInvocationQueueListener invocationQueueListener) {
        invocationQueueListeners.add(invocationQueueListener);
    }

    public void removeInvocationQueueListener(IInvocationQueueListener invocationQueueListener) {
        invocationQueueListeners.remove(invocationQueueListener);
    }

    public void addGCClientListener(IGCClientListener gcClientListener) {
        gcClientListeners.add(gcClientListener);
    }

    public void removeGCClientListener(IGCClientListener gcClientListener) {
        gcClientListeners.remove(gcClientListener);
    }

    public void addIInvocationListener(IInvocationListener invocationListener) {
        invocationListeners.add(invocationListener);
    }

    public void removeIInvocationListener(IInvocationListener invocationListener) {
        invocationListeners.remove(invocationListener);
    }

    private static ObjectHandler getObjectHandlerFromProxy(Object object) throws Exception {
        if (Proxy.isProxyClass(object.getClass())) {
            InvocationHandler invocationHandler = Proxy.getInvocationHandler(object);
            if (invocationHandler instanceof ObjectHandler) {
                ObjectHandler objectHandler = (ObjectHandler) invocationHandler;
                return objectHandler;
            }
            throw new Exception("The Proxy object: " + object + " is not an instance of ObjectHandler.");
        }
        throw new Exception("The object: " + object + " is not of type Proxy.");
    }

    private static Server getServerFromExportedObject(Object object) throws Exception {
        Collection<Server> servers = null;
        synchronized (Server.servers) {
            servers = Server.servers.values();
        }
        if (servers != null) {
            for (Server server : servers) {
                if (server.getObjectInformations().getObjectInformation(object) != null) {
                    return server;
                }
            }
        }
        throw new Exception("Unable to find a remote server for the object: " + object + ". The object is not of type Proxy, and has not been exported locally.");
    }

    private ObjectName getObjectName() throws MalformedObjectNameException, NullPointerException {
        Hashtable<String, String> properties = new Hashtable<String, String>();
        properties.put("type", "MRMIConfigurator");
        properties.put("server_id", "Server[" + endPoint.getHost() + ";" + endPoint.getPort() + ";" + id + "]");
        return new ObjectName("jcpp.rmi.server.util", properties);
    }


    private class LifecycleImpl implements ILifecycle {

        @Override
        public void export(ObjectInformation objectInformation, EndPoint endPoint) {
            for (ILifecycle lifecycle : lifecycles) {
                lifecycle.export(objectInformation, endPoint);
            }
        }

        @Override
        public void unexport(ObjectInformation objectInformation) {
            for (ILifecycle lifecycle : lifecycles) {
                lifecycle.unexport(objectInformation);
            }
        }

        @Override
        public void export(ObjectInformation objectInformation) {
            for (ILifecycle lifecycle : lifecycles) {
                lifecycle.export(objectInformation);
            }
        }

        @Override
        public void unexport(ObjectInformation objectInformation, EndPoint endPoint) {
            for (ILifecycle lifecycle : lifecycles) {
                lifecycle.unexport(objectInformation, endPoint);
            }
        }
    }

    private class InvocationQueueListenerImpl implements IInvocationQueueListener {

        @Override
        public void invocationFailed(EndPoint endPoint, String id, long digest, Object[] args, Throwable throwable) {
            for (IInvocationQueueListener invocationQueueListener : invocationQueueListeners) {
                invocationQueueListener.invocationFailed(endPoint, id, digest, args, throwable);
            }
        }

        @Override
        public void invocationSucceded(EndPoint endPoint, Object object, String methodName, Object[] args, Object result) {
            for (IInvocationQueueListener invocationQueueListener : invocationQueueListeners) {
                invocationQueueListener.invocationSucceded(endPoint, object, methodName, args, result);
            }
        }

        @Override
        public void pollingFailed(EndPoint endPoint, Throwable throwable) {
            for (IInvocationQueueListener invocationQueueListener : invocationQueueListeners) {
                invocationQueueListener.pollingFailed(endPoint, throwable);
            }
        }

    }

    private class GCClientListenerImpl implements IGCClientListener {

        @Override
        public void objectAlive(EndPoint endPoint, Object[] objects) {
            for (IGCClientListener gcClientListener : gcClientListeners) {
                gcClientListener.objectAlive(endPoint, objects);
            }
        }

        @Override
        public void objectDead(EndPoint endPoint, Object[] objects) {
            for (IGCClientListener gcClientListener : gcClientListeners) {
                gcClientListener.objectDead(endPoint, objects);
            }
        }

        @Override
        public void objectDead(EndPoint endPoint, Object[] objects, Throwable throwable) {
            for (IGCClientListener gcClientListener : gcClientListeners) {
                gcClientListener.objectDead(endPoint, objects, throwable);
            }
        }

        @Override
        public void objectMaybeDead(EndPoint endPoint, Object[] objects, Throwable throwable) {
            for (IGCClientListener gcClientListener : gcClientListeners) {
                gcClientListener.objectMaybeDead(endPoint, objects, throwable);
            }
        }

    }

    private class InvocationListenerImpl implements IInvocationListener {

        @Override
        public void invocationFailed(Object proxy, Method method, Object[] args, Throwable e) {
            for (IInvocationListener invocationListener : invocationListeners) {
                invocationListener.invocationFailed(proxy, method, args, e);
            }
        }

        @Override
        public void invocationSucceeded(Object proxy, Method method, Object[] args) {
            for (IInvocationListener invocationListener : invocationListeners) {
                invocationListener.invocationSucceeded(proxy, method, args);
            }
        }

    }
}
