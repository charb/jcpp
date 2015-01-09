package jcpp.lang;

import jcpp.*;
import java.io.*;
import org.junit.*;

public class IllegalStateExceptionTest extends AbstractTest{
	private static ObjectOutputStream os;

	public IllegalStateExceptionTest(){
	}

	@BeforeClass
	public static void setUp() throws Exception{
		File file=createOutputFile(IllegalStateExceptionTest.class);
		os=new ObjectOutputStream(new FileOutputStream(file));
	}

	@AfterClass
	public static void tearDown() throws Exception{
		os.close();
	}

	@Test
	public void testWrite() throws Exception{
		IllegalStateException cause=new IllegalStateException("This is the cause");
		IllegalStateException exception=new IllegalStateException("The exception to test");
		exception.initCause(cause);
		os.writeObject(exception);	
	}
}