package jcpp.lang;

import jcpp.*;
import java.io.*;
import org.junit.*;

public class RuntimeExceptionTest extends AbstractTest{
	private static ObjectOutputStream os;

	public RuntimeExceptionTest(){
	}

	@BeforeClass
	public static void setUp() throws Exception{
		File file=createOutputFile(RuntimeExceptionTest.class);
		os=new ObjectOutputStream(new FileOutputStream(file));
	}

	@AfterClass
	public static void tearDown() throws Exception{
		os.close();
	}

	@Test
	public void testWrite() throws Exception{
		RuntimeException cause=new RuntimeException("This is the cause");
		RuntimeException exception=new RuntimeException("The exception to test");
		exception.initCause(cause);
		os.writeObject(exception);	
	}
}