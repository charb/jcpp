package jcpp.management;

import jcpp.jmx.mbeanserver.JmxMBeanServer;
import jcpp.jmx.mbeanserver.MBeanServerDelegate;

public class MBeanServerBuilder {

	public MBeanServerBuilder(){
	}
	
	public MBeanServerDelegate newMBeanServerDelegate() {
		return JmxMBeanServer.newMBeanServerDelegate();
	}

	public MBeanServer newMBeanServer(String defaultDomain, MBeanServer outer, MBeanServerDelegate delegate){
		return JmxMBeanServer.newMBeanServer(defaultDomain, outer, delegate);
	}
	
}
