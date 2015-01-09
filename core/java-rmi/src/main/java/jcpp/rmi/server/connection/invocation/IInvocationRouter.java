package jcpp.rmi.server.connection.invocation;

import jcpp.rmi.server.transport.EndPoint;

public interface IInvocationRouter {

    public boolean canInvoke(EndPoint fromEndPoint, EndPoint toEndPoint);
    
}
