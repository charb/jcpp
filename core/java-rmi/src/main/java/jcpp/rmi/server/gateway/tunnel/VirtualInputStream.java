package jcpp.rmi.server.gateway.tunnel;

import java.io.IOException;
import java.io.InputStream;

import java.util.Iterator;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingQueue;


@Deprecated
public class VirtualInputStream extends InputStream {
    private BlockingQueue<Byte[]> queue;
    private Byte[] currentBuffer;
    private int currentPos;
    private volatile boolean isClosed;


    public VirtualInputStream() {
        queue = new LinkedBlockingQueue<Byte[]>();
    }


    public void addData(byte[] b, int off, int length) {
        Byte[] dest = new Byte[length];
        for (int i = 0; i < length; i++) {
            dest[i] = b[i + off];
        }
        queue.add(dest);
    }

    public void endStream() {
        queue.add(new Byte[0]);
    }

    @Override
    public int read(byte[] b, int off, int len) throws IOException {
        checkIfOpen();
        int count = 0;
        while (count < len) {
            if ((currentBuffer == null) || (currentBuffer.length == currentPos)) {
                if ((count > 0) && (queue.isEmpty())) {
                    return count;
                } else {
                    try {
                        currentBuffer = queue.take();
                        currentPos = 0;
                        if ((currentBuffer == null) || (currentBuffer.length == 0)) {
                            return (count == 0) ? -1 : count;
                        }
                    } catch (InterruptedException e) {
                        return (count == 0) ? -1 : count;
                    }
                }
            }
            int toCopy = Math.min(currentBuffer.length - currentPos, len - count);
            for (int i = 0; i < toCopy; i++) {
                b[i + off + count] = currentBuffer[i + currentPos];
            }
            currentPos += toCopy;
            count += toCopy;

        }
        assert (count == len);
        return count;
    }

    @Override
    public int read() throws IOException {
        checkIfOpen();
        if ((currentBuffer == null) || (currentBuffer.length == currentPos)) {
            try {
                currentBuffer = queue.take();
                currentPos = 0;
                if ((currentBuffer == null) || (currentBuffer.length == 0)) {
                    return -1;
                }
            } catch (InterruptedException e) {
                return -1;
            }
        }
        int b = currentBuffer[currentPos++] & 0xff;
        return b;
    }

    @Override
    public int available() throws IOException {
        Iterator<Byte[]> iterator = queue.iterator();
        int count = 0;
        while (iterator.hasNext()) {
            count += iterator.next().length;
        }
        return (currentBuffer.length - currentPos) + count;
    }

    @Override
    public void close() throws IOException {
        if (isClosed == false) {
            endStream();
            isClosed = true;
        }
    }

    private void checkIfOpen() throws IOException {
        if (isClosed) {
            throw new IOException("Stream closed");
        }
    }
}
