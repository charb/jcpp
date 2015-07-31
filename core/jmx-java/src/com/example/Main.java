package com.example;

import java.util.LinkedList;
import java.util.Queue;

import jcpp.management.Attribute;
import jcpp.management.MBeanServer;
import jcpp.management.MBeanServerFactory;
import jcpp.management.ObjectName;

public class Main {

	public static void main(String[] args) throws Exception {

		MBeanServer mbs = MBeanServerFactory.createMBeanServer();

		ObjectName mbeanName = new ObjectName("com.example:type=Hello");

		Hello mbean = new Hello();

		mbs.registerMBean(mbean, mbeanName);

		ObjectName mbeanName2 = new ObjectName("com.example:type=CopyOfHello");

		CopyOfHello mbean2 = new CopyOfHello();

		mbs.registerMBean(mbean2, mbeanName2);

		ObjectName mbeanName3 = new ObjectName("com.example2:type=Hello");

		com.example2.Hell mbean3 = new com.example2.Hell();

		mbs.registerMBean(mbean3, mbeanName3);

		Object obj = mbs.invoke(mbeanName, "sayHello", null, null);

		String helloName = (String) mbs.getAttribute(mbeanName, "Name");
		System.out.println(helloName);

		Attribute cacheSizeAttribute = new Attribute("CacheSize", 234);
		mbs.setAttribute(mbeanName, cacheSizeAttribute);

		mbs.setAttribute(mbeanName2, cacheSizeAttribute);
		mbs.invoke(mbeanName2, "say", null, null);
		
		
		Integer[] params = { 1, 2 };
		String[] sig = { int.class.getName(), int.class.getName() };
		
		int x = (Integer) mbs.invoke(mbeanName, "add", params, sig);
		System.out.println(x);
		
		Queue<String> q = new LinkedList<>();
		
		
	}

}
