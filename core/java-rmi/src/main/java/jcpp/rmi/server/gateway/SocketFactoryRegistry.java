package jcpp.rmi.server.gateway;

import jcpp.rmi.server.transport.TransportRouter;

public class SocketFactoryRegistry {

    private static TransportRouter transportRouter;
    private static String localSite;

    public static TransportRouter getTransportRouter() {
        return transportRouter;
    }

    public static void setTransportRouter(TransportRouter transportRouter) {
        SocketFactoryRegistry.transportRouter = transportRouter;
    }

    public static String getLocalSite() {
        return localSite;
    }

    public static void setLocalSite(String localSite) {
        SocketFactoryRegistry.localSite = localSite;
    }
}
