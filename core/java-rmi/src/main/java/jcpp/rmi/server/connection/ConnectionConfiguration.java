package jcpp.rmi.server.connection;

import java.io.Serializable;

import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlElement;
import javax.xml.bind.annotation.XmlRootElement;
import javax.xml.bind.annotation.XmlType;

import jcpp.rmi.server.transport.TransportConfiguration;


@XmlRootElement(name = "connection")
@XmlAccessorType(XmlAccessType.FIELD)
@XmlType(name = "RemotingConnection")
public class ConnectionConfiguration implements Serializable {
    private static final long serialVersionUID = -7733929591819747912L;
    protected static final long GC_TIMEOUT = 20 * 60000;
    protected static final long GCCLIENT_TIMEOUT = 2 * 60000;
    protected static final long QUEUE_READER_TIMEOUT = 10000;
    protected static final long QUEUE_POP_TIMEOUT = 60000;
    protected static final int GCCLIENT_EXCEPTION_THRESHOLD = 10;
    protected static final int EXECUTOR_CORE_POOL_SIZE = 2; //TODO might need to have it > 1 for performance

    protected static final int CONNECTION_STATISTIC_HISTORY_SIZE = 10;
    protected static final int METHOD_STATISTIC_HISTORY_SIZE = 10;
    protected static final boolean RECORD_STATS = false;

    private static Long gcInitialDelayRange;

    @XmlElement
    private TransportConfiguration transportConfiguration;
    @XmlElement
    private Long gcTimeout;
    @XmlElement
    private Long gcClientTimeout;
    @XmlElement
    private Long queueReaderTimeout;
    @XmlElement
    private Long queuePopTimeout;
    @XmlElement
    private Integer gcClientExceptionThreshold;
    @XmlElement
    private Integer executorCorePoolSize;
    @XmlElement
    private Integer connectionStatisticHistorySize;
    @XmlElement
    private Integer methodStatisticHistorySize;
    @XmlElement
    private Boolean recordStats;


    /**
     * All timeout values are in milliseconds.
     */
    public ConnectionConfiguration(TransportConfiguration transportConfiguration, long gcTimeout, long gcClientTimeout, long queueReaderTimeout, long queuePopTimeout, int gcClientExceptionThreshold, int executorCorePoolSize,
        int connectionStatisticHistorySize, int methodStatisticHistorySize, boolean recordStats) {
        this.transportConfiguration = transportConfiguration;
        this.gcTimeout = gcTimeout;
        this.gcClientTimeout = gcClientTimeout;
        this.queueReaderTimeout = queueReaderTimeout;
        this.queuePopTimeout = queuePopTimeout;
        this.gcClientExceptionThreshold = gcClientExceptionThreshold;
        this.executorCorePoolSize = executorCorePoolSize;
        this.connectionStatisticHistorySize = connectionStatisticHistorySize;
        this.methodStatisticHistorySize = methodStatisticHistorySize;
        this.recordStats = recordStats;
    }

    public ConnectionConfiguration() {
    }


    public static final long getGcClientInitialDelayRange() {
        if (gcInitialDelayRange == null) {
            gcInitialDelayRange = GCCLIENT_TIMEOUT;
            String property = System.getProperty("mrmi.gcClientInitialDelayRange");
            if (property != null) {
                try {
                    gcInitialDelayRange = Long.parseLong(property.trim());
                } catch (NumberFormatException e) {
                }
            }
        }
        return gcInitialDelayRange;
    }

    public TransportConfiguration getTransportConfiguration() {
        if (transportConfiguration == null) {
            transportConfiguration = new TransportConfiguration();
        }
        return transportConfiguration;
    }

    public void setTransportConfiguration(TransportConfiguration transportConfiguration) {
        this.transportConfiguration = transportConfiguration;
    }

    public long getGcTimeout() {
        if (gcTimeout == null) {
            gcTimeout = GC_TIMEOUT;
        }
        return gcTimeout;
    }

    /**
     * Timeout value in milliseconds.
     */
    public void setGcTimeout(long gcTimeout) {
        this.gcTimeout = gcTimeout;
    }

    public long getGcClientTimeout() {
        if (gcClientTimeout == null) {
            gcClientTimeout = GCCLIENT_TIMEOUT;
        }
        return gcClientTimeout;
    }

    /**
     * Timeout value in milliseconds.
     */
    public void setGcClientTimeout(long gcClientTimeout) {
        this.gcClientTimeout = gcClientTimeout;
    }

    public long getQueueReaderTimeout() {
        if (queueReaderTimeout == null) {
            queueReaderTimeout = QUEUE_READER_TIMEOUT;
        }
        return queueReaderTimeout;
    }

    /**
     * Timeout value in milliseconds.
     */
    public void setQueueReaderTimeout(long queueReaderTimeout) {
        this.queueReaderTimeout = queueReaderTimeout;
    }

    public long getQueuePopTimeout() {
        if (queuePopTimeout == null) {
            queuePopTimeout = QUEUE_POP_TIMEOUT;
        }
        return queuePopTimeout;
    }

    /**
     * Timeout value in milliseconds.
     */
    public void setQueuePopTimeout(long queuePopTimeout) {
        this.queuePopTimeout = queuePopTimeout;
    }

    public int getGcClientExceptionThreshold() {
        if (gcClientExceptionThreshold == null) {
            gcClientExceptionThreshold = GCCLIENT_EXCEPTION_THRESHOLD;
        }
        return gcClientExceptionThreshold;
    }

    public void setGcClientExceptionThreshold(int gcClientExceptionThreshold) {
        this.gcClientExceptionThreshold = gcClientExceptionThreshold;
    }

    public int getExecutorCorePoolSize() {
        if (executorCorePoolSize == null) {
            executorCorePoolSize = EXECUTOR_CORE_POOL_SIZE;
        }
        return executorCorePoolSize;
    }

    public void setExecutorCorePoolSize(int executorCorePoolSize) {
        this.executorCorePoolSize = executorCorePoolSize;
    }

    public int getConnectionStatisticHistorySize() {
        if (connectionStatisticHistorySize == null) {
            connectionStatisticHistorySize = CONNECTION_STATISTIC_HISTORY_SIZE;
        }
        return connectionStatisticHistorySize;
    }

    public void setConnectionStatisticHistorySize(int connectionStatisticHistorySize) {
        this.connectionStatisticHistorySize = connectionStatisticHistorySize;
    }

    public int getMethodStatisticHistorySize() {
        if (methodStatisticHistorySize == null) {
            methodStatisticHistorySize = METHOD_STATISTIC_HISTORY_SIZE;
        }
        return methodStatisticHistorySize;
    }

    public void setMethodStatisticHistorySize(int methodStatisticHistorySize) {
        this.methodStatisticHistorySize = methodStatisticHistorySize;
    }

    public boolean isRecordStats() {
        if (recordStats == null) {
            recordStats = RECORD_STATS;
        }
        return recordStats;
    }

    public void setRecordStats(boolean recordStats) {
        this.recordStats = recordStats;
    }
}
