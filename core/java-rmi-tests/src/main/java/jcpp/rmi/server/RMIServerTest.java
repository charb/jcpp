package jcpp.rmi.server;

import jcpp.rmi.server.connection.*;
import jcpp.rmi.server.transport.*;
import jcpp.rmi.server.gateway.*;
import jcpp.*;
import java.net.*;
import java.io.*;
import java.util.*;
import org.junit.*;

public class RMIServerTest{

	//@BeforeClass
	public static void setUp() throws Exception{
	}

	//@AfterClass
	public static void tearDown() throws Exception{
	}

	//@Test
	public void test() throws Exception{
		main(null);
	}

 	public static void main(String[] argv) throws Exception{
 		System.setProperty("org.apache.commons.logging.Log", "org.apache.commons.logging.impl.SimpleLog");
		System.setProperty("org.apache.commons.logging.simplelog.showdatetime", "true");
		System.setProperty("org.apache.commons.logging.simplelog.log.jcpp", "debug");
		System.setProperty("org.apache.commons.logging.simplelog.defaultlog", "debug");
 		EndPoint endPoint=new EndPoint(InetAddress.getLocalHost().getHostName(),9876,"site1");
 		Server server=Server.create(endPoint);
 		RemoteSample rs=new RemoteSample();
 		List l=new ArrayList();
 		l.add(IRemoteSample.class);
 		server.getRegistry().bind(IRemoteSample.class.getName(),rs,l);
    } 
}