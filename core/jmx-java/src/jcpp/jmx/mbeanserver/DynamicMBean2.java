package jcpp.jmx.mbeanserver;

import jcpp.management.DynamicMBean;
import jcpp.management.MBeanServer;
import jcpp.management.ObjectName;

public interface DynamicMBean2 extends DynamicMBean{
	
	public Object getResource();
	
	public void registerFailed();
	
	public void preRegister2(MBeanServer mbs, ObjectName name) throws Exception;
	
}
