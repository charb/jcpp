package jcpp.rmi.server.connection;

import jcpp.rmi.server.connection.statistic.ConnectionStatistic;
import jcpp.rmi.server.transport.EndPoint;


public interface IServer {

    <T> T lookup(EndPoint endPoint, Class<T> clazz) throws Exception;

    IRegistry getRegistry() throws Exception;

    ConnectionStatistic getConnectionStatistic() throws Exception;

    IGC getGC() throws Exception;

    IGCClient getGCClient() throws Exception;

    void startRecordingStats(int methodStatisticHistorySize) throws Exception;

    void stopRecordingStats() throws Exception;

}
