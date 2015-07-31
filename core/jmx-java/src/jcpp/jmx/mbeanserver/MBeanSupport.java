package jcpp.jmx.mbeanserver;


import jcpp.management.Attribute;
import jcpp.management.MBeanRegistration;
import jcpp.management.MBeanServer;
import jcpp.management.ObjectName;

public abstract class MBeanSupport<M> implements DynamicMBean2, MBeanRegistration{
	
	private final Object resource;
	
	private final PerInterface<M> perInterface;
	
	
	<T> MBeanSupport(T resource, Class<T> mbeanInterface)
			throws Exception {
		if (mbeanInterface == null)
			throw new Exception("Null MBean interface");
		if (!mbeanInterface.isInstance(resource)) {
			final String msg = "Resource class "
					+ resource.getClass().getName() + " is not an instance of "
					+ mbeanInterface.getName();
			throw new Exception(msg);
		}
		this.resource = resource;
		MBeanIntrospector<M> introspector = getMBeanIntrospector();
		this.perInterface = introspector.getPerInterface(mbeanInterface);
	//	this.mbeanInfo = introspector.getMBeanInfo(resource, perInterface);
	}
	
	abstract MBeanIntrospector<M> getMBeanIntrospector();
	
	abstract Object getCookie();
	
	public abstract void register(MBeanServer mbs, ObjectName name) throws Exception;
	
	public abstract void unregister();
	
	public final Object getResource(){
		return resource;
	}
	
	public final ObjectName preRegister(MBeanServer server, ObjectName name) throws Exception{
		if(resource instanceof MBeanRegistration)
			return ((MBeanRegistration) resource).preRegister(server, name);
		else
			return name;
	}
	
	public final void preRegister2(MBeanServer server, ObjectName name) throws Exception{
		register(server, name);
	}
	
	public final void postRegister(Boolean registrationDone){
		if(resource instanceof MBeanRegistration){
			((MBeanRegistration) resource).postRegister(registrationDone);
		}
	}
	
	public final Object invoke(String operation, Object[] params, String[] signature) throws Exception{
		return perInterface.invoke(resource, operation, params, signature, getCookie());
	}
	
	public final Object getAttribute(String attribute) throws Exception{
		return perInterface.getAttribute(resource, attribute, getCookie());
	}
	
	public final void setAttribute(Attribute attribute) throws Exception{
		final String name = attribute.getName();
		final Object value = attribute.getValue();
		perInterface.setAttribute(resource, name, value, getCookie());
	}
}
