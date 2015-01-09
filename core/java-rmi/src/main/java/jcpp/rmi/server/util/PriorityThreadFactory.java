package jcpp.rmi.server.util;

import java.util.concurrent.atomic.AtomicInteger;

import edu.emory.mathcs.backport.java.util.concurrent.ThreadFactory;


public class PriorityThreadFactory implements ThreadFactory {
    static final AtomicInteger poolNumber = new AtomicInteger(1);
    final ThreadGroup group;
    final AtomicInteger threadNumber = new AtomicInteger(1);
    final String namePrefix;


    public PriorityThreadFactory() {
        SecurityManager s = System.getSecurityManager();
        group = (s != null) ? s.getThreadGroup() : Thread.currentThread().getThreadGroup();
        namePrefix = "pool-" +poolNumber.getAndIncrement() +"-thread-";
    }


    @Override
    public Thread newThread(Runnable r) {
        Thread t = new Thread(group, r, "MRMI Scheduled Executor Thread (" + namePrefix + threadNumber.getAndIncrement() + ")", 0);
        if (t.isDaemon()) {
            t.setDaemon(false);
        }
        t.setPriority(Thread.MAX_PRIORITY);
        return t;
    }
}
