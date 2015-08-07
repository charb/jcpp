package jcpp.management;

public interface MBeanRegistration {
	
	
	public void postRegister(Boolean registrationDone);
	
	public ObjectName preRegister(MBeanServer server, ObjectName name) throws Exception;
	
}
