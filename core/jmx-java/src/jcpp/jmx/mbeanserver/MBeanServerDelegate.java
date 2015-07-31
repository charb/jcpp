package jcpp.jmx.mbeanserver;

import jcpp.management.Attribute;
import jcpp.management.DynamicMBean;
import jcpp.management.MBeanRegistration;
import jcpp.management.MBeanServer;
import jcpp.management.ObjectName;

public class MBeanServerDelegate  implements DynamicMBean, MBeanRegistration {


	
	public MBeanServerDelegate() {
		super();
	}

	@Override
	final public void postRegister(Boolean registrationDone) {
	}

	@Override
	public ObjectName preRegister(MBeanServer server, ObjectName name) throws Exception {
		return name;
	}

	@Override
	public Object invoke(String actionname, Object[] params, String[] signature) throws Exception {
		// TODO Auto-generated method stub
		System.out.println("6 implement me " + this.getClass().getName());
		return null;
	}


	@Override
	public Object getAttribute(String attribute) throws Exception {
		// TODO
		System.out.println("1 implement me " + this.getClass().getName());
		return null;
	}

	@Override
	public void setAttribute(Attribute attribute) throws Exception {
		// TODO Auto-generated method stub
		System.out.println("2 implement me " + this.getClass().getName());
	}

}
