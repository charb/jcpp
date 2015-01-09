package jcpp.rmi.server.gateway.http;

import java.io.EOFException;
import java.io.FilterInputStream;
import java.io.IOException;
import java.io.InputStream;

import java.util.concurrent.atomic.AtomicLong;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import jcpp.rmi.server.compression.CompressionInputStream;
import jcpp.rmi.server.statistic.IStatisticStream;


public class HttpRequestGatewayInputStream extends FilterInputStream implements IStatisticStream {
    private static Log log = LogFactory.getLog(HttpRequestGatewayInputStream.class);
    private HttpRequestGatewaySocket httpGatewaySocket;
    private AtomicLong networkByteCounter;


    public HttpRequestGatewayInputStream(InputStream in, HttpRequestGatewaySocket httpGatewaySocket) throws IOException {
        super(in);
        this.httpGatewaySocket = httpGatewaySocket;
        this.networkByteCounter = new AtomicLong();
    }


    @Override
    public int read() throws IOException {
        createInputStream();
        try {
            return in.read();
        } catch (EOFException e) {
            return -1;
        }
    }

    @Override
    public int read(byte[] b, int off, int len) throws IOException {
        if (len == 0) {
            return 0;
        }
        createInputStream();
        try {
            return in.read(b, off, len);
        } catch (EOFException e) {
            return -1;
        }
    }

    @Override
    public long skip(long n) throws IOException {
        if (n == 0) {
            return 0;
        }
        createInputStream();
        return in.skip(n);
    }

    @Override
    public int available() throws IOException {
        createInputStream();
        return in.available();
    }

    @Override
    public void close() throws IOException {
        httpGatewaySocket.close();
    }

    @Override
    public synchronized void mark(int readlimit) {
        if (in == null) {
            try {
                createInputStream();
            } catch (Throwable throwable) {
                if (log.isDebugEnabled()) {
                    log.debug("Error creating inputstream while calling mark() - Socket: " + httpGatewaySocket, throwable);
                }
                return;
            }
        }
        in.mark(readlimit);
    }

    @Override
    public synchronized void reset() throws IOException {
        createInputStream();
        in.reset();
    }

    @Override
    public boolean markSupported() {
        if (in == null) {
            try {
                createInputStream();
            } catch (Throwable throwable) {
                if (log.isDebugEnabled()) {
                    log.debug("Error creating inputstream while calling markSupported() - Socket: " + httpGatewaySocket, throwable);
                }
                return false;
            }
        }
        return in.markSupported();
    }

    @Override
    public AtomicLong getNetworkDataCounter() {
        if (usesCompressionStream()) {
            return networkByteCounter;
        }
        return null;
    }

    @Override
    public boolean usesCompressionStream() {
        if (in instanceof CompressionInputStream) {
            return true;
        }
        return false;
    }

    @Override
    public void setNetworkDataCounter(AtomicLong networkByteCounter) {
        this.networkByteCounter = networkByteCounter;
        if (usesCompressionStream()) {
            if (in != null) {
                ((IStatisticStream) in).setNetworkDataCounter(networkByteCounter);
            }
        }
    }

    private void createInputStream() throws IOException {
        if (in == null) {
            in = httpGatewaySocket.createInputStream();
            setNetworkDataCounter(networkByteCounter);
        }
    }
}
