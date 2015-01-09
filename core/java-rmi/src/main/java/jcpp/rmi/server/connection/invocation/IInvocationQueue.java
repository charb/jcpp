package jcpp.rmi.server.connection.invocation;

import java.util.List;

import jcpp.rmi.server.transport.EndPoint;

public interface IInvocationQueue {

    public List<InvocationItem> pop(EndPoint endPoint, long timeout) throws Exception;

    public void stopPop(EndPoint endPoint) throws Exception;

}
