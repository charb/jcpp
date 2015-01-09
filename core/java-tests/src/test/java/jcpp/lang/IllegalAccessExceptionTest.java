package jcpp.lang;

import jcpp.*;
import java.io.*;
import org.junit.*;

public class IllegalAccessExceptionTest extends AbstractTest{
	private static ObjectOutputStream os;

	public IllegalAccessExceptionTest(){
	}

	@BeforeClass
	public static void setUp() throws Exception{
		File file=createOutputFile(IllegalAccessExceptionTest.class);
		os=new ObjectOutputStream(new FileOutputStream(file));
	}

	@AfterClass
	public static void tearDown() throws Exception{
		os.close();
	}

	@Test
	public void testWrite() throws Exception{
		IllegalAccessException cause=new IllegalAccessException("This is the cause");
		IllegalAccessException exception=new IllegalAccessException("The exception to test");
		exception.initCause(cause);
		os.writeObject(exception);	
	}
}