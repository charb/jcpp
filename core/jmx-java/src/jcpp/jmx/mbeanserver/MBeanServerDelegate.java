package jcpp.jmx.mbeanserver;

import jcpp.management.Attribute;
import jcpp.management.DynamicMBean;
import jcpp.management.MBeanAttributeInfo;
import jcpp.management.MBeanInfo;
import jcpp.management.MBeanRegistration;
import jcpp.management.MBeanServer;
import jcpp.management.ObjectName;

public class MBeanServerDelegate  implements DynamicMBean, MBeanRegistration {

	private MBeanInfo delegateInfo;

	private static final MBeanAttributeInfo[] attributeInfos = new MBeanAttributeInfo[] { new MBeanAttributeInfo("MBeanServerId", "java.lang.String", "The MBean server agent identification", true, false, false),
			new MBeanAttributeInfo("SpecificationName", "java.lang.String", "The full name of the JMX specification " + "implemented by this product.", true, false, false),
			new MBeanAttributeInfo("SpecificationVersion", "java.lang.String", "The version of the JMX specification " + "implemented by this product.", true, false, false),
			new MBeanAttributeInfo("SpecificationVendor", "java.lang.String", "The vendor of the JMX specification " + "implemented by this product.", true, false, false),
			new MBeanAttributeInfo("ImplementationName", "java.lang.String", "The JMX implementation name " + "(the name of this product)", true, false, false),
			new MBeanAttributeInfo("ImplementationVersion", "java.lang.String", "The JMX implementation version " + "(the version of this product).", true, false, false),
			new MBeanAttributeInfo("ImplementationVendor", "java.lang.String", "the JMX implementation vendor " + "(the vendor of this product).", true, false, false) };

	public MBeanServerDelegate() {
		super();
		delegateInfo = new MBeanInfo("jx.management.MbeanServerDelegate", "Represents the MBean server from the management " + "point of view.", MBeanServerDelegate.attributeInfos, null, null);
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
	public MBeanInfo getMBeanInfo() {
		return delegateInfo;
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
