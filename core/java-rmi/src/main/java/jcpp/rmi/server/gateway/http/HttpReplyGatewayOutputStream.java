package jcpp.rmi.server.gateway.http;

import java.io.ByteArrayOutputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.OutputStream;

public class HttpReplyGatewayOutputStream extends ByteArrayOutputStream {
    private static byte[] emptyData = {0};
    private OutputStream outputStream;
    private boolean outputSent;

    public HttpReplyGatewayOutputStream(OutputStream outputStream) {
        this.outputStream = outputStream;
    }

    public synchronized void flush() throws IOException {
        if(!outputSent) {
            if(size() == 0) {
                write(emptyData);
            }
            DataOutputStream dataOutputStream = new DataOutputStream(outputStream);
            dataOutputStream.writeBytes("Content-type: application/zip\r\n");
            dataOutputStream.writeBytes("Content-length: " + size() + "\r\n");
            dataOutputStream.writeBytes("\r\n");
            writeTo(dataOutputStream);
            dataOutputStream.flush();
            reset();
            dataOutputStream.close();
            outputSent = true;
        }
    }

    public synchronized void close() throws IOException {
        flush();
    }
}
