package jcpp.rmi.server.connection.invocation;


import jcpp.rmi.server.transport.EndPoint;

public interface IInvocationQueueListener {

    public void invocationSucceded(EndPoint endPoint, Object object, String methodName, Object args[], Object result);
    
    public void invocationFailed(EndPoint endPoint, String id, long digest, Object args[], Throwable throwable);
    
    public void pollingFailed(EndPoint endPoint, Throwable throwable);
    
}
