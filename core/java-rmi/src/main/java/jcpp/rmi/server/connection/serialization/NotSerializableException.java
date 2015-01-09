package jcpp.rmi.server.connection.serialization;

import java.io.IOException;


public class NotSerializableException extends IOException {
    private static final long serialVersionUID = -3634347662562109631L;


    public NotSerializableException() {
    }

    public NotSerializableException(String message) {
        super(message);
    }

    public NotSerializableException(Throwable cause) {
        super(cause);
    }

    public NotSerializableException(String message, Throwable cause) {
        super(message, cause);
    }

}
