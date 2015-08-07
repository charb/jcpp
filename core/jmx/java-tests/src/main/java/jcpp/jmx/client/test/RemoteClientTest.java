package jcpp.jmx.client.test;

import java.net.InetAddress;

import jcpp.management.Attribute;
import jcpp.management.MBeanServer;
//import jcpp.management.ObjectName;
import jcpp.rmi.server.connection.Server;
import jcpp.rmi.server.transport.EndPoint;

public class RemoteClientTest {
	
	public static void main(String[] argv) throws Exception {
		
		System.setProperty("org.apache.commons.logging.Log", "org.apache.commons.logging.impl.SimpleLog");
		System.setProperty("org.apache.commons.logging.simplelog.showdatetime", "true");
		System.setProperty("org.apache.commons.logging.simplelog.defaultlog", "debug");
		
		
 		EndPoint endPoint = new EndPoint(InetAddress.getLocalHost().getHostName(), 9875, "site1");
 		Server server = Server.create(endPoint);

 		EndPoint serverEndPoint = new EndPoint(InetAddress.getLocalHost().getHostName(), 9800, "site1");
 		MBeanServer mbs = (MBeanServer)server.lookup(serverEndPoint, MBeanServer.class);

 		
 		String mbeanName = "jcpp.lang.jmx.tests:type=Hello";
 		
 		mbs.invoke(mbeanName, "sayHello", null, null);
 		
 		
 		
 		Attribute cacheSizeAttribute = new Attribute("CacheSize", 234);
		mbs.setAttribute(mbeanName, cacheSizeAttribute);
		
		
		String helloName = (String) mbs.getAttribute(mbeanName, "Name");
		System.out.println(helloName);
		
		
		Integer[] params = {new Integer(1), new Integer(2) };
		String[] sig = { Integer.class.getName(), Integer.class.getName() };
		
		int x = (Integer) mbs.invoke(mbeanName, "add", params, sig);
		System.out.println(x);
		
	
 		
 		server.unexport();
    }
	
}
