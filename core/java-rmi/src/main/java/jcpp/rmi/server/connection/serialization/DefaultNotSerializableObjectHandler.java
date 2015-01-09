package jcpp.rmi.server.connection.serialization;

public class DefaultNotSerializableObjectHandler implements INotSerializableObjectHandler {

    public DefaultNotSerializableObjectHandler() {
    }


    @Override
    public Object handleNotSerializableObject(Object obj) {
        return new NotSerializableException("Cannot serialize the object of type: " + obj.getClass().getName() + ". Object: " + obj);
    }

}
