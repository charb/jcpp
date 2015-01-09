package jcpp.rmi.server.transport;

import java.io.EOFException;
import java.io.IOException;
import java.io.InputStream;

import java.nio.ByteBuffer;


public class ChannelInputStream extends InputStream {
    private byte[] inputData;
    private int position;
    private int dataSize;

    private ChannelConnection connection;


    public ChannelInputStream(ChannelConnection connection) {
        this.connection = connection;
        inputData = new byte[connection.getGatewayConfiguration().getReceiveBufferSize()];
    }


    @Override
    public int read() throws IOException {
        if (position >= dataSize) {
            try {
                fillInputData();
            } catch (EOFException e) {
                return -1;
            }
        }
        int n = inputData[position++] & 0xff;
        return n;
    }

    @Override
    public int read(byte[] b, int off, int len) throws IOException {
        int count = 0;
        while (count < len) {
            if (position >= dataSize) {
                try {
                    if ((count > 0) && (connection.getReadQueue().isEmpty())) {
                        return count;
                    } else {
                        fillInputData();
                    }
                } catch (EOFException eof) {
                    if (count == 0) {
                        count = -1;
                    }
                    return count;
                }
            }
            int toCopy = Math.min(dataSize - position, len - count);
            System.arraycopy(inputData, position, b, off + count, toCopy);
            position += toCopy;
            count += toCopy;
        }
        assert (count == len);
        return count;
    }

    @Override
    public long skip(long n) throws IOException {
        return super.skip(n);
    }

    @Override
    public int available() throws IOException {
        int sizeInQueue = 0;
        for (ReadQueueEntry entry : connection.getReadQueue()) {
            sizeInQueue += (entry.getBuffer() != null) ? entry.getBuffer().remaining() : 0;
        }
        return (dataSize - position) + sizeInQueue;
    }

    @Override
    public void mark(int readlimit) {
        super.mark(readlimit);
    }

    @Override
    public boolean markSupported() {
        return super.markSupported();
    }

    @Override
    public void reset() throws IOException {
        super.reset();
        position = 0;
    }

    @Override
    public void close() throws IOException {
        connection.close();
    }

    private void fillInputData() throws IOException {
        ByteBuffer byteBuffer;
        if (!connection.getChannel().isOpen()) {
            throw new IOException("channel is closed");
        }
        try {
            ReadQueueEntry queueEntry = connection.getReadQueue().take();
            byteBuffer = queueEntry.getBuffer();
        } catch (InterruptedException e) {
            throw new EOFException();
        }
        if (byteBuffer == null) {
            throw new EOFException();
        }

        dataSize = byteBuffer.position();
        if (dataSize <= 0) {
            position = 0;
            return;
        }
        System.arraycopy(byteBuffer.array(), 0, inputData, 0, dataSize);
        position = 0;
    }

}
