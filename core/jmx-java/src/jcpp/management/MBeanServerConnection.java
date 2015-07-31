package jcpp.management;

public interface MBeanServerConnection {
	
	
	public Object invoke (ObjectName name, String operationName, Object params[], String signature[]) throws Exception;
	
	public Object getAttribute(ObjectName name, String attribute) throws Exception;
	
	public void setAttribute(ObjectName name, Attribute attribute) throws Exception;
	
}
