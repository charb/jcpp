package jcpp.rmi.server.connection.invocation;

import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;

import jcpp.rmi.server.transport.EndPoint;


public class InvocationRouter implements IInvocationRouter {
    private Map<String, Set<String>> invocationMap;


    public InvocationRouter() {
        this.invocationMap = new HashMap<String, Set<String>>();
    }


    public void addInvocationRoute(String fromSite, String toSite) {
        Set<String> toSiteSet = invocationMap.get(fromSite);
        if (toSiteSet == null) {
            toSiteSet = new HashSet<String>();
            invocationMap.put(fromSite, toSiteSet);
        }
        toSiteSet.add(toSite);
    }

    @Override
    public boolean canInvoke(EndPoint fromEndPoint, EndPoint toEndPoint) {
        if ((fromEndPoint != null) && (toEndPoint != null)) {
            if (fromEndPoint.getSite().equals(toEndPoint.getSite())) {
                return true;
            }
            Set<String> toSiteSet = invocationMap.get(fromEndPoint.getSite());
            if (toSiteSet != null) {
                return toSiteSet.contains(toEndPoint.getSite());
            }
        }
        return false;
    }

}
