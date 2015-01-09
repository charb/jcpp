package jcpp.rmi.server.transport;

import java.io.Serializable;

import java.util.concurrent.TimeUnit;

import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlElement;
import javax.xml.bind.annotation.XmlRootElement;
import javax.xml.bind.annotation.XmlType;

import jcpp.rmi.server.gateway.GatewayConfiguration;


@XmlRootElement(name = "transport")
@XmlAccessorType(XmlAccessType.FIELD)
@XmlType(name = "RemotingTransport")
public class TransportConfiguration implements Serializable {
    private static final long serialVersionUID = 721031819973449961L;
    public static final byte MSG_TYPE_PING = (byte) 0x11;
    public static final byte MSG_TYPE_CALL = (byte) 0x21;
    public static final byte MSG_TYPE_OK = (byte) 0x31;
    public static final byte MSG_TYPE_EXCEPTION = (byte) 0x41;
    public static final int MAGIC_NUMBER = 0x4d524d49; // "MRMI"

    protected static final long DEFAULT_CONNECTION_POOL_TIMEOUT = 60000 * 10;
    protected static final int DEFAULT_SOCKET_TIMEOUT = 24 * 3600 * 1000; // 24 hours
    protected static final int DEFAULT_PING_TIMEOUT = 30000;
    protected static final int LIMITED_SOCKET_TIMEOUT = 60000 * 3;
    protected static final long TIMEOUT_TIMER_INTERVAL = 60000 * 5;
    protected static final TimeUnit TIMEOUT_TIMER_TIMEUNIT = TimeUnit.MILLISECONDS;

    protected static final int ENDPOINT_STATISTIC_HISTORY_SIZE = 10;
    protected static final int TRANSPORT_STATISTIC_HISTORY_SIZE = 100;

    @XmlElement
    private GatewayConfiguration gatewayConfiguration;
    @XmlElement
    private Long connectionPoolTimeout;
    @XmlElement
    private Integer socketTimeout;
    @XmlElement
    private Integer pingTimeout;
    @XmlElement
    private Integer limitedSocketTimeout;
    @XmlElement
    private Long timeoutTimerInterval;
    @XmlElement
    private Integer endPointStatisticHistorySize;
    @XmlElement
    private Integer transportStatisticHistorySize;


    public TransportConfiguration(GatewayConfiguration gatewayConfiguration, long connectionTimeout, int socketTimeout, int pingTimeout, long timeoutTimerInterval, TimeUnit timeoutTimerTimeUnit,
        int endPointStatisticHistorySize, int transportStatisticHistorySize) {
        this.gatewayConfiguration = gatewayConfiguration;
        this.connectionPoolTimeout = connectionTimeout;
        this.socketTimeout = socketTimeout;
        this.pingTimeout = pingTimeout;
        this.timeoutTimerInterval = timeoutTimerInterval;
        this.endPointStatisticHistorySize = endPointStatisticHistorySize;
        this.transportStatisticHistorySize = transportStatisticHistorySize;
    }

    public TransportConfiguration() {
    }


    public static int getMagicNumber() {
        return MAGIC_NUMBER;
    }

    public GatewayConfiguration getGatewayConfiguration() {
        if (gatewayConfiguration == null) {
            gatewayConfiguration = new GatewayConfiguration();
        }
        return gatewayConfiguration;
    }

    public void setGatewayConfiguration(GatewayConfiguration gatewayConfiguration) {
        this.gatewayConfiguration = gatewayConfiguration;
    }

    public long getConnectionPoolTimeout() {
        if (connectionPoolTimeout == null) {
            connectionPoolTimeout = DEFAULT_CONNECTION_POOL_TIMEOUT;
        }
        return connectionPoolTimeout;
    }

    public void setConnectionPoolTimeout(long connectionTimeout) {
        this.connectionPoolTimeout = connectionTimeout;
    }

    public int getSocketTimeout() {
        if (socketTimeout == null) {
            socketTimeout = DEFAULT_SOCKET_TIMEOUT;
        }
        return socketTimeout;
    }

    public void setSocketTimeout(int socketTimeout) {
        this.socketTimeout = socketTimeout;
    }

    public int getLimitedSocketTimeout() {
        if (limitedSocketTimeout == null) {
            limitedSocketTimeout = LIMITED_SOCKET_TIMEOUT;
        }
        return limitedSocketTimeout;
    }

    public void setLimitedSocketTimeout(int limitedSocketTimeout) {
        this.limitedSocketTimeout = limitedSocketTimeout;
    }

    public int getPingTimeout() {
        if (pingTimeout == null) {
            pingTimeout = DEFAULT_PING_TIMEOUT;
        }
        return pingTimeout;
    }

    public void setPingTimeout(int pingTimeout) {
        this.pingTimeout = pingTimeout;
    }

    public long getTimeoutTimerInterval() {
        if (timeoutTimerInterval == null) {
            timeoutTimerInterval = TIMEOUT_TIMER_INTERVAL;
        }
        return timeoutTimerInterval;
    }

    public void setTimeoutTimer(long timeoutTimerInterval) {
        this.timeoutTimerInterval = timeoutTimerInterval;
    }

    public int getEndPointStatisticHistorySize() {
        if (endPointStatisticHistorySize == null) {
            endPointStatisticHistorySize = ENDPOINT_STATISTIC_HISTORY_SIZE;
        }
        return endPointStatisticHistorySize;
    }

    public void setEndPointStatisticHistorySize(int endPointStatisticHistorySize) {
        this.endPointStatisticHistorySize = endPointStatisticHistorySize;
    }

    public int getTransportStatisticHistorySize() {
        if (transportStatisticHistorySize == null) {
            transportStatisticHistorySize = TRANSPORT_STATISTIC_HISTORY_SIZE;
        }
        return transportStatisticHistorySize;
    }

    public void setTransportStatisticHistorySize(int transportStatisticHistorySize) {
        this.transportStatisticHistorySize = transportStatisticHistorySize;
    }
}
