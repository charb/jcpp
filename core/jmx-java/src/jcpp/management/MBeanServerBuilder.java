package jcpp.management;

import jcpp.jmx.mbeanserver.JmxMBeanServer;


public class MBeanServerBuilder {

	public MBeanServerBuilder(){
	}

	public MBeanServer newMBeanServer(String defaultDomain, MBeanServer outer){
		return JmxMBeanServer.newMBeanServer(defaultDomain, outer);
	}
	
}
