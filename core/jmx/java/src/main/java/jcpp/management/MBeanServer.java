package jcpp.management;

public interface MBeanServer {
	
	
	public ObjectInstance registerMBean(Object object, String name) throws Exception;
	
	public Object invoke(String name, String operationName, Object params[], String signature[]) throws Exception;
	
	

	public Object getAttribute(String name, String attribute) throws Exception;

	
	public void setAttribute(String name, Attribute attribute) throws Exception;
	
}
