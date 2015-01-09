package jcpp.rmi.server.connection;

import jcpp.rmi.server.transport.EndPoint;

public interface IClassLoaderProvider {
    
    public ClassLoader getClassLoader(EndPoint remoteEndPoint); 

}
