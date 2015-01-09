package jcpp.rmi.server.connection;

import java.io.IOException;
import java.io.InputStream;
import java.io.ObjectInputStream;
import java.io.ObjectStreamClass;

import java.lang.reflect.InvocationHandler;
import java.lang.reflect.Modifier;
import java.lang.reflect.Proxy;

import java.util.HashMap;
import java.util.Map;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import jcpp.rmi.server.connection.serialization.NotSerializableException;
import jcpp.rmi.server.transport.EndPoint;


public class ConnectionInputStream extends ObjectInputStream {
    private static Log log = LogFactory.getLog(ConnectionInputStream.class);
    private ObjectInformations objectInformations;
    private Map<ObjectPointer, Object> gcObjectPointers;
    private EndPoint remoteEndPoint;


    public ConnectionInputStream(InputStream in, ObjectInformations objectInformations, EndPoint remoteEndPoint) throws IOException {
        super(in);
        enableResolveObject(true);
        this.objectInformations = objectInformations;
        this.gcObjectPointers = new HashMap<ObjectPointer, Object>();
        this.remoteEndPoint = remoteEndPoint;
    }


    public void done() throws Exception {
        objectInformations.getGCClient().add(gcObjectPointers);
        gcObjectPointers.clear();
    }

    @Override
    protected Object resolveObject(Object obj) throws IOException {
        if (Proxy.isProxyClass(obj.getClass())) {
            InvocationHandler invocationHandler = Proxy.getInvocationHandler(obj);
            if (invocationHandler instanceof ObjectHandler) {
                ObjectHandler objectHandler = (ObjectHandler) invocationHandler;
                objectHandler.setObjectInformations(objectInformations);
                ObjectPointer objectPointer = objectHandler.getInvoker().getObjectPointer();
                if (objectPointer.getEndPoint().equals(objectInformations.getTransport().getLocalEndPoint())) {
                    return objectInformations.getObjectInformation(objectPointer.getId()).getObject();
                }
                if (objectHandler.getInvoker().usesInvocationQueue()) {
                    objectHandler.getInvoker().setInvocationQueue(objectInformations.getInvocationQueue());
                    objectHandler.getInvoker().setUseInvocationQueue(false);
                } else {
                    gcObjectPointers.put(objectPointer, obj);
                }
                return obj;
            }
        } else if (obj instanceof NotSerializableException) {
            throw (NotSerializableException) obj;
        }
        return obj;
    }

    @Override
    protected Class<?> resolveClass(ObjectStreamClass desc) throws IOException, ClassNotFoundException {
        ClassLoader latestLoader = getEndPointClassLoader();
        if (latestLoader == null) {
            return super.resolveClass(desc);
        }
        String name = desc.getName();
        try {
            return Class.forName(name, false, latestLoader);
        } catch (ClassNotFoundException ex) {
            return super.resolveClass(desc);
        }
    }

    @Override
    protected Class<?> resolveProxyClass(String[] interfaces) throws IOException, ClassNotFoundException {
        ClassLoader latestLoader = getEndPointClassLoader();
        if (latestLoader == null) {
            return super.resolveProxyClass(interfaces);
        }
        ClassLoader nonPublicLoader = null;
        boolean hasNonPublicInterface = false;

        // define proxy in class loader of non-public interface(s), if any
        Class<?>[] classObjs = new Class[interfaces.length];
        for (int i = 0; i < interfaces.length; i++) {
            Class<?> cl = Class.forName(interfaces[i], false, latestLoader);
            if ((cl.getModifiers() & Modifier.PUBLIC) == 0) {
                if (hasNonPublicInterface) {
                    if (nonPublicLoader != cl.getClassLoader()) {
                        throw new IllegalAccessError("conflicting non-public interface class loaders");
                    }
                } else {
                    nonPublicLoader = cl.getClassLoader();
                    hasNonPublicInterface = true;
                }
            }
            classObjs[i] = cl;
        }
        try {
            return Proxy.getProxyClass(hasNonPublicInterface ? nonPublicLoader : latestLoader, classObjs);
        } catch (IllegalArgumentException e) {
            throw new ClassNotFoundException(null, e);
        }
    }

    @Override
    protected ObjectStreamClass readClassDescriptor() throws IOException, ClassNotFoundException {
        // This method has been overriden to ignore SerialVersionUIDs when they do not match.
        // This is especially helpful when interacting with the C++ version of MRMI.
        //
        ObjectStreamClass resultClassDescriptor = super.readClassDescriptor(); // initially streams descriptor
        Class<?> localClass; // the class in the local JVM that this descriptor represents.
        try {
            localClass = Class.forName(resultClassDescriptor.getName());
        } catch (ClassNotFoundException e) {
            log.debug("No local class for " + resultClassDescriptor.getName(), e);
            return resultClassDescriptor;
        }
        ObjectStreamClass localClassDescriptor = ObjectStreamClass.lookup(localClass);
        if (localClassDescriptor != null) { // only if class implements serializable
            final long localSUID = localClassDescriptor.getSerialVersionUID();
            final long streamSUID = resultClassDescriptor.getSerialVersionUID();
            if (streamSUID != localSUID) { // check for serialVersionUID mismatch.
                resultClassDescriptor = localClassDescriptor; // Use local class descriptor for deserialization
            }
        }
        return resultClassDescriptor;
    }

    private ClassLoader getEndPointClassLoader() {
        IClassLoaderProvider classLoaderProvider = objectInformations.getServer().getClassLoaderProvider();
        if (classLoaderProvider != null) {
            ClassLoader classLoader = classLoaderProvider.getClassLoader(remoteEndPoint);
            return classLoader;
        }
        return null;
    }

}
