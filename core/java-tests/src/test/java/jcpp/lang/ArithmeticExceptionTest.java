package jcpp.lang;

import jcpp.*;
import java.io.*;
import org.junit.*;

public class ArithmeticExceptionTest extends AbstractTest{
	private static ObjectOutputStream os;

	public ArithmeticExceptionTest(){
	}

	@BeforeClass
	public static void setUp() throws Exception{
		File file=createOutputFile(ArithmeticExceptionTest.class);
		os=new ObjectOutputStream(new FileOutputStream(file));
	}

	@AfterClass
	public static void tearDown() throws Exception{
		os.close();
	}

	@Test
	public void testWrite() throws Exception{
		ArithmeticException cause=new ArithmeticException("This is the cause");
		ArithmeticException exception=new ArithmeticException("The exception to test");
		exception.initCause(cause);
		os.writeObject(exception);	
	}
}