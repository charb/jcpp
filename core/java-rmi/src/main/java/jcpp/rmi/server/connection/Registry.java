package jcpp.rmi.server.connection;

import java.util.*;

public class Registry implements IRegistry {
    private ObjectInformations objectInformations;

    public Registry(ObjectInformations objectInformations) {
        this.objectInformations = objectInformations;
    }

    public void bind(String id, Object object, List interfaces) throws Exception {
        if(object == null) {
            throw new ConnectionException("Bind Error: Attempting to bind a null object");
        }
        if(id == null || "".equals(id)) {
            throw new ConnectionException("Bind Error: Attempting to bind an object with an invalid id.");
        }
        if(interfaces == null || interfaces.size()==0) {
            throw new ConnectionException("Bind Error: Attempting to bind and object without any specified interfaces.");
        }
        ObjectInformation objInfo = objectInformations.getObjectInformation(id);
        if(objInfo == null) {
            objectInformations.export(id, object, interfaces);
        } else {
            throw new ConnectionException("Bind Error: Object already bound: " + objInfo + " at: " + objectInformations.getTransport().getLocalEndPoint());
        }
    }

    public String[] list() throws Exception{
        return objectInformations.list();
    }

    public Object lookup(String id) throws Exception {
        ObjectInformation objInfo = objectInformations.getObjectInformation(id);
        if(objInfo == null) {
            throw new ConnectionException("Object of ID: " + id + " is not bound in registry at: " + objectInformations.getTransport().getLocalEndPoint());
        }
        return objInfo.getObject();
    }

    public void rebind(String id, Object object, List interfaces) throws Exception {
        if(object == null) {
            throw new ConnectionException("Bind Error: Attempting to bind a null object");
        }
        if(id == null || "".equals(id)) {
            throw new ConnectionException("Bind Error: Attempting to bind an object with an invalid id.");
        }
        if(interfaces == null || interfaces.size()==0) {
            throw new ConnectionException("Bind Error: Attempting to bind and object without any specified interfaces.");
        }
        objectInformations.export(id, object, interfaces);
    }

    public void unbind(String id) throws Exception {
        if(objectInformations.unexport(id) == null) {
            throw new ConnectionException("Object of ID: " + id + " is not bound in registry at: " + objectInformations.getTransport().getLocalEndPoint());
        }
    }
}
