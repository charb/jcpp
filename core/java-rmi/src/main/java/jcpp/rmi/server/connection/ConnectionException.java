package jcpp.rmi.server.connection;

public class ConnectionException extends Exception{
    private static final long serialVersionUID = 1470950606719849553L;

    public ConnectionException() {
        super();
    }
    
    public ConnectionException(String message) {
        super(message);
    }
    
    public ConnectionException(String message, Throwable cause) {
        super(message, cause);
    }
    
}
