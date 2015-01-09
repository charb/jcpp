package jcpp.rmi.server.transport;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.EOFException;
import java.io.IOException;
import java.io.Serializable;
import java.io.UTFDataFormatException;

import jcpp.rmi.server.gateway.Address;

public class EndPoint implements Serializable{
    private static final long serialVersionUID = 1L;
    private Address address;
    private String site;

    public EndPoint(String host, int port, String site) {
        this.address = new Address(host, port);
        this.site = site;
    }

    public EndPoint(DataInputStream in) throws IOException, EOFException, UTFDataFormatException {
        String host = in.readUTF();
        int port = in.readInt();
        this.site = in.readUTF();
        this.address = new Address(host, port);
    }

    public void write(DataOutputStream out) throws IOException {
        out.writeUTF(address.getHostName());
        out.writeInt(address.getPort());
        out.writeUTF(site);
    }

    public String getHost() {
        return address.getHostName();
    }

    public int getPort() {
        return address.getPort();
    }

    public void setPort(int port) {
        this.address.setPort(port);
    }

    public Address getAddress() {
        return address;
    }
    
    public String getSite() {
        return site;
    }

    public String toString() {
        return "EndPoint[" + address + ", Site[" + site + "]]";
    }
    
    public int hashCode(){
        return address.getHostName().hashCode()+ address.getPort() + site.hashCode();
    }
    
    public boolean equals(Object obj) {
        if(obj != null && obj instanceof EndPoint) {
            EndPoint endPoint = (EndPoint) obj;
            return address.equals(endPoint.getAddress())&& site.equals(endPoint.getSite());
        }
        return false;
    }
}
