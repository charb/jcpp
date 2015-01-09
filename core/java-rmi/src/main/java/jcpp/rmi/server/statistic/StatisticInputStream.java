package jcpp.rmi.server.statistic;

import java.io.IOException;
import java.io.InputStream;
import java.util.concurrent.atomic.AtomicLong;

public class StatisticInputStream extends InputStream {
    private InputStream in;
    private AtomicLong applicationDataCounter;

    public StatisticInputStream(InputStream in) {
        this.in = in;
        this.applicationDataCounter = new AtomicLong();
    }

    public int read() throws IOException {
        int read = in.read();
        if(read != -1) {
            applicationDataCounter.incrementAndGet();
        }
        return read;
    }

    public int read(byte b[], int off, int len) throws IOException {
        int read = in.read(b, off, len);
        if(read != -1) {
            applicationDataCounter.addAndGet(read);
        }
        return read;
    }

    public AtomicLong getApplicationDataCounter() {
        return applicationDataCounter;
    }

    public void setApplicationDataCounter(AtomicLong applicationByteCounter) {
        this.applicationDataCounter = applicationByteCounter;
    }

    public AtomicLong getNetworkDataCounter() {
        if(in instanceof IStatisticStream && ((IStatisticStream) in).usesCompressionStream()) {
            return ((IStatisticStream) in).getNetworkDataCounter();
        }
        return applicationDataCounter;
    }

    public void setNetworkDataCounter(AtomicLong networkByteCounter) {
        if(in instanceof IStatisticStream) {
            ((IStatisticStream) in).setNetworkDataCounter(networkByteCounter);
        }
    }

    public long skip(long n) throws IOException {
        return in.skip(n);
    }

    public int available() throws IOException {
        return in.available();
    }

    public void mark(int readlimit) {
        in.mark(readlimit);
    }

    public boolean markSupported() {
        return in.markSupported();
    }

    public void reset() throws IOException {
        in.reset();
    }

    public void close() throws IOException {
        in.close();
    }

}
