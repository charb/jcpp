package com.example;

/*
 * HelloMBean.java - MBean interface describing the management operations and
 * attributes for the Hello World MBean. In this case there are two operations,
 * "sayHello" and "add", and two attributes, "Name" and "CacheSize".
 */


public interface CopyOfHelloMBean {
    //-----------
    // operations
    //-----------

    public void say();
    public int adds(int x, int y);

    //-----------
    // attributes
    //-----------

    // a read-only attribute called Name of type String
    public String getName();

    // a read-write attribute called CacheSize of type int
    public int getCacheSize();
    public void setCacheSize(int size);
}
