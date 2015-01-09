package jcpp.rmi.server.statistic;

import java.util.concurrent.atomic.AtomicLong;

public interface IStatisticStream {
    
    public AtomicLong getNetworkDataCounter();

    public void setNetworkDataCounter(AtomicLong networkByteCounter);
    
    public boolean usesCompressionStream();
    
}
