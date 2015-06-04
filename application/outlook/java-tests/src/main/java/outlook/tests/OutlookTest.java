package outlook.tests;

import java.io.EOFException;
import java.net.InetAddress;
import java.util.ArrayList;
import java.util.List;

import jcpp.rmi.server.connection.Server;
import jcpp.rmi.server.transport.EndPoint;
import outlook.client.IOutlook;
import outlook.client.IOutlookServer;
import outlook.client.MailMessage;


public class OutlookTest {

	//@BeforeClass
	public static void setUp() throws Exception{
	}

	//@AfterClass
	public static void tearDown() throws Exception{
	}

	//@Test
	public void test() throws Exception{
		//main(null);
		List<String> args = new ArrayList<String>();
		args.add("-b");
		args.add("El 3awafi");
		args.add("-d");
		args.add( "walid@lello.com");
		args.add("moustafa@dahrouge.com");
		args.add( "-s");
		args.add("El mas2ala");
		//maincmd((String[]) args.toArray());
	}

 	public static void maincc(String[] argv) throws Exception {
 		System.setProperty("org.apache.commons.logging.Log", "org.apache.commons.logging.impl.SimpleLog");
		System.setProperty("org.apache.commons.logging.simplelog.showdatetime", "true");
		System.setProperty("org.apache.commons.logging.simplelog.defaultlog", "debug");
 		EndPoint endPoint = new EndPoint(InetAddress.getLocalHost().getHostName(), 9875, "site1");
 		Server server = Server.create(endPoint);

 		EndPoint serverEndPoint = new EndPoint(InetAddress.getLocalHost().getHostName(), 9800, "site1");
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
 	
 	
 	
 	private enum MODE {BCC, CC, BODY, SUBJECT, RECIPIENT, TEMP_FOLDER, NONE};
 	//-c cc list
 	//-d recipient list
 	//-b body
 	//-s subject
 	//-bc bcc list
 	//-t temp folder
 	public static void main(String[] argv) throws Exception {
 		System.setProperty("org.apache.commons.logging.Log", "org.apache.commons.logging.impl.SimpleLog");
		System.setProperty("org.apache.commons.logging.simplelog.showdatetime", "true");
		System.setProperty("org.apache.commons.logging.simplelog.defaultlog", "debug");
 		EndPoint endPoint = new EndPoint(InetAddress.getLocalHost().getHostName(), 9875, "site1");
 		Server server = Server.create(endPoint);

 		EndPoint serverEndPoint = new EndPoint(InetAddress.getLocalHost().getHostName(), 9800, "site1");
// 		IOutlook outlook = server.lookup(serverEndPoint, IOutlook.class);
 		IOutlookServer outlookServer = server.lookup(serverEndPoint, IOutlookServer.class);
 		
 		

 		MailMessage mail = new MailMessage();
 		
 		MODE mode = MODE.NONE;
 		for (String arg : argv){
 			
 			if (arg.equals("-c")){
 				mode = MODE.CC;
 			}
 			else if (arg.equals("-d")){
 				mode = MODE.RECIPIENT;
 			}
 			else if (arg.equals("-b")){
 				mode = MODE.BODY;
 			}
 			else if (arg.equals("-s")){
 				mode = MODE.SUBJECT;
 			}
 			else if (arg.equals("-bc")){
 				mode = MODE.BCC;
 			}
 			else if (arg.equals("-t")){
 				mode = MODE.TEMP_FOLDER;
 			}
 			else {
 				switch (mode){
 				case CC:
 					mail.getCcList().add(arg);
 					break;
 				case BCC:
 					mail.getBccList().add(arg);
 					break;
 				case NONE:
 					break;
 				case BODY:
 					mail.setBody(arg);
 					mode = MODE.NONE;
 					break;
 				case SUBJECT:
 					mail.setSubject(arg);
 					mode = MODE.NONE;
 					break;
 				case RECIPIENT:
 					mail.getToList().add(arg);
 					break;
 				}
 			}
 			
 		}
 		
 		System.out.println("invoking openMail");
 		
// 		outlook.openMailMessageInOutlook(mail);
 		
 		outlookServer.setTempFolder("outlookTempDir");
 		
 		outlookServer.openMailMessageInOutlook(mail);
 		
 		try {
 			outlookServer.shutdown();
 		} catch(Exception e){
 			if (!(e.getCause() instanceof EOFException)) {
 				throw e;
 			} 			
 		} 		
 		
 		server.unexport();
    } 
}
