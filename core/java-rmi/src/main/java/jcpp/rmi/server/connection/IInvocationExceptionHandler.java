package jcpp.rmi.server.connection;

import java.lang.reflect.Method;


public interface IInvocationExceptionHandler {

    Throwable handleException(Object object, Method method, Object[] args, Throwable exception);

}
