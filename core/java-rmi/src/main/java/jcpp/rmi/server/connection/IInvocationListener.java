package jcpp.rmi.server.connection;

import java.lang.reflect.Method;

public interface IInvocationListener {
    
    public void invocationSucceeded(Object proxy, Method method, Object[] args);
    
    public void invocationFailed(Object proxy, Method method, Object[] args, Throwable e);

}
