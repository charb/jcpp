package jcpp.rmi.server.gateway;

import java.io.Serializable;

import java.net.UnknownHostException;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;


public class Route implements Serializable, Iterable<Address>, Cloneable {
    private static final long serialVersionUID = 2731749507109405573L;
    private List<Address> addressList;
    private boolean isHttp;


    public Route(boolean isHttp) {
        addressList = new ArrayList<Address>();
        this.isHttp = isHttp;
    }


    public boolean addAddress(String host, int port) {
        Address address = new Address(host, port);
        return addressList.add(address);
    }

    public boolean addAddress(Address address) {
        return addressList.add(address);
    }

    public boolean removeAddress(Address address) throws UnknownHostException {
        return addressList.remove(address);
    }

    public List<Address> getAddressList() {
        return addressList;
    }

    public Address getAddress(int index) {
        return addressList.get(index);
    }

    public Address peakAddress() {
        if ((addressList != null) && (addressList.size() > 0)) {
            Address address = addressList.get(0);
            return address;
        }
        return null;
    }

    public Address popAddress() {
        if ((addressList != null) && (addressList.size() > 0)) {
            Address address = addressList.get(0);
            addressList.remove(0);
            return address;
        }
        return null;
    }

    public void pushAddress(Address address) {
        if (addressList == null) {
            addressList = new ArrayList<Address>();
        }
        addressList.add(0, address);
    }

    public boolean isHttp() {
        return isHttp;
    }

    public int size() {
        if (addressList != null) {
            return addressList.size();
        }
        return -1;
    }

    public void clear() {
        addressList.clear();
    }

    @Override
    @SuppressWarnings("unchecked")
    public Route clone() throws CloneNotSupportedException {
        Route route = (Route) super.clone();
        route.addressList = (List<Address>) ((ArrayList<Address>) addressList).clone();
        return route;
    }

    @Override
    public Iterator<Address> iterator() {
        return addressList.iterator();
    }

    @Override
    public String toString() {
        String str = "Http: " + isHttp + ", adressList: ";
        if (addressList.size() > 0) {
            str += addressList.get(0);
            for (int i = 1; i < addressList.size(); i++) {
                str += "," + addressList.get(i);
            }
        } else {
            str += "<empty>";
        }
        return "Route[" + str + "]";
    }
}
