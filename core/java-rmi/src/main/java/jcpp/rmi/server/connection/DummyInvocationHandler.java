package jcpp.rmi.server.connection;

import java.io.Serializable;
import java.lang.reflect.InvocationHandler;
import java.lang.reflect.Method;
import java.lang.reflect.Proxy;

public class DummyInvocationHandler implements InvocationHandler, Serializable {
    private static final long serialVersionUID = 1985197689179244062L;
    private Class<?>[] interfaces;
    private ObjectPointer objectPointer;

    public DummyInvocationHandler(Class<?>[] interfaces, ObjectPointer objectPointer) {
        this.interfaces = interfaces;
        this.objectPointer = objectPointer;
    }

    @Override
    public Object invoke(Object proxy, Method method, Object[] args) throws Throwable {
        if(method.getDeclaringClass().equals(Object.class)) {
            if(method.getName().equals("toString")) {
                String strInterfaces = "";
                for(int i = 0; i < interfaces.length - 1; i++) {
                    strInterfaces += interfaces[i].getName() + ", ";
                }
                strInterfaces += interfaces[interfaces.length - 1];
                return "Proxy[" + objectPointer + ", Interfaces[" + strInterfaces + "]]";
            }
            if(method.getName().equals("hashCode")) {
                return objectPointer.hashCode();
            }
            if(method.getName().equals("equals")) {
                if(Proxy.isProxyClass(args[0].getClass())) {
                    InvocationHandler invocationHandler = Proxy.getInvocationHandler(args[0]);
                    if(invocationHandler instanceof DummyInvocationHandler) {
                        DummyInvocationHandler dummyHandler = (DummyInvocationHandler) invocationHandler;
                        return objectPointer.equals(dummyHandler.getObjectPointer());
                    }
                }
                return false;
            }
        }
        throw new Exception("Not implemented. The DummyInvocationHandler can only handle methods inherited from Object class.");
    }

    public ObjectPointer getObjectPointer() {
        return objectPointer;
    }

}
