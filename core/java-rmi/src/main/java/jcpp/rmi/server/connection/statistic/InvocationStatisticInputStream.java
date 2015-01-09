package jcpp.rmi.server.connection.statistic;

import java.io.IOException;
import java.io.InputStream;
import java.io.ObjectInputStream;

public class InvocationStatisticInputStream extends ObjectInputStream {

    public InvocationStatisticInputStream(InputStream inputStream) throws IOException {
        super(inputStream);
    }

    
}
