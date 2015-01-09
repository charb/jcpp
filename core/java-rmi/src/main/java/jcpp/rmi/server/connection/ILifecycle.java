package jcpp.rmi.server.connection;

import jcpp.rmi.server.transport.EndPoint;

public interface ILifecycle {

    public void export(ObjectInformation objectInformation);
    
    public void export(ObjectInformation objectInformation, EndPoint endPoint);

    public void unexport(ObjectInformation objectInformation,EndPoint endPoint);

    public void unexport(ObjectInformation objectInformation);

}
