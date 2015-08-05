package jcpp.management;

public interface MBeanServer extends MBeanServerConnection{
	
	
	public ObjectInstance registerMBean(Object object, ObjectName name) throws Exception;
	
	@Override
	public Object invoke(ObjectName name, String operationName, Object params[], String signature[]) throws Exception;
	
	
	@Override
	public Object getAttribute(ObjectName name, String attribute) throws Exception;
	
	@Override
	public void setAttribute(ObjectName name, Attribute attribute) throws Exception;
	
}
