package jcpp.rmi.server.gateway;

import java.io.Serializable;


public class Address implements Serializable, Cloneable {
    private static final long serialVersionUID = 1L;
    private String hostName;
    private int port;


    public Address(String host, int port) {
        this.hostName = host;
        this.port = port;
    }


    public String getHostName() {
        return hostName;
    }

    public void setHostName(String host) {
        this.hostName = host;
    }

    public int getPort() {
        return port;
    }

    public void setPort(int port) {
        this.port = port;
    }

    @Override
    public boolean equals(Object obj) {
        if ((obj != null) && (obj instanceof Address)) {
            Address address = (Address) obj;
            return (this.hostName.equals(address.getHostName()) && (this.port == address.getPort()));
        }
        return false;
    }

    @Override
    public Address clone() throws CloneNotSupportedException {
        return (Address) super.clone();
    }

    @Override
    public String toString() {
        return "Address[" + hostName + ":" + port + "]";
    }

    @Override
    public int hashCode() {
        return (hostName != null) ? ((hostName.hashCode() * 37) + port) : port;
    }
}
