package jcpp.rmi.server.gateway;

import java.io.FilterInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.util.concurrent.atomic.AtomicLong;

import jcpp.rmi.server.compression.CompressionInputStream;
import jcpp.rmi.server.statistic.IStatisticStream;

public class GatewayCompressionInputStream extends FilterInputStream implements IStatisticStream {
    private GatewayInputStream gatewayInputStream;
    private CompressionInputStream compressionInputStream;

    public GatewayCompressionInputStream(InputStream in, boolean bEnableCompression, GatewayConfiguration gatewayConfiguration) throws IOException, ClassNotFoundException {
        super(in);
        gatewayInputStream = new GatewayInputStream(in);
        if(bEnableCompression) {
            compressionInputStream = new CompressionInputStream(in, gatewayConfiguration.getReceiveBufferSize());
        }
    }

    public int read() throws IOException {
        if(compressionInputStream != null) {
            return compressionInputStream.read();
        }
        return in.read();
    }

    public int read(byte b[], int off, int len) throws IOException {
        if(compressionInputStream != null) {
            return compressionInputStream.read(b, off, len);
        }
        return in.read(b, off, len);
    }

    public int available() throws IOException {
        if(compressionInputStream != null) {
            return compressionInputStream.available();
        }
        return in.available();
    }

    public Route getRoute() {
        return gatewayInputStream.getRoute();
    }

    public AtomicLong getNetworkDataCounter() {
        if(compressionInputStream != null) {
            return compressionInputStream.getNetworkDataCounter();
        }
        return null;
    }

    public boolean usesCompressionStream() {
        if(compressionInputStream != null) {
            return true;
        }
        return false;
    }

    public void setNetworkDataCounter(AtomicLong networkByteCounter) {
        if(compressionInputStream != null) {
            compressionInputStream.setNetworkDataCounter(networkByteCounter);
        }
    }
}
