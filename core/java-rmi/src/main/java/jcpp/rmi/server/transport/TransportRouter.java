package jcpp.rmi.server.transport;

import java.util.HashMap;
import java.util.Map;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import jcpp.rmi.server.gateway.Route;

public class TransportRouter implements ITransportRouter {
    private static Log log = LogFactory.getLog(TransportRouter.class);
    private Map<String, Map<String, Route>> routeMap;

    public TransportRouter() {
        routeMap = new HashMap<String, Map<String, Route>>();
    }

    public void addRoute(String localSite, String remoteSite, Route route) {
        Map<String, Route> internalMap = routeMap.get(localSite);
        if(internalMap == null) {
            internalMap = new HashMap<String, Route>();
            routeMap.put(localSite, internalMap);
        }
        internalMap.put(remoteSite, route);
    }

    public Route findRoute(String localSite, EndPoint remoteEndPoint) {
        if(localSite != null && remoteEndPoint != null) {
            if(localSite.equals(remoteEndPoint.getSite())) {
                Route route = new Route(false);
                route.addAddress(remoteEndPoint.getHost(), remoteEndPoint.getPort());
                return route;
            }
            Map<String, Route> internalMap = routeMap.get(localSite);
            if(internalMap != null) {
                Route route=internalMap.get(remoteEndPoint.getSite());
                if (route!=null){
                    try {
                        route = route.clone();
                        route.addAddress(remoteEndPoint.getHost(), remoteEndPoint.getPort());
                        return route;
                    } catch (CloneNotSupportedException e) {
                        if(log.isDebugEnabled()) {
                            log.debug("Error trying to clone route: " + route + " in findRoute(localSite: " + localSite + ", remoteEndPoint: " + remoteEndPoint + ")", e);
                        }
                    }
                }
            }
        }
        return null;
    }
}
