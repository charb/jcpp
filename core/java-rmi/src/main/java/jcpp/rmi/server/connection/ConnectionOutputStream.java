package jcpp.rmi.server.connection;

import java.io.IOException;
import java.io.ObjectOutputStream;
import java.io.OutputStream;
import java.io.Serializable;

import java.util.HashSet;
import java.util.Set;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import jcpp.rmi.server.connection.serialization.INotSerializableObjectHandler;
import jcpp.rmi.server.transport.EndPoint;


public class ConnectionOutputStream extends ObjectOutputStream {
    private static Log log = LogFactory.getLog(ConnectionOutputStream.class);
    private EndPoint remoteEndPoint;
    private ObjectInformations objectInformations;
    private Set<ObjectInformation> exportedObjInfos;
    private boolean canInvoke;


    public ConnectionOutputStream(OutputStream out, ObjectInformations objectInformations, EndPoint remoteEndPoint) throws IOException {
        super(out);
        enableReplaceObject(true);
        this.objectInformations = objectInformations;
        this.remoteEndPoint = remoteEndPoint;
        this.exportedObjInfos = new HashSet<ObjectInformation>();
        this.canInvoke = objectInformations.getInvocationRouter().canInvoke(remoteEndPoint, objectInformations.getTransport().getLocalEndPoint());
    }


    public void done() throws IOException {
        objectInformations.getGC().export(exportedObjInfos, remoteEndPoint);
        if (!canInvoke) {
            objectInformations.getInvocationQueueReader().add(exportedObjInfos, remoteEndPoint);
        }
        exportedObjInfos.clear();
    }

    @Override
    protected Object replaceObject(Object obj) throws IOException {
        ObjectInformation objInfo = objectInformations.getObjectInformation(obj);
        if ((objInfo == null) && (obj != null) && !(obj instanceof Serializable)) {
            boolean isExported = false;
            INotExportedObjectListener notExportedObjectListener = objectInformations.getServer().getNotExportedObjectListener();
            if (notExportedObjectListener != null) {
                isExported = notExportedObjectListener.handleNotExportedObject(obj);
                if (isExported) {
                    objInfo = objectInformations.getObjectInformation(obj);
                }
            }
            INotSerializableObjectHandler notSerializableObjectHandler = objectInformations.getServer().getNotSerializableObjectHandler();
            if (!isExported && (notSerializableObjectHandler != null)) {
                if (log.isErrorEnabled()) {
                    log.error("Non-serializable object handled by: " + notSerializableObjectHandler.getClass().getName() + ". Object: " + obj + ". Type: " + obj.getClass());
                }
                return notSerializableObjectHandler.handleNotSerializableObject(obj);
            }
        }
        if (objInfo != null) {
            exportedObjInfos.add(objInfo);
            ObjectHandler objectHandler = (ObjectHandler) objInfo.getObjectHandler().clone();
            objectHandler.getInvoker().setUseInvocationQueue(!canInvoke);
            return objectHandler.getProxy();
        }
        return obj;
    }

}
