package jcpp.lang;

import jcpp.*;
import java.io.*;
import org.junit.*;

public class IllegalThreadStateExceptionTest extends AbstractTest{
	private static ObjectOutputStream os;

	public IllegalThreadStateExceptionTest(){
	}

	@BeforeClass
	public static void setUp() throws Exception{
		File file=createOutputFile(IllegalThreadStateExceptionTest.class);
		os=new ObjectOutputStream(new FileOutputStream(file));
	}

	@AfterClass
	public static void tearDown() throws Exception{
		os.close();
	}

	@Test
	public void testWrite() throws Exception{
		IllegalThreadStateException cause=new IllegalThreadStateException("This is the cause");
		IllegalThreadStateException exception=new IllegalThreadStateException("The exception to test");
		exception.initCause(cause);
		os.writeObject(exception);	
	}
}