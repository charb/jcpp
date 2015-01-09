package jcpp.rmi.server.transport;

import jcpp.rmi.server.gateway.Route;

public interface ITransportRouter {

    public Route findRoute(String localSite, EndPoint remoteEndPoint);
    
}
