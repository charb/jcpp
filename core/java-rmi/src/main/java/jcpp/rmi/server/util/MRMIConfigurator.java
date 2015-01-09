package jcpp.rmi.server.util;

import jcpp.rmi.server.connection.ConnectionConfiguration;
import jcpp.rmi.server.gateway.GatewayConfiguration;
import jcpp.rmi.server.transport.TransportConfiguration;


public class MRMIConfigurator implements MRMIConfiguratorMBean {
    private ConnectionConfiguration connectionConfiguration;

    public MRMIConfigurator(ConnectionConfiguration connectionConfiguration) {
        this.connectionConfiguration = connectionConfiguration;
    }


    public ConnectionConfiguration getConnectionConfiguration() {
        return connectionConfiguration;
    }

    public void setConnectionConfiguration(ConnectionConfiguration connectionConfiguration) {
        this.connectionConfiguration = connectionConfiguration;
    }

    public TransportConfiguration getTransportConfiguration() {
        return connectionConfiguration.getTransportConfiguration();
    }

    public GatewayConfiguration getGatewayConfiguration() {
        return getTransportConfiguration().getGatewayConfiguration();
    }

    @Override
    public int getBackLog() {
        return getGatewayConfiguration().getBackLog();
    }

    @Override
    public int getReceiveBufferSize() {
        return getGatewayConfiguration().getReceiveBufferSize();
    }

    @Override
    public int getSendBufferSize() {
        return getGatewayConfiguration().getSendBufferSize();
    }

    @Override
    public int getReadTimeout() {
        return getGatewayConfiguration().getReadTimeout();
    }

    @Override
    public int getEstablishConnectionInitialTimeout() {
        return getGatewayConfiguration().getEstablishConnectionInitialTimeout();
    }

    @Override
    public int getEstablishConnectionMinTimeout() {
        return getGatewayConfiguration().getEstablishConnectionMinTimeout();
    }

    @Override
    public int getCompressionThreshold() {
        return getGatewayConfiguration().getCompressionThreshold();
    }

    @Override
    public int getCompressionLevel() {
        return getGatewayConfiguration().getCompressionLevel();
    }

    @Override
    public boolean isCompressionEnabled() {
        return getGatewayConfiguration().isCompressionEnabled();
    }

    @Override
    public void setBackLog(int backLog) {
        getGatewayConfiguration().setBackLog(backLog);
    }

    @Override
    public void setReceiveBufferSize(int receiveBufferSize) {
        getGatewayConfiguration().setReceiveBufferSize(receiveBufferSize);
    }

    @Override
    public void setSendBufferSize(int sendBufferSize) {
        getGatewayConfiguration().setSendBufferSize(sendBufferSize);
    }

    @Override
    public void setReadTimeout(int readTimeout) {
        getGatewayConfiguration().setReadTimeout(readTimeout);
    }

    @Override
    public void setEstablishConnectionInitialTimeout(int establishConnectionInitialTimeout) {
        getGatewayConfiguration().setEstablishConnectionInitialTimeout(establishConnectionInitialTimeout);
    }

    @Override
    public void setEstablishConnectionMinTimeout(int establishConnectionMinTimeout) {
        getGatewayConfiguration().setEstablishConnectionMinTimeout(establishConnectionMinTimeout);
    }

    @Override
    public void setCompressionThreshold(int compressionThreshold) {
        getGatewayConfiguration().setCompressionThreshold(compressionThreshold);
    }

    @Override
    public void setCompressionLevel(int compressionLevel) {
        getGatewayConfiguration().setCompressionLevel(compressionLevel);
    }

    @Override
    public void setCompressionEnabled(boolean compressionEnabled) {
        getGatewayConfiguration().setCompressionEnabled(compressionEnabled);
    }

    @Override
    public long getConnectionPoolTimeout() {
        return getTransportConfiguration().getConnectionPoolTimeout();
    }

    @Override
    public void setConnectionPoolTimeout(long connectionTimeout) {
        getTransportConfiguration().setConnectionPoolTimeout(connectionTimeout);
    }

    @Override
    public int getSocketTimeout() {
        return getTransportConfiguration().getSocketTimeout();
    }

    @Override
    public void setSocketTimeout(int socketTimeout) {
        getTransportConfiguration().setSocketTimeout(socketTimeout);
    }

    @Override
    public int getPingTimeout() {
        return getTransportConfiguration().getPingTimeout();
    }

    @Override
    public void setPingTimeout(int pingTimeout) {
        getTransportConfiguration().setPingTimeout(pingTimeout);
    }

    @Override
    public long getTimeoutTimerInterval() {
        return getTransportConfiguration().getTimeoutTimerInterval();
    }

    @Override
    public void setTimeoutTimer(long timeoutTimerInterval) {
        getTransportConfiguration().setTimeoutTimer(timeoutTimerInterval);
    }

