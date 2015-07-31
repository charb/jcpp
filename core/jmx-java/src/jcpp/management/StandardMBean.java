package jcpp.management;

import jcpp.jmx.mbeanserver.Introspector;
import jcpp.jmx.mbeanserver.MBeanSupport;
import jcpp.jmx.mbeanserver.StandardMBeanSupport;
import jcpp.jmx.mbeanserver.Util;

public class StandardMBean implements DynamicMBean, MBeanRegistration {

	private volatile MBeanSupport<?> mbean;

	public <T> StandardMBean(T implementation, Class<T> mbeanInterface) {
		try {
			construct(implementation, mbeanInterface, false);
		} catch (Exception e) {
			throw new IllegalArgumentException(e);
		}
	}

	private <T> void construct(T implementation, Class<T> mbeanInterface, boolean nullImplementationAllowed) throws Exception {
		if (implementation == null) {
			// Have to use (T)this rather than mbeanInterface.cast(this)
			// because mbeanInterface might be null.
			if (nullImplementationAllowed)
				implementation = Util.<T> cast(this);
			else
				throw new IllegalArgumentException("implementation is null");
		}

		if (mbeanInterface == null) {
			mbeanInterface = Util.cast(Introspector.getStandardMBeanInterface(implementation.getClass()));
		}
		this.mbean = new StandardMBeanSupport(implementation, mbeanInterface);

	}

	@Override
	public void postRegister(Boolean registrationDone) {
		mbean.unregister();
	}

	@Override
	public ObjectName preRegister(MBeanServer server, ObjectName name) throws Exception {
		mbean.register(server, name);
		return name;
	}

	@Override
	public Object invoke(String actionName, Object[] params, String[] signature) throws Exception {
		return mbean.invoke(actionName, params, signature);
	}

	@Override
	public MBeanInfo getMBeanInfo() {
		// TODO Auto-generated method stub
		System.out.println("6 implement me " + this.getClass().getName());
		return null;
	}

	@Override
	public Object getAttribute(String attribute) throws Exception {
		// TODO Auto-generated method stub
		System.out.println("7 implement me " + this.getClass().getName());
		return null;
	}

	@Override
	public void setAttribute(Attribute attribute) throws Exception {
		// TODO Auto-generated method stub
		System.out.println("8 implement me " + this.getClass().getName());
	}

}
