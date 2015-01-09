package jcpp.rmi.server.gateway;

public interface IGatewaySocket {
    
    public abstract Route getRoute();
    
    public abstract boolean isReausable();

}