    @Override
    public int getEndPointStatisticHistorySize() {
        return getTransportConfiguration().getEndPointStatisticHistorySize();
    }

    @Override
    public void setEndPointStatisticHistorySize(int endPointStatisticHistorySize) {
        getTransportConfiguration().setEndPointStatisticHistorySize(endPointStatisticHistorySize);
    }

    @Override
    public int getTransportStatisticHistorySize() {
        return getTransportConfiguration().getTransportStatisticHistorySize();
    }

    @Override
    public void setTransportStatisticHistorySize(int transportStatisticHistorySize) {
        getTransportConfiguration().setTransportStatisticHistorySize(transportStatisticHistorySize);
    }

    @Override
    public long getGcTimeout() {
        return getConnectionConfiguration().getGcTimeout();
    }

    @Override
    public void setGcTimeout(long gcTimeout) {
        getConnectionConfiguration().setGcTimeout(gcTimeout);
    }

    @Override
    public long getGcClientTimeout() {
        return getConnectionConfiguration().getGcClientTimeout();
    }

    @Override
    public void setGcClientTimeout(long gcClientTimeout) {
        getConnectionConfiguration().setGcClientTimeout(gcClientTimeout);
    }

    @Override
    public long getQueueReaderTimeout() {
        return getConnectionConfiguration().getQueueReaderTimeout();
    }

    @Override
    public void setQueueReaderTimeout(long queueReaderTimeout) {
        getConnectionConfiguration().setQueueReaderTimeout(queueReaderTimeout);
    }

    @Override
    public long getQueuePopTimeout() {
        return getConnectionConfiguration().getQueuePopTimeout();
    }

    @Override
    public void setQueuePopTimeout(long queuePopTimeout) {
        getConnectionConfiguration().setQueuePopTimeout(queuePopTimeout);
    }

    @Override
    public int getGcClientExceptionThreshold() {
        return getConnectionConfiguration().getGcClientExceptionThreshold();
    }

    @Override
    public void setGcClientExceptionThreshold(int gcClientExceptionThreshold) {
        getConnectionConfiguration().setGcClientExceptionThreshold(gcClientExceptionThreshold);
    }

    @Override
    public int getExecutorCorePoolSize() {
        return getConnectionConfiguration().getExecutorCorePoolSize();
    }

    @Override
    public void setExecutorCorePoolSize(int executorCorePoolSize) {
        getConnectionConfiguration().setExecutorCorePoolSize(executorCorePoolSize);
    }

    @Override
    public int getConnectionStatisticHistorySize() {
        return getConnectionConfiguration().getConnectionStatisticHistorySize();
    }

    @Override
    public void setConnectionStatisticHistorySize(int connectionStatisticHistorySize) {
        getConnectionConfiguration().setConnectionStatisticHistorySize(connectionStatisticHistorySize);
    }

    @Override
    public int getMethodStatisticHistorySize() {
        return getConnectionConfiguration().getMethodStatisticHistorySize();
    }

    @Override
    public void setMethodStatisticHistorySize(int methodStatisticHistorySize) {
        getConnectionConfiguration().setMethodStatisticHistorySize(methodStatisticHistorySize);
    }

    @Override
    public boolean isRecordStats() {
        return getConnectionConfiguration().isRecordStats();
    }

    @Override
    public void setRecordStats(boolean recordStats) {
        getConnectionConfiguration().setRecordStats(recordStats);
    }

    @Override
    public boolean isNioEnabled() {
        return getGatewayConfiguration().isNioEnabled();
    }

    @Override
    public void setNioEnabled(boolean nioEnabled) {
        getGatewayConfiguration().setNioEnabled(nioEnabled);
    }

    @Override
    public int getNioDispatcherPoolSize() {
        return getGatewayConfiguration().getNioDispatcherPoolSize();
    }

    @Override
    public void setNioDispatcherPoolSize(int nioDispatcherPoolSize) {
        getGatewayConfiguration().setNioDispatcherPoolSize(nioDispatcherPoolSize);
    }

    @Override
    public int getNioDispatcherChannelsLimit() {
        return getGatewayConfiguration().getNioDispatcherChannelsLimit();
    }

    @Override
    public void setNioDispatcherChannelsLimit(int nioDispatcherChannelsLimit) {
        getGatewayConfiguration().setNioDispatcherChannelsLimit(nioDispatcherChannelsLimit);
    }

    @Override
    public int getGatewayTunnelReconnectTime() {
        return getGatewayConfiguration().getGatewayTunnelReconnectTime();
    }

    @Override
    public void setGatewayTunnelReconnectTime(int gatewayTunnelReconnectTime) {
        getGatewayConfiguration().setGatewayTunnelReconnectTime(gatewayTunnelReconnectTime);
    }

}
