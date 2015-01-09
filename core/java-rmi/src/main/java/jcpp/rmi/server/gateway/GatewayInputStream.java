package jcpp.rmi.server.gateway;

import java.io.IOException;
import java.io.InputStream;
import java.io.ObjectInputStream;

public class GatewayInputStream extends ObjectInputStream {
    private Route route;

    public GatewayInputStream(InputStream in) throws IOException, ClassNotFoundException {
        super(in);
        route = (Route) readObject();
    }

    public Route getRoute() {
        return route;
    }
}
