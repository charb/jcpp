package jcpp.rmi.server.util;

import edu.emory.mathcs.backport.java.util.concurrent.helpers.NanoTimer;


public class MillisProvider implements NanoTimer {

    public MillisProvider() {
    }


    @Override
    public long nanoTime() {
        return System.currentTimeMillis() * 1000000L;
    }
}
