package jcpp.rmi.server.connection;

import jcpp.rmi.server.transport.EndPoint;


public interface IGCClient {

    EndPoint[] getEndPoints() throws Exception;

}
