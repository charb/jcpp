package jcpp.rmi.server.connection;

import java.io.EOFException;
import java.io.Serializable;

import java.lang.reflect.Method;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import jcpp.rmi.server.connection.invocation.InvocationItem;
import jcpp.rmi.server.connection.invocation.InvocationQueue;
import jcpp.rmi.server.connection.statistic.InvocationStatistic;
import jcpp.rmi.server.connection.statistic.ObjectStatistic.MethodType;
import jcpp.rmi.server.transport.Connection;
import jcpp.rmi.server.transport.Connections;
import jcpp.rmi.server.transport.TransportConfiguration;


public class Invoker implements Serializable {
    private static final long serialVersionUID = -5888955964943945437L;
    private static transient Log log = LogFactory.getLog(Invoker.class);
    private transient ObjectInformations objectInformations;
    private ObjectPointer objectPointer;
    private boolean useInvocationQueue;
    private transient InvocationQueue invocationQueue;


    public Invoker(ObjectInformations objectInformations, ObjectPointer objectPointer) {
        this.objectInformations = objectInformations;
        this.objectPointer = objectPointer;
    }


    public ObjectPointer getObjectPointer() {
        return objectPointer;
    }

    public void setObjectInformations(ObjectInformations objectInformations) {
        this.objectInformations = objectInformations;
    }

    public ObjectInformations getObjectInformations() {
        return objectInformations;
    }

    public void setUseInvocationQueue(boolean useInvocationQueue) {
        this.useInvocationQueue = useInvocationQueue;
    }

    public boolean usesInvocationQueue() {
        return useInvocationQueue;
    }

    public void setInvocationQueue(InvocationQueue invocationQueue) {
        this.invocationQueue = invocationQueue;
    }

    public Object invoke(Method method, Object[] args) throws Throwable {
        long digest = objectInformations.getMethodDigester().getDigestFromMethod(method);
        if (invocationQueue != null) {
            invocationQueue.push(objectPointer.getEndPoint(), new InvocationItem(digest, args, objectPointer.getId()));
            return null;
        }
        Connections connections = objectInformations.getTransport().getConnections(objectPointer.getEndPoint());
        Connection connection = null;
        connection = connections.createConnection();
        try {
            if (!connection.openConnection()) {
                try {
                    connection.kill();
                } catch (Exception e) {
                    if (log.isDebugEnabled()) {
                        log.debug("Error killing connection to " + objectPointer.getEndPoint(), e);
                    }
                }
                throw new ConnectionException("Unable to open a connection to " + objectPointer.getEndPoint());
            }
            connection.startCall();

            ConnectionOutputStream oos = new ConnectionOutputStream(connection.getOutputStream(), objectInformations, connection.getConnections().getRemoteEndPoint());
            InvocationStatistic invocationStatistic = null;
            if (objectInformations.getServer().getConnectionConfiguration().isRecordStats()) {
                Object[] statArgs = (Object[]) objectInformations.getInvocationStatisticObject(args);
                invocationStatistic = objectInformations.getConnectionStatistic().getObjectStatistic(objectPointer.getId(), objectPointer.getEndPoint()).getMethodStatistic(method.toString(), MethodType.CLIENT_METHOD)
                    .createInvocationStatistic(objectInformations.getTransport().getLocalEndPoint(), statArgs);
            }
            try {
                oos.writeUTF(objectPointer.getId());
                oos.writeLong(digest);
                oos.writeObject(args);
                connection.finishCall();
            } catch (Throwable e) {
                if (invocationStatistic != null) {
                    invocationStatistic.callFailed(e);
                }
                throw e;
            } finally {
                oos.done();
            }

            ConnectionInputStream ois = new ConnectionInputStream(connection.getInputStream(), objectInformations, objectPointer.getEndPoint());
            try {
                byte exceptionCheck = ois.readByte();
                if (exceptionCheck == TransportConfiguration.MSG_TYPE_OK) {
                    Object obj = ois.readObject();
                    if (invocationStatistic != null) {
                        Object statObj = objectInformations.getInvocationStatisticObject(obj);
                        invocationStatistic.callSucceeded(statObj);
                    }
                    connection.readOk();
                    return obj;
                } else if (exceptionCheck == TransportConfiguration.MSG_TYPE_EXCEPTION) {
                    if (log.isDebugEnabled()) {
                        log.debug("Receiving exception from dispatcher while invoking method: " + method + " on object: " + objectPointer + " ...");
                    }
                    Throwable throwable = (Throwable) ois.readObject();
                    connection.readOk();
                    List<StackTraceElement> serverStackTrace = Arrays.asList(throwable.getStackTrace());
                    List<StackTraceElement> clientStackTrace = Arrays.asList(Thread.currentThread().getStackTrace());
                    List<StackTraceElement> tmp1 = new ArrayList<StackTraceElement>(clientStackTrace);
                    tmp1.remove(0);
                    List<StackTraceElement> tmp = new ArrayList<StackTraceElement>(serverStackTrace);
                    tmp.addAll(tmp1);
                    throwable.setStackTrace(tmp.toArray(new StackTraceElement[0]));
                    if (log.isDebugEnabled()) {
                        log.debug("Received the follwoing exception from dispatcher while invoking method: " + method + " on object: " + objectPointer + " ...", throwable);
                    }
                    throw throwable;
                } else {
                    if (log.isDebugEnabled()) {
                        log.debug("Invalid exception checking byte received while invoking method: " + method + " on object: " + objectPointer);
                    }
                    throw new EOFException("Invalid exception checking byte received while invoking method: " + method + " on object: " + objectPointer);
                }
            } catch (Throwable e) {
                if (invocationStatistic != null) {
                    invocationStatistic.callFailed(e);
                }
                throw e;
            } finally {
                ois.done();
            }
        } finally {
            connection.free();
        }
    }

}
