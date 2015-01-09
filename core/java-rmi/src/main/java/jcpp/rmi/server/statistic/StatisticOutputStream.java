package jcpp.rmi.server.statistic;

import java.io.IOException;
import java.io.OutputStream;
import java.util.concurrent.atomic.AtomicLong;

public class StatisticOutputStream extends OutputStream {
    private OutputStream out;
    private AtomicLong applicationDataCounter;

    public StatisticOutputStream(OutputStream out) {
        this.out = out;
        this.applicationDataCounter = new AtomicLong();
    }

    public void write(int b) throws IOException {
        applicationDataCounter.incrementAndGet();
        out.write(b);
    }

    public void write(byte b[], int off, int len) throws IOException {
        applicationDataCounter.addAndGet(len);
        out.write(b, off, len);
    }

    public void flush() throws IOException {
        out.flush();
    }

    public void close() throws IOException {
        out.close();
    }

    public AtomicLong getApplicationDataCounter() {
        return applicationDataCounter;
    }

    public void setApplicationByteCounter(AtomicLong applicationByteCounter) {
        this.applicationDataCounter = applicationByteCounter;
    }

    public AtomicLong getNetworkDataCounter() {
        if((out instanceof IStatisticStream) && ((IStatisticStream) out).usesCompressionStream()) {
            return ((IStatisticStream) out).getNetworkDataCounter();
        }
        return applicationDataCounter;
    }

    public void setNetworkByteCounter(AtomicLong networkByteCounter) {
        if((out instanceof IStatisticStream) && ((IStatisticStream) out).usesCompressionStream()) {
            ((IStatisticStream) out).setNetworkDataCounter(networkByteCounter);
        } else {
            applicationDataCounter = networkByteCounter;
        }

    }

}
