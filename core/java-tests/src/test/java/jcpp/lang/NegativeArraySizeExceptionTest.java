package jcpp.lang;

import jcpp.*;
import java.io.*;
import org.junit.*;

public class NegativeArraySizeExceptionTest extends AbstractTest{
	private static ObjectOutputStream os;

	public NegativeArraySizeExceptionTest(){
	}

	@BeforeClass
	public static void setUp() throws Exception{
		File file=createOutputFile(NegativeArraySizeExceptionTest.class);
		os=new ObjectOutputStream(new FileOutputStream(file));
	}

	@AfterClass
	public static void tearDown() throws Exception{
		os.close();
	}

	@Test
	public void testWrite() throws Exception{
		NegativeArraySizeException cause=new NegativeArraySizeException("This is the cause");
		NegativeArraySizeException exception=new NegativeArraySizeException("The exception to test");
		exception.initCause(cause);
		os.writeObject(exception);	
	}
}