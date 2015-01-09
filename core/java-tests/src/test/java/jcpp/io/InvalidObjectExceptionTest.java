package jcpp.io;

import jcpp.*;
import java.io.*;
import org.junit.*;

public class InvalidObjectExceptionTest extends AbstractTest{
	private static ObjectOutputStream os;

	public InvalidObjectExceptionTest(){
	}

	@BeforeClass
	public static void setUp() throws Exception{
		File file=createOutputFile(InvalidObjectExceptionTest.class);
		os=new ObjectOutputStream(new FileOutputStream(file));
	}

	@AfterClass
	public static void tearDown() throws Exception{
		os.close();
	}

	@Test
	public void testWrite() throws Exception{
		InvalidObjectException cause=new InvalidObjectException("This is the cause");
		InvalidObjectException exception=new InvalidObjectException("The exception to test");
		exception.initCause(cause);
		os.writeObject(exception);	
	}
}