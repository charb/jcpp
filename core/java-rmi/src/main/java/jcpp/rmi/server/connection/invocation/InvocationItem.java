package jcpp.rmi.server.connection.invocation;

import java.io.Serializable;

public class InvocationItem implements Serializable {
    private static final long serialVersionUID = -8082595495558250242L;

    private long digest;
    private Object[] args;
    private String id;

    public InvocationItem(long digest, Object[] args, String id) {
        this.digest = digest;
        this.args = args;
        this.id = id;
    }

    public long getDigest() {
        return digest;
    }

    public Object[] getArgs() {
        return args;
    }

    public String getId() {
        return id;
    }

}
