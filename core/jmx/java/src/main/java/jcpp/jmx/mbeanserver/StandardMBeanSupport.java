package jcpp.jmx.mbeanserver;

import java.lang.reflect.Method;

import jcpp.management.MBeanServer;
import jcpp.management.ObjectName;

public class StandardMBeanSupport extends MBeanSupport<Method> {

	public <T> StandardMBeanSupport(T resource, Class<T> mbeanInterface) throws Exception{
		super(resource, mbeanInterface);
	}

	@Override
	MBeanIntrospector<Method> getMBeanIntrospector() {
		return StandardMBeanIntrospector.getInstance();
	}
	

	@Override
	public void registerFailed() {
		// TODO Auto-generated method stub
		System.out.println("1 implement me " + this.getClass().getName());
	}


	@Override
	public void register(MBeanServer mbs, ObjectName name) throws Exception {
		// TODO Auto-generated method stub
		System.out.println("empty " + this.getClass().getName());
	}

	@Override
	public void unregister() {
		// TODO Auto-generated method stub
		System.out.println("6 implement me " + this.getClass().getName());
	}

	

	@Override
	Object getCookie() {
		return null;
	}

	
	
}