package jcpp.rmi.server.gateway.http;

import java.io.ByteArrayInputStream;
import java.io.DataInputStream;
import java.io.FilterInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.util.concurrent.atomic.AtomicLong;

import jcpp.rmi.server.gateway.GatewayCompressionInputStream;
import jcpp.rmi.server.gateway.GatewayConfiguration;
import jcpp.rmi.server.statistic.IStatisticStream;

import org.apache.commons.io.IOUtils;

public class HttpReplyGatewayInputStream extends FilterInputStream implements IStatisticStream {
    protected GatewayCompressionInputStream gatewayInputStream;
    private int bytesLeft;
    private int bytesLeftAtMark;

    public HttpReplyGatewayInputStream(InputStream in, boolean isGateway, GatewayConfiguration gatewayConfiguration) throws IOException, ClassNotFoundException {
        super(in);
        if(in.markSupported()) {
            in.mark(0);
        }
        DataInputStream dataInputStream = new DataInputStream(in);
        String line;
        String key = "content-length:";
        do {
            line = dataInputStream.readLine();
            if(line.indexOf(key) != -1) {
                bytesLeft = Integer.parseInt(line.substring(key.length()).trim());
            }
        } while ((line.length() != 0) && (line.charAt(0) != '\r') && (line.charAt(0) != '\n') );
        if(bytesLeft <= 0) {
            bytesLeft = Integer.MAX_VALUE;
        }

        byte[] read = toByteArray(dataInputStream, bytesLeft);
        ByteArrayInputStream bis = new ByteArrayInputStream(read);
        gatewayInputStream = new GatewayCompressionInputStream(bis, gatewayConfiguration.isCompressionEnabled() && !isGateway, gatewayConfiguration);
        read = IOUtils.toByteArray(gatewayInputStream);
        bytesLeft = read.length;
        bytesLeftAtMark = bytesLeft;
        this.in = new ByteArrayInputStream(read);
    }

    /**
     * Similar to IOUtils.toByteArray(InputStream) except that it reads until
     * in.read() returns 0.
     * 
     * @param in
     *            the InputStream to read from
     * @param len
     *            the expected length of the byte array
     * @return the requested byte array
     * @throws IOException
     */
    private byte[] toByteArray(InputStream in, int len) throws IOException {
        byte[] read = new byte[len];
        int offSet = 0;
        int r = 0;
        while (len > 0 && (r = in.read(read, offSet, len)) != -1 ) {
            len -= r;
            offSet += r;
        }
        assert len == 0;
        return read;
    }

    public GatewayCompressionInputStream getGatewayCompressionInputStream() {
        return gatewayInputStream;
    }

    public int available() throws IOException {
        int bytesAvailable = in.available();
        if(bytesAvailable > bytesLeft) {
            bytesAvailable = bytesLeft;
        }
        return bytesAvailable;
    }

    public void mark(int readlimit) {
        in.mark(readlimit);
        if(in.markSupported()) {
            bytesLeftAtMark = bytesLeft;
        }
    }

    public void reset() throws IOException {
        in.reset();
        bytesLeft = bytesLeftAtMark;
    }

    public long skip(long n) throws IOException {
        if(n > bytesLeft) {
            n = bytesLeft;
        }
        long bytesSkipped = in.skip(n);
        bytesLeft -= bytesSkipped;
        return bytesSkipped;
    }

    public int read() throws IOException {
        if(bytesLeft > 0) {
            int data = in.read();
            if(data != -1) {
                bytesLeft--;
            }
            return data;
        }
        return -1;

    }

    public int read(byte b[], int off, int len) throws IOException {
        if(bytesLeft == 0 && len > 0) {
            return -1;
        }
        if(len > bytesLeft) {
            len = bytesLeft;
        }
        int bytesRead = in.read(b, off, len);
        bytesLeft -= bytesRead;
        return bytesRead;
    }

    public AtomicLong getNetworkDataCounter() {
        return gatewayInputStream.getNetworkDataCounter();
    }

    public boolean usesCompressionStream() {
        return gatewayInputStream.usesCompressionStream();
    }

    public void setNetworkDataCounter(AtomicLong networkByteCounter) {
        gatewayInputStream.setNetworkDataCounter(networkByteCounter);
    }

}
