package jcpp.jmx.mbeanserver;



import jcpp.jmx.interceptor.DefaultMBeanServerInterceptor;
import jcpp.jmx.interceptor.MBeanServerInterceptor;
import jcpp.management.Attribute;
import jcpp.management.MBeanServer;
import jcpp.management.ObjectInstance;
import jcpp.management.ObjectName;

public class JmxMBeanServer implements MBeanServer {

	public static final boolean DEFAULT_FAIR_LOCK_POLICY = true;


	private transient MBeanServerInterceptor mbsInterceptor = null;


	JmxMBeanServer(String domain, MBeanServer outer) {
		this(domain, outer, true);
	}


	JmxMBeanServer(String domain, MBeanServer outer,  boolean fairLock) {

		if (outer == null)
			outer = this;
		
		final Repository repository = new Repository(domain, fairLock);
		this.mbsInterceptor = new DefaultMBeanServerInterceptor(outer, repository);
		
	}


	public static MBeanServer newMBeanServer(String defaultDomain, MBeanServer outer) {

		final boolean fairLock = DEFAULT_FAIR_LOCK_POLICY;

		return new JmxMBeanServer(defaultDomain, outer, fairLock);
	}


	private ObjectName cloneObjectName(ObjectName name) {
		if (name != null) {
			return ObjectName.getInstance(name);
		}
		return name;
	}

	private Attribute cloneAttribute(Attribute attribute) {
		if (attribute != null) {
			if (!attribute.getClass().equals(Attribute.class)) {
				return new Attribute(attribute.getName(), attribute.getValue());
			}
		}
		return attribute;
	}

	@Override
	public ObjectInstance registerMBean(Object object, String name) throws Exception {
		jcpp.management.ObjectName objName = new jcpp.management.ObjectName(name);
		return mbsInterceptor.registerMBean(object, cloneObjectName(objName));
	}

	@Override
	public Object invoke(String name, String operationName, Object[] params, String[] signature) throws Exception {
		jcpp.management.ObjectName objName = new jcpp.management.ObjectName(name);
		return mbsInterceptor.invoke(cloneObjectName(objName), operationName, params, signature);
	}

	@Override
	public Object getAttribute(String name, String attribute) throws Exception {
		jcpp.management.ObjectName objName = new jcpp.management.ObjectName(name);
		return mbsInterceptor.getAttribute(cloneObjectName(objName), attribute);
	}

	@Override
	public void setAttribute(String name, Attribute attribute) throws Exception {
		jcpp.management.ObjectName objName = new jcpp.management.ObjectName(name);
		mbsInterceptor.setAttribute(cloneObjectName(objName), cloneAttribute(attribute));
	}

	
}
