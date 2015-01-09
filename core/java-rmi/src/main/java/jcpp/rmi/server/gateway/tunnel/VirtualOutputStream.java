package jcpp.rmi.server.gateway.tunnel;

import java.io.IOException;
import java.io.OutputStream;


@Deprecated
public class VirtualOutputStream extends OutputStream {
    private byte[] data;
    private int dataLength;
    private VirtualSocket virtualSocket;
    private GatewayTunnel tunnel;


    public VirtualOutputStream(VirtualSocket virtualSocket, GatewayTunnel tunnel) {
        this.virtualSocket = virtualSocket;
        this.tunnel = tunnel;
        this.data = new byte[GatewayTunnel.BUFFER_SIZE];
    }


    @Override
    public void write(int b) throws IOException {
        data[dataLength++] = (byte) b;
        if (dataLength >= data.length) {
            sendData();
        }
    }

    @Override
    public void flush() throws IOException {
        sendData();
    }

    @Override
    public void close() throws IOException {
    }

    protected void sendData() throws IOException {
        if (dataLength > 0) {
            tunnel.write(data, dataLength, virtualSocket.getId());
            dataLength = 0;
        }
    }

}
