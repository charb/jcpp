package jcpp.rmi.server.transport;

public interface ITransportDispatcher {

    public void dispatch(EndPoint fromEndPoint, EndPoint toEndPoint, Connection connection) throws Throwable;
    
}
