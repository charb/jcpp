package jcpp.jmx.interceptor;

import jcpp.jmx.mbeanserver.DynamicMBean2;
import jcpp.jmx.mbeanserver.Introspector;
import jcpp.jmx.mbeanserver.Repository;
import jcpp.management.Attribute;
import jcpp.management.DynamicMBean;
import jcpp.management.MBeanRegistration;
import jcpp.management.MBeanServer;
import jcpp.management.ObjectInstance;
import jcpp.management.ObjectName;

public class DefaultMBeanServerInterceptor implements MBeanServerInterceptor {


	private transient MBeanServer server = null;



	private final transient Repository repository;

	public DefaultMBeanServerInterceptor(MBeanServer outer,  Repository repository) {
		if (outer == null)
			throw new IllegalArgumentException("outer MBeanServer cannot be null");

		if (repository == null)
			throw new IllegalArgumentException("Repository cannot be null");

		this.server = outer;
		this.repository = repository;

	}

	@Override
	public ObjectInstance registerMBean(Object object, ObjectName name) throws Exception {
		
		Class theClass = object.getClass();

		Introspector.checkCompliance(theClass);

		final String infoClassName = getNewMBeanClassName(object);

		return registerObject(infoClassName, object, name);
	}

	private ObjectInstance registerObject(String classname, Object object, ObjectName name) throws Exception {

		if (object == null) {
			throw new Exception("Exception occurred trying to register the MBean");
		}

		DynamicMBean mbean = Introspector.makeDynamicMBean(object);

		return registerDynamicMBean(classname, mbean, name);
	}

	private ObjectInstance registerDynamicMBean(String classname, DynamicMBean mbean, ObjectName name) throws Exception {

		ObjectName logicalName = name;

		if (mbean instanceof MBeanRegistration) {
			MBeanRegistration reg = (MBeanRegistration) mbean;
			logicalName = preRegisterInvoke(reg, name, server);
			if (mbean instanceof DynamicMBean2) {
				try {
					((DynamicMBean2) mbean).preRegister2(server, logicalName);
				} catch (Exception e) {
					postRegisterInvoke(reg, false, false);
					e.printStackTrace();
				}
			}
		}

		final ObjectInstance result;
		if (logicalName != null) {
			result = new ObjectInstance();
			internal_addObject(mbean, logicalName);
		} else {
			if (mbean instanceof MBeanRegistration)
				postRegisterInvoke((MBeanRegistration) mbean, false, true);

			throw new Exception("Exception occurred trying to register the MBean");
		}

		if (mbean instanceof MBeanRegistration)
			postRegisterInvoke((MBeanRegistration) mbean, true, false);

		
		return result;
	}



	private static String getNewMBeanClassName(Object mbeanToRegister) throws Exception {
		return mbeanToRegister.getClass().getName();
	}

	private static void postRegisterInvoke(MBeanRegistration moi, boolean registrationDone, boolean registerFailed) {

		if (registerFailed && moi instanceof DynamicMBean2)
			((DynamicMBean2) moi).registerFailed();
		try {
			moi.postRegister(new Boolean(registrationDone));
		} catch (RuntimeException e) {
			throw new RuntimeException("RuntimeException thrown in postRegister method");
		} catch (Error er) {
			throw new Error("Error thrown in postRegister method");
		}
	}

	private void internal_addObject(DynamicMBean object, ObjectName logicalName) throws Exception {

		// Let the repository do the work.
		try {
			repository.addMBean(object, logicalName);
		} catch (Exception e) {
			if (object instanceof MBeanRegistration) {
				postRegisterInvoke((MBeanRegistration) object, false, true);
			}
			throw e;
		}

	}

	private static ObjectName preRegisterInvoke(MBeanRegistration moi, ObjectName name, MBeanServer mbs) throws Exception {

		final ObjectName newName;

		try {
			newName = moi.preRegister(mbs, name);
		} catch (RuntimeException e) {
			throw new RuntimeException("RuntimeException thrown in preRegister method");
		} catch (Error er) {
			throw new RuntimeException("Error thrown in preRegister method");
		} catch (Exception ex) {
			throw new RuntimeException("Exception thrown in preRegister method");
		}

		if (newName != null)
			return newName;
		else
			return name;
	}

	@Override
	public Object invoke(ObjectName name, String operationName, Object[] params, String[] signature) throws Exception {

		DynamicMBean instance = getMBean(name);
		return instance.invoke(operationName, params, signature);
	}

	DynamicMBean getMBean(ObjectName name) throws Exception {
		if (name == null) {
			throw new Exception("Object name cannot be null, Exception occured trying to et an MBean");
		}
		DynamicMBean obj = null;
		obj = repository.retrieve(name);
		if (obj == null) {
			throw new Exception(name.toString());
		}
		return obj;
	}

	@Override
	public Object getAttribute(ObjectName name, String attribute) throws Exception {

		if (name == null) {
			throw new Exception("Exception occurred trying to invoke the getter on the MBean");
		}
		if (attribute == null) {
			throw new Exception("Exception occurred trying to invoke the getter on the MBean");
		}

		final DynamicMBean instance = getMBean(name);

		try {
			return instance.getAttribute(attribute);
		} catch (Exception e) {
			throw e;
		} catch (Throwable t) {
			throw new AssertionError();
		}
	}

	@Override
	public void setAttribute(ObjectName name, Attribute attribute) throws Exception {
		if (name == null) {
			throw new Exception("Exception occurred trying to invoke the setter on the MBean");
		}

		if (attribute == null) {
			throw new Exception("Exception occurred trying to invoke the setter on the MBean");
		}

		
		DynamicMBean instance = getMBean(name);

		try {
			instance.setAttribute(attribute);
		} catch (Exception t) {
			throw new AssertionError();
		}

	}

}
