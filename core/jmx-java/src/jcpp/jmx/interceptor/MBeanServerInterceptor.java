package jcpp.jmx.interceptor;

import jcpp.management.MBeanServerConnection;
import jcpp.management.ObjectInstance;
import jcpp.management.ObjectName;

public interface MBeanServerInterceptor extends MBeanServerConnection{
	
	public ObjectInstance registerMBean(Object object, ObjectName name) throws Exception;
	
	public Object invoke(ObjectName name, String operationName, Object params[], String signature[]) throws Exception;
	
	
}
