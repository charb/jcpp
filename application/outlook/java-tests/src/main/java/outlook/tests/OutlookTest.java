package outlook.tests;

import java.net.InetAddress;

import outlook.client.IOutlook;
import outlook.client.MailMessage;
import jcpp.rmi.server.connection.Server;
import jcpp.rmi.server.transport.EndPoint;


public class OutlookTest {

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

 	public static void main(String[] argv) throws Exception {
 		System.setProperty("org.apache.commons.logging.Log", "org.apache.commons.logging.impl.SimpleLog");
		System.setProperty("org.apache.commons.logging.simplelog.showdatetime", "true");
		System.setProperty("org.apache.commons.logging.simplelog.defaultlog", "debug");
 		EndPoint endPoint = new EndPoint(InetAddress.getLocalHost().getHostName(), 9876, "site1");
 		Server server = Server.create(endPoint);

 		EndPoint serverEndPoint = new EndPoint(InetAddress.getLocalHost().getHostName(), 9875, "site1");
 		IOutlook outlook = server.lookup(serverEndPoint, IOutlook.class);
 		
 		
 		for (String s : server.getRegistry().list()) {
 			System.out.println(s);
 		}
 		
 		System.out.println(outlook);
 		
 		MailMessage mail = new MailMessage();
 		
 		mail.getToList().add("loulou@lala.com");
 		mail.setBody("Ya Ahla");
 		
 		System.out.println("invoking openMail");
 		
 		outlook.openMailMessageInOutlook(mail);
    } 
}
