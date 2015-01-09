package jcpp.rmi.server.transport;

import java.nio.ByteBuffer;

public class ReadQueueEntry {
    private ByteBuffer buffer;


    public ReadQueueEntry(ByteBuffer buffer) {
        super();
        this.buffer = buffer;
    }


    public ByteBuffer getBuffer() {
        return buffer;
    }

    public void setBuffer(ByteBuffer buffer) {
        this.buffer = buffer;
    }

}
