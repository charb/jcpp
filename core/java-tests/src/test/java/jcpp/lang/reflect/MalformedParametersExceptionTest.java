package jcpp.lang.reflect;

import jcpp.*;
import java.io.*;
import java.lang.reflect.*;
import org.junit.*;

public class MalformedParametersExceptionTest extends AbstractTest{
	private static ObjectOutputStream os;

	public MalformedParametersExceptionTest(){
	}

	@BeforeClass
	public static void setUp() throws Exception{
		File file=createOutputFile(MalformedParametersExceptionTest.class);
		os=new ObjectOutputStream(new FileOutputStream(file));
	}

	@AfterClass
	public static void tearDown() throws Exception{
		os.close();
	}

	@Test
	public void testWrite() throws Exception{
			//TODO reactivate when on java8
/*		MalformedParametersException cause=new MalformedParametersException("This is the cause");
		MalformedParametersException exception=new MalformedParametersException("The exception to test");
		exception.initCause(cause);
		os.writeObject(exception);	
		*/
	}
}