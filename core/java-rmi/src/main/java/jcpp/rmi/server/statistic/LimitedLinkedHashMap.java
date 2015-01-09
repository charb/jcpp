package jcpp.rmi.server.statistic;

import java.io.Serializable;
import java.util.LinkedHashMap;
import java.util.Map;

public class LimitedLinkedHashMap<K, V> extends LinkedHashMap<K, V> implements Serializable{
    private static final long serialVersionUID = 1L;

    private int maxSize;

    public LimitedLinkedHashMap(int maxSize) {
        super();
        this.maxSize = maxSize;
    }

    public LimitedLinkedHashMap(int initialCapacity, float loadFactor, boolean accessOrder, int maxSize) {
        super(initialCapacity, loadFactor, accessOrder);
        this.maxSize = maxSize;
    }

    public LimitedLinkedHashMap(int initialCapacity, float loadFactor, int maxSize) {
        super(initialCapacity, loadFactor);
        this.maxSize = maxSize;
    }

    public LimitedLinkedHashMap(int initialCapacity, int maxSize) {
        super(initialCapacity);
        this.maxSize = maxSize;
    }

    public LimitedLinkedHashMap(Map<? extends K, ? extends V> m, int maxSize) {
        super(m);
        this.maxSize = maxSize;
    }
    
    protected boolean removeEldestEntry(Map.Entry<K,V> eldest) {
        return size() > maxSize;
    }

}
