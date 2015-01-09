package jcpp.io;

import jcpp.*;
import java.io.*;
import org.junit.*;

public class InvalidClassExceptionTest extends AbstractTest{
	private static ObjectOutputStream os;

	public InvalidClassExceptionTest(){
	}

	@BeforeClass
	public static void setUp() throws Exception{
		File file=createOutputFile(InvalidClassExceptionTest.class);
		os=new ObjectOutputStream(new FileOutputStream(file));
	}

	@AfterClass
	public static void tearDown() throws Exception{
		os.close();
	}

	@Test
	public void testWrite() throws Exception{
		InvalidClassException cause=new InvalidClassException("This is the cause");
		cause.classname="SAMPLE";
		InvalidClassException exception=new InvalidClassException("The exception to test");
		exception.classname="SAMPLE";
		exception.initCause(cause);
		os.writeObject(exception);	
	}
}