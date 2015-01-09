package jcpp.rmi.server.util;

public interface MRMIConfiguratorMBean {

    int getBackLog();

    int getReceiveBufferSize();

    int getSendBufferSize();

    int getReadTimeout();

    int getEstablishConnectionInitialTimeout();

    int getEstablishConnectionMinTimeout();

    int getCompressionThreshold();

    int getCompressionLevel();

    boolean isCompressionEnabled();

    void setBackLog(int backLog);

    void setReceiveBufferSize(int receiveBufferSize);

    void setSendBufferSize(int sendBufferSize);

    void setReadTimeout(int readTimeout);

    void setEstablishConnectionInitialTimeout(int establishConnectionInitialTimeout);

    void setEstablishConnectionMinTimeout(int establishConnectionMinTimeout);

    void setCompressionThreshold(int compressionThreshold);

    void setCompressionLevel(int compressionLevel);

    void setCompressionEnabled(boolean compressionEnabled);

    long getConnectionPoolTimeout();

    void setConnectionPoolTimeout(long connectionTimeout);

    int getSocketTimeout();

    void setSocketTimeout(int socketTimeout);

    int getPingTimeout();

    void setPingTimeout(int pingTimeout);

    long getTimeoutTimerInterval();

    void setTimeoutTimer(long timeoutTimerInterval);

    int getEndPointStatisticHistorySize();

    void setEndPointStatisticHistorySize(int endPointStatisticHistorySize);

    int getTransportStatisticHistorySize();

    void setTransportStatisticHistorySize(int transportStatisticHistorySize);

    long getGcTimeout();

    void setGcTimeout(long gcTimeout);

    long getGcClientTimeout();

    void setGcClientTimeout(long gcClientTimeout);

    long getQueueReaderTimeout();

    void setQueueReaderTimeout(long queueReaderTimeout);

    long getQueuePopTimeout();

    void setQueuePopTimeout(long queuePopTimeout);

    int getGcClientExceptionThreshold();

    void setGcClientExceptionThreshold(int gcClientExceptionThreshold);

    int getExecutorCorePoolSize();

    void setExecutorCorePoolSize(int executorCorePoolSize);

    int getConnectionStatisticHistorySize();

    void setConnectionStatisticHistorySize(int connectionStatisticHistorySize);

    int getMethodStatisticHistorySize();

    void setMethodStatisticHistorySize(int methodStatisticHistorySize);

    boolean isRecordStats();

    void setRecordStats(boolean recordStats);

    boolean isNioEnabled();

    void setNioEnabled(boolean nioEnabled);

    int getNioDispatcherPoolSize();

    void setNioDispatcherPoolSize(int nioDispatcherPoolSize);

    int getNioDispatcherChannelsLimit();

    void setNioDispatcherChannelsLimit(int nioDispatcherChannelsLimit);

    int getGatewayTunnelReconnectTime();

    void setGatewayTunnelReconnectTime(int gatewayTunnelReconnectTime);
}
