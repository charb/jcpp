package jcpp.rmi.server.connection;

import java.io.Serializable;
import java.util.*;
import java.lang.reflect.InvocationHandler;
import java.lang.reflect.Method;
import java.lang.reflect.Proxy;


public class ObjectHandler implements InvocationHandler, Serializable, Cloneable {
    private static final long serialVersionUID = 3179670252394270616L;
    private Invoker invoker;
    private Object proxy;
    private transient ClassLoader classLoader;
    private List<Class> interfaces;
    private transient IInvocationListener invocationListener;


    public ObjectHandler(ObjectInformations objectInformations, ClassLoader classLoader, List<Class> interfaces, ObjectPointer objectPointer) {
        this.invoker = new Invoker(objectInformations, objectPointer);
        this.proxy = Proxy.newProxyInstance(classLoader, interfaces.toArray(new Class[0]), this);
        this.interfaces = interfaces;
        this.classLoader = classLoader;
        this.invocationListener = objectInformations.getInvocationListener();
    }


    public Object getProxy() {
        return proxy;
    }

    public Invoker getInvoker() {
        return invoker;
    }

    public ClassLoader getClassLoader() {
        return classLoader;
    }

    public List<Class> getInterfaces() {
        return interfaces;
    }

    @Override
    public Object invoke(Object proxy, Method method, Object[] args) throws Throwable {
        if (method.getDeclaringClass().equals(Object.class)) {
            if (method.getName().equals("toString")) {
                String strInterfaces = "";
                for (int i = 0; i < (interfaces.size() - 1); i++) {
                    strInterfaces += interfaces.get(i).getName() + ", ";
                }
                strInterfaces += interfaces.get(interfaces.size() - 1);
                return "Proxy[" + invoker.getObjectPointer() + ", Interfaces[" + strInterfaces + "]]";
            }
            if (method.getName().equals("hashCode")) {
                return invoker.getObjectPointer().hashCode();
            }
            if (method.getName().equals("equals")) {
                if (Proxy.isProxyClass(args[0].getClass())) {
                    InvocationHandler invocationHandler = Proxy.getInvocationHandler(args[0]);
                    if (invocationHandler instanceof ObjectHandler) {
                        ObjectHandler objectHandler = (ObjectHandler) invocationHandler;
                        ObjectPointer objectPointer = objectHandler.getInvoker().getObjectPointer();
                        return invoker.getObjectPointer().equals(objectPointer);
                    }
                }
                return false;
            }
        }
        Object invocationResult = null;
        try {
            invocationResult = invoker.invoke(method, args);
            invocationListener.invocationSucceeded(proxy, method, args);
        } catch (Throwable e) {
            invocationListener.invocationFailed(proxy, method, args, e);
            throw e;
        }
        return invocationResult;
    }

    public void setObjectInformations(ObjectInformations objectInformations) {
        invoker.setObjectInformations(objectInformations);
        invocationListener = objectInformations.getInvocationListener();
    }

    @Override
    public Object clone() {
        ObjectHandler objectHandler = new ObjectHandler(invoker.getObjectInformations(), classLoader, interfaces, invoker.getObjectPointer());
        return objectHandler;
    }
}
