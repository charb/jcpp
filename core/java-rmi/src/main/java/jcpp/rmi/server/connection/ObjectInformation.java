package jcpp.rmi.server.connection;

import java.io.IOException;

import java.util.HashMap;
import java.util.*;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import jcpp.rmi.server.transport.EndPoint;


public class ObjectInformation {
    private static Log log = LogFactory.getLog(ObjectInformation.class);

    private String id;
    private Object object;
    private ILifecycle lifecycle;
    private ObjectHandler objectHandler;
    private Map<EndPoint, GC.EndPointInfo> exportedEndPoints;
    private ObjectInformations objectInformations;


    public ObjectInformation(String id, Object object, List interfaces, ObjectInformations objectInformations, ILifecycle lifecycle, GC gc) {
        this.object = object;
        this.id = id;
        this.objectInformations = objectInformations;
        this.objectHandler = new ObjectHandler(objectInformations, object.getClass().getClassLoader(), interfaces, new ObjectPointer(objectInformations.getTransport().getLocalEndPoint(), id));
        this.lifecycle = lifecycle;
        this.exportedEndPoints = new HashMap<EndPoint, GC.EndPointInfo>();
    }


    public Object getObject() {
        return object;
    }

    public String getId() {
        return id;
    }

    public ILifecycle getLifecycle() {
        return lifecycle;
    }

    public ObjectHandler getObjectHandler() {
        return objectHandler;
    }

    public void exported() {
        if (log.isDebugEnabled()) {
            log.debug("Exported " + this);
        }
        lifecycle.export(this);
    }

    public void export(GC.EndPointInfo remoteEndPointInfo) {
        synchronized (this) {
            exportedEndPoints.put(remoteEndPointInfo.getRemoteEndPoint(), remoteEndPointInfo);
        }
        if (log.isDebugEnabled()) {
            log.debug("Exported " + this + " to " + remoteEndPointInfo);
        }
        lifecycle.export(this, remoteEndPointInfo.getRemoteEndPoint());
    }

    public void unexport(EndPoint endPoint) {
        synchronized (this) {
            exportedEndPoints.remove(endPoint);
        }
        if (log.isDebugEnabled()) {
            log.debug("Unexported " + this + " from " + endPoint);
        }
        lifecycle.unexport(this, endPoint);
    }

    public void unexport() throws IOException {
        objectInformations.remove(id);
        GC.EndPointInfo[] endPointInfos;
        synchronized (this) {
            endPointInfos = exportedEndPoints.values().toArray(new GC.EndPointInfo[0]);
            exportedEndPoints.clear();
        }
        for (GC.EndPointInfo endPointInfo : endPointInfos) {
            endPointInfo.unexport(this);
            lifecycle.unexport(this, endPointInfo.getRemoteEndPoint());
        }
        if (log.isDebugEnabled()) {
            log.debug("Unexported " + this);
        }
        lifecycle.unexport(this);
    }

    @Override
    public String toString() {
        return "ObjectInformation[Id[" + id + "], Object[" + object + "]]";
    }
}
