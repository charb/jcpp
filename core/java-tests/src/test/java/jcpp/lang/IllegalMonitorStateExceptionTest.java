package jcpp.lang;

import jcpp.*;
import java.io.*;
import org.junit.*;

public class IllegalMonitorStateExceptionTest extends AbstractTest{
	private static ObjectOutputStream os;

	public IllegalMonitorStateExceptionTest(){
	}

	@BeforeClass
	public static void setUp() throws Exception{
		File file=createOutputFile(IllegalMonitorStateExceptionTest.class);
		os=new ObjectOutputStream(new FileOutputStream(file));
	}

	@AfterClass
	public static void tearDown() throws Exception{
		os.close();
	}

	@Test
	public void testWrite() throws Exception{
		IllegalMonitorStateException cause=new IllegalMonitorStateException("This is the cause");
		IllegalMonitorStateException exception=new IllegalMonitorStateException("The exception to test");
		exception.initCause(cause);
		os.writeObject(exception);	
	}
}