package jcpp.rmi.server.gateway;

import java.io.Serializable;

import java.util.HashMap;
import java.util.Map;
import java.util.zip.Deflater;

import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlElement;
import javax.xml.bind.annotation.XmlRootElement;
import javax.xml.bind.annotation.XmlType;


@XmlRootElement(name = "gateway")
@XmlAccessorType(XmlAccessType.FIELD)
@XmlType(name = "RemotingGateway")
public class GatewayConfiguration implements Serializable {
    private static final long serialVersionUID = 7816914239055009789L;

    protected static final int BACKLOG = 4000;
    protected static final int RECEIVE_BUFFER_SIZE = 20480;
    protected static final int SEND_BUFFER_SIZE = 20480;
    protected static final int READ_TIMEOUT = 24 * 3600 * 1000; // 24 hours
    protected static final int ESTABLISH_CONNECTION_INITIAL_TO = 60000;
    protected static final int ESTABLISH_CONNECTION_MIN_TO = 4000;
    protected static final int COMPRESION_THRESHOLD = 1024;
    protected static final int COMPRESION_LEVEL = Deflater.DEFAULT_COMPRESSION;
    protected static final boolean COMPRESSION_ENABLED = false;
    protected static final boolean NIO_ENABLED = false;
    protected static final int NIO_DISPATCHER_POOL_INITIAL_SIZE = 1;
    protected static final int NIO_DISPATCHER_MAX_CHANNELS = 100;
    protected static final int GATEWAY_TUNNEL_RECONNECT_TO = 10000;

    @XmlElement
    private Integer backLog;
    @XmlElement
    private Integer receiveBufferSize;
    @XmlElement
    private Integer sendBufferSize;
    @XmlElement
    private Integer readTimeout;
    @XmlElement
    private Integer establishConnectionInitialTimeout;
    @XmlElement
    private Integer establishConnectionMinTimeout;
    @XmlElement
    private Integer compressionThreshold;
    @XmlElement
    private Integer compressionLevel;
    @XmlElement
    private Boolean compressionEnabled;
    @XmlElement
    private Boolean nioEnabled;
    @XmlElement
    private Integer nioDispatcherPoolSize;
    @XmlElement
    private Integer nioDispatcherChannelsLimit; // max num of channels registered per dispatcher
    @XmlElement
    private Integer gatewayTunnelReconnectTime;

    private transient Map<Address, Integer> failedConnectionAttempts;


    public GatewayConfiguration(int backLog, int receiveBufferSize, int sendBufferSize, int readTimeout, int compressionThreshold, int compressionLevel, boolean compressionEnabled) {
        this.backLog = backLog;
        this.receiveBufferSize = receiveBufferSize;
        this.sendBufferSize = sendBufferSize;
        this.readTimeout = readTimeout;
        this.compressionThreshold = compressionThreshold;
        this.compressionLevel = compressionLevel;
        this.compressionEnabled = compressionEnabled;
    }

    public GatewayConfiguration() {
    }


    public int getBackLog() {
        if (backLog == null) {
            backLog = BACKLOG;
        }
        return backLog;
    }

    public int getReceiveBufferSize() {
        if (receiveBufferSize == null) {
            receiveBufferSize = RECEIVE_BUFFER_SIZE;
        }
        return receiveBufferSize;
    }

    public int getSendBufferSize() {
        if (sendBufferSize == null) {
            sendBufferSize = SEND_BUFFER_SIZE;
        }
        return sendBufferSize;
    }

    public int getReadTimeout() {
        if (readTimeout == null) {
            readTimeout = READ_TIMEOUT;
        }
        return readTimeout;
    }

    public int getEstablishConnectionInitialTimeout() {
        if (establishConnectionInitialTimeout == null) {
            establishConnectionInitialTimeout = ESTABLISH_CONNECTION_INITIAL_TO;
        }
        return establishConnectionInitialTimeout;
    }

    public int getEstablishConnectionMinTimeout() {
        if (establishConnectionMinTimeout == null) {
            establishConnectionMinTimeout = ESTABLISH_CONNECTION_MIN_TO;
        }
        return establishConnectionMinTimeout;
    }

    public int getCompressionThreshold() {
        if (compressionThreshold == null) {
            compressionThreshold = COMPRESION_THRESHOLD;
        }
        return compressionThreshold;
    }

    public int getCompressionLevel() {
        if (compressionLevel == null) {
            compressionLevel = COMPRESION_LEVEL;
        }
        return compressionLevel;
    }

    public boolean isCompressionEnabled() {
        if (compressionEnabled == null) {
            compressionEnabled = COMPRESSION_ENABLED;
        }
        return compressionEnabled;
    }

    public boolean isNioEnabled() {
        if (nioEnabled == null) {
            return NIO_ENABLED;
        }
        return nioEnabled;
    }

    public int getNioDispatcherPoolSize() {
        if (nioDispatcherPoolSize == null) {
            return NIO_DISPATCHER_POOL_INITIAL_SIZE;
        }
        return nioDispatcherPoolSize;
    }

    public int getNioDispatcherChannelsLimit() {
        if (nioDispatcherChannelsLimit == null) {
            return NIO_DISPATCHER_MAX_CHANNELS;
        }
        return nioDispatcherChannelsLimit;
    }

    public int getGatewayTunnelReconnectTime() {
        if (gatewayTunnelReconnectTime == null) {
            return GATEWAY_TUNNEL_RECONNECT_TO;
        }
        return gatewayTunnelReconnectTime;
    }

    public void setNioDispatcherPoolSize(Integer nioDispatcherPoolSize) {
        this.nioDispatcherPoolSize = nioDispatcherPoolSize;
    }

    public void setNioDispatcherChannelsLimit(Integer nioDispatcherChannelsLimit) {
        this.nioDispatcherChannelsLimit = nioDispatcherChannelsLimit;
    }

    public void setNioEnabled(Boolean nioEnabled) {
        this.nioEnabled = nioEnabled;
    }

    public void setBackLog(int backLog) {
        this.backLog = backLog;
    }

    public void setReceiveBufferSize(int receiveBufferSize) {
        this.receiveBufferSize = receiveBufferSize;
    }

    public void setSendBufferSize(int sendBufferSize) {
        this.sendBufferSize = sendBufferSize;
    }

    public void setReadTimeout(int readTimeout) {
        this.readTimeout = readTimeout;
    }

    public void setEstablishConnectionInitialTimeout(int establishConnectionInitialTimeout) {
        this.establishConnectionInitialTimeout = establishConnectionInitialTimeout;
    }

    public void setEstablishConnectionMinTimeout(int establishConnectionMinTimeout) {
        this.establishConnectionMinTimeout = establishConnectionMinTimeout;
    }

    public void setCompressionThreshold(int compressionThreshold) {
        this.compressionThreshold = compressionThreshold;
    }

    public void setCompressionLevel(int compressionLevel) {
        this.compressionLevel = compressionLevel;
    }

    public void setCompressionEnabled(boolean compressionEnabled) {
        this.compressionEnabled = compressionEnabled;
    }

    public void setGatewayTunnelReconnectTime(Integer gatewayTunnelReconnectTime) {
        this.gatewayTunnelReconnectTime = gatewayTunnelReconnectTime;
    }

    public int getEstablishConnectionTimeout(Address address) {
        Integer attempts = getFailedConnectionAttempts().get(address);
        if (attempts == null) {
            return getEstablishConnectionInitialTimeout();
        }
        int timeout = getEstablishConnectionInitialTimeout() / (2 * attempts);
        return (timeout > ESTABLISH_CONNECTION_MIN_TO) ? timeout : ESTABLISH_CONNECTION_MIN_TO;
    }

    public int incrementFailedConnectionAttempts(Address address) {
        Integer attempts = getFailedConnectionAttempts().get(address);
        if (attempts == null) {
            getFailedConnectionAttempts().put(address, 1);
            return 1;
        } else {
            getFailedConnectionAttempts().put(address, ++attempts);
            return attempts;
        }
    }

    public void connectionSucceeded(Address address) {
        getFailedConnectionAttempts().remove(address);
    }

    protected Map<Address, Integer> getFailedConnectionAttempts() {
        if (failedConnectionAttempts == null) {
            this.failedConnectionAttempts = new HashMap<Address, Integer>(); // no sync needed since all access will be sync
        }
        return failedConnectionAttempts;
    }
}
