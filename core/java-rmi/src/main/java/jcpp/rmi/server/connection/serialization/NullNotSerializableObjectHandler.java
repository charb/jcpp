package jcpp.rmi.server.connection.serialization;

public class NullNotSerializableObjectHandler implements INotSerializableObjectHandler {

    public NullNotSerializableObjectHandler() {
    }


    @Override
    public Object handleNotSerializableObject(Object obj) {
        return null;
    }

}
