package jcpp.rmi.server.connection.invocation;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Set;

import jcpp.rmi.server.transport.EndPoint;

public class InvocationQueue implements IInvocationQueue {
    private Map<EndPoint, List<InvocationItem>> queues;
    private Set<EndPoint> stoppedEndPoints;
    private boolean unexported;

    public InvocationQueue() {
        this.queues = new HashMap<EndPoint, List<InvocationItem>>();
        this.stoppedEndPoints = new HashSet<EndPoint>();
    }

    public synchronized void push(EndPoint endPoint, InvocationItem item) {
        List<InvocationItem> queue = queues.get(endPoint);
        if(queue == null) {
            queue = new ArrayList<InvocationItem>();
            queues.put(endPoint, queue);
        }
        queue.add(item);
        this.notifyAll();
    }

    public synchronized List<InvocationItem> pop(EndPoint endPoint, long timeout) throws Exception {
        List<InvocationItem> queue = queues.remove(endPoint);
        long waitStartTime = System.currentTimeMillis();
        long timeWaited = 0;
        while (!unexported && queue == null ) {
            if(stoppedEndPoints.remove(endPoint)) {
                break;
            }
            if((timeWaited = System.currentTimeMillis() - waitStartTime) >= timeout) {
                break;
            }
            try {
                this.wait(timeout - timeWaited);
            } catch (Exception e) {
            }
            queue = queues.remove(endPoint);
        }
        return queue;
    }

    public synchronized void stopPop(EndPoint endPoint) throws Exception {
        stoppedEndPoints.add(endPoint);
        this.notifyAll();
    }

    public synchronized void unexport(EndPoint endPoint) {
        queues.remove(endPoint);
        stoppedEndPoints.remove(endPoint);
        try {
            stopPop(endPoint);
        } catch (Exception e) {
        }
    }

    public synchronized void unexport() {
        unexported = true;
        this.notifyAll();
    }
}
