package jcpp.jmx.mbeanserver;

import jcpp.management.DynamicMBean;


public class Introspector {

	public static void checkCompliance(Class mbeanClass) throws Exception {
		// Is DynamicMBean?
		//
		if (DynamicMBean.class.isAssignableFrom(mbeanClass))
			return;
		try {
			getStandardMBeanInterface(mbeanClass);
			return;
		} catch (Exception e) {
		}
	}

	public static DynamicMBean makeDynamicMBean(Object mbean) throws Exception {
		if (mbean instanceof DynamicMBean)
			return (DynamicMBean) mbean;
		final Class mbeanClass = mbean.getClass();
		Class<?> c = null;
		try {
			c = getStandardMBeanInterface(mbeanClass);
		} catch (Exception e) {
			// Ignore exception - we need to check whether
			// mbean is an MXBean first.
		}
		if (c != null)
			return new StandardMBeanSupport(mbean, Util.<Class<Object>> cast(c));

		checkCompliance(mbeanClass);
		throw new Exception("Not compliant"); // not reached
	}

	public static Class getStandardMBeanInterface(Class baseClass) throws Exception {
		Class current = baseClass;
		Class mbeanInterface = null;
		while (current != null) {
			mbeanInterface = findMBeanInterface(current, current.getName());
			if (mbeanInterface != null)
				break;
			current = current.getSuperclass();
		}
		if (mbeanInterface != null) {
			return mbeanInterface;
		} else {
			final String msg = "Class " + baseClass.getName() + " is not a JMX compliant Standard MBean";
			throw new Exception(msg);
		}
	}


	private static Class findMBeanInterface(Class aClass, String aName) {
		Class current = aClass;
		while (current != null) {
			final Class[] interfaces = current.getInterfaces();
			final int len = interfaces.length;
			for (int i = 0; i < len; i++) {
				final Class inter = implementsMBean(interfaces[i], aName);
				if (inter != null)
					return inter;
			}
			current = current.getSuperclass();
		}
		return null;
	}

	private static Class implementsMBean(Class c, String clName) {
		String clMBeanName = clName + "MBean";
		if (c.getName().equals(clMBeanName)) {
			return c;
		}
		Class[] interfaces = c.getInterfaces();
		for (int i = 0; i < interfaces.length; i++) {
			if (interfaces[i].getName().equals(clMBeanName))
				return interfaces[i];
		}

		return null;
	}

	static Exception throwException(Class<?> notCompliant, Throwable cause) throws Exception {

		throw new Exception("TODO");
	}

}
