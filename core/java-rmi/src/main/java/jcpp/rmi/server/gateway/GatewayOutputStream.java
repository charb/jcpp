package jcpp.rmi.server.gateway;

import java.io.IOException;
import java.io.ObjectOutputStream;
import java.io.OutputStream;

public class GatewayOutputStream extends ObjectOutputStream{
    private Route route;

    public GatewayOutputStream(OutputStream out, Route route) throws IOException {
        super(out);
        this.route = route;
        writeObject(route);
        flush();
    }

    public Route getRoute() {
        return route;
    }
}
