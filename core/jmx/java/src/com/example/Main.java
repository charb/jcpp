package com.example;



import jcpp.management.Attribute;
import jcpp.management.MBeanServer;
import jcpp.management.MBeanServerFactory;
import jcpp.management.ObjectName;


public class Main {

	public static void main(String[] args) throws Exception {

		MBeanServer mbs = MBeanServerFactory.createMBeanServer();

		ObjectName mbeanName = new ObjectName("com.example:type=Hello");

		System.out.println(mbeanName.getDomain());
		
		Hello mbean = new Hello();

		mbs.registerMBean(mbean, mbeanName);

		
		
		
//		


		Attribute cacheSizeAttribute = new Attribute("CacheSize", 234);
		mbs.setAttribute(mbeanName, cacheSizeAttribute);

		
		ObjectName mbeanName2 = new ObjectName("com.example:type=CopyOfHello");

		CopyOfHello mbean2 = new CopyOfHello();

		mbs.registerMBean(mbean2, mbeanName2);
		
		
		

		ObjectName mbeanName3 = new ObjectName("com.example2:type=Hello");

		com.example2.Hell mbean3 = new com.example2.Hell();

		mbs.registerMBean(mbean3, mbeanName3);

		

		
		
		String helloName = (String) mbs.getAttribute(mbeanName, "Name");
		System.out.println(helloName);
		
		mbs.setAttribute(mbeanName2, cacheSizeAttribute);
		mbs.invoke(mbeanName2, "say", null, null);
		
		
		Integer[] params = { 1, 2 };
		String[] sig = { int.class.getName(), int.class.getName() };
		
		int x = (Integer) mbs.invoke(mbeanName, "add", params, sig);
		System.out.println(x);
		
		
		
		com.example2.Hell hell = new com.example2.Hell();
		ObjectName hellname = new ObjectName("com.example2:type=Hell");
		mbs.registerMBean(hell, hellname);
		
		mbs.invoke(hellname, "sayHello", null, null);
	}

}
