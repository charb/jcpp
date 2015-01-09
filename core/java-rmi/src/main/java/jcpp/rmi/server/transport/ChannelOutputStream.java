package jcpp.rmi.server.transport;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.OutputStream;

import java.nio.ByteBuffer;


public class ChannelOutputStream extends OutputStream {

    private ByteArrayOutputStream baos;
    private ChannelConnection connection;
    private int capacity;


    public ChannelOutputStream(ChannelConnection connection) {
        this.connection = connection;
        this.capacity = connection.getGatewayConfiguration().getSendBufferSize();
        this.baos = new ByteArrayOutputStream(capacity);
    }


    @Override
    public void write(int b) throws IOException {
        baos.write(b);
        if (baos.size() >= capacity) {
            flush();
        }
    }

    @Override
    public void write(byte[] b, int off, int len) throws IOException {
        while ((baos.size() + len) > capacity) {
            int numBytesToWrite = capacity - baos.size();
            baos.write(b, off, numBytesToWrite);
            flush();
            off += numBytesToWrite;
            len -= numBytesToWrite;
        }
        baos.write(b, off, len);
    }

    @Override
    public void flush() throws IOException {
        if (baos.size() > 0) {
            ByteBuffer byteBuffer = ByteBuffer.wrap(baos.toByteArray());
            connection.write(byteBuffer);
            baos.reset();
        }
    }

    @Override
    public void close() throws IOException {
        flush();
        baos.close();
    }

}
