package jcpp.lang;

import jcpp.*;
import java.io.*;
import org.junit.*;

public class IllegalArgumentExceptionTest extends AbstractTest{
	private static ObjectOutputStream os;

	public IllegalArgumentExceptionTest(){
	}

	@BeforeClass
	public static void setUp() throws Exception{
		File file=createOutputFile(IllegalArgumentExceptionTest.class);
		os=new ObjectOutputStream(new FileOutputStream(file));
	}

	@AfterClass
	public static void tearDown() throws Exception{
		os.close();
	}

	@Test
	public void testWrite() throws Exception{
		IllegalArgumentException cause=new IllegalArgumentException("This is the cause");
		IllegalArgumentException exception=new IllegalArgumentException("The exception to test");
		exception.initCause(cause);
		os.writeObject(exception);	
	}
}