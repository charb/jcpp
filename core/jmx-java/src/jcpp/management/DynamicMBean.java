package jcpp.management;

public interface DynamicMBean {
	
	public Object invoke(String actionname, Object params[], String signature[]) throws Exception;
	
	public MBeanInfo getMBeanInfo();
	
	public Object getAttribute(String attribute) throws Exception;
	
	public void setAttribute(Attribute attribute) throws Exception;
	
}
