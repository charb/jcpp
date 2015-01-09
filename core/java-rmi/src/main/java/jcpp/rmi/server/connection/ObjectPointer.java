package jcpp.rmi.server.connection;

import java.io.Serializable;

import jcpp.rmi.server.transport.EndPoint;

public class ObjectPointer implements Serializable {
    private static final long serialVersionUID = 1L;
    private EndPoint endPoint;
    private String id;

    public ObjectPointer(EndPoint endPoint, String id) {
        this.endPoint = endPoint;
        this.id = id;
    }

    public EndPoint getEndPoint() {
        return endPoint;
    }

    public String getId() {
        return id;
    }

    public int hashCode() {
        int hash = 1;
        hash = hash * 31 + id.hashCode();
        hash = hash * 31 + endPoint.hashCode();
        return hash;
    }

    public boolean equals(Object object) {
        boolean equals = object instanceof ObjectPointer;
        if(equals) {
            ObjectPointer objectPointer = (ObjectPointer) object;
            equals = objectPointer.endPoint.equals(endPoint) && objectPointer.id.equals(id);
        }
        return equals;
    }

    public String toString() {
        return "ObjectPointer[" + endPoint + "[Id:" + id + "]]";
    }
}
