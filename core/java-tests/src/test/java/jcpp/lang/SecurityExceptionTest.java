package jcpp.lang;

import jcpp.*;
import java.io.*;
import org.junit.*;

public class SecurityExceptionTest extends AbstractTest{
	private static ObjectOutputStream os;

	public SecurityExceptionTest(){
	}

	@BeforeClass
	public static void setUp() throws Exception{
		File file=createOutputFile(SecurityExceptionTest.class);
		os=new ObjectOutputStream(new FileOutputStream(file));
	}

	@AfterClass
	public static void tearDown() throws Exception{
		os.close();
	}

	@Test
	public void testWrite() throws Exception{
		SecurityException cause=new SecurityException("This is the cause");
		SecurityException exception=new SecurityException("The exception to test");
		exception.initCause(cause);
		os.writeObject(exception);	
	}
}