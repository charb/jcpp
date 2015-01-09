package jcpp.rmi.server.connection.statistic;

import java.io.IOException;
import java.io.ObjectOutputStream;
import java.io.OutputStream;
import java.io.Serializable;

import java.lang.reflect.Proxy;

import jcpp.rmi.server.connection.DummyInvocationHandler;
import jcpp.rmi.server.connection.ObjectHandler;
import jcpp.rmi.server.connection.ObjectInformation;
import jcpp.rmi.server.connection.ObjectInformations;
import jcpp.rmi.server.connection.ObjectPointer;


public class InvocationStatisticOutputStream extends ObjectOutputStream {
    private ObjectInformations objectInformations;


    public InvocationStatisticOutputStream(OutputStream out, ObjectInformations objectInformations) throws IOException {
        super(out);
        enableReplaceObject(true);
        this.objectInformations = objectInformations;
    }


    @Override
    protected Object replaceObject(Object obj) throws IOException {
        if (obj instanceof Serializable) {
            return obj;
        }
        ObjectInformation objInfo = (ObjectInformation) objectInformations.getObjectInformation(obj);
        if (objInfo != null) {
            ObjectHandler objectHandler = (ObjectHandler) objInfo.getObjectHandler();
            ObjectPointer objectPointer = objectHandler.getInvoker().getObjectPointer();
            DummyInvocationHandler dummyInvocationHandler = new DummyInvocationHandler(new Class[] { obj.getClass() }, objectPointer);
            return Proxy.newProxyInstance(obj.getClass().getClassLoader(), objectHandler.getInterfaces().toArray(new Class[0]), dummyInvocationHandler);
        }
        return null;
    }
}
