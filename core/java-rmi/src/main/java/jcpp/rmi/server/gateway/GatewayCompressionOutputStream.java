package jcpp.rmi.server.gateway;

import java.io.FilterOutputStream;
import java.io.IOException;
import java.io.OutputStream;
import java.util.concurrent.atomic.AtomicLong;

import jcpp.rmi.server.compression.CompressionOutputStream;
import jcpp.rmi.server.statistic.IStatisticStream;

public class GatewayCompressionOutputStream extends FilterOutputStream implements IStatisticStream {
    private GatewayOutputStream gatewayOutputStream;
    private CompressionOutputStream compressionOutputStream;

    public GatewayCompressionOutputStream(OutputStream out, Route route, boolean bEnableCompression, int uncompressedBufferSize, int compressedBufferSize, int compressionThreshold, int compressionType) throws IOException {
        super(out);
        gatewayOutputStream = new GatewayOutputStream(out, route);
        if(bEnableCompression) {
            compressionOutputStream = new CompressionOutputStream(out, uncompressedBufferSize, compressedBufferSize, compressionThreshold, compressionType);
        }
    }

    public Route getRoute() {
        return gatewayOutputStream.getRoute();
    }

    public void write(int b) throws IOException {
        if(compressionOutputStream != null) {
            compressionOutputStream.write(b);
        } else {
            out.write(b);
        }
    }

    public void write(byte b[], int off, int len) throws IOException {
        if(compressionOutputStream != null) {
            compressionOutputStream.write(b, off, len);
        } else {
            out.write(b, off, len);
        }
    }

    public void flush() throws IOException {
        if(compressionOutputStream != null) {
            compressionOutputStream.flush();
        } else {
            out.flush();
        }
    }

    public void close() throws IOException {
        if(compressionOutputStream != null) {
            compressionOutputStream.close();
        }
        gatewayOutputStream.close();
        out.close();
    }

    public AtomicLong getNetworkDataCounter() {
        if(compressionOutputStream != null) {
            return compressionOutputStream.getNetworkDataCounter();
        }
        return null;
    }

    public boolean usesCompressionStream() {
        if(compressionOutputStream != null) {
            return true;
        }
        return false;
    }

    public void setNetworkDataCounter(AtomicLong networkByteCounter) {
        if(compressionOutputStream != null) {
            compressionOutputStream.setNetworkDataCounter(networkByteCounter);
        }
    }
}
