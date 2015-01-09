package jcpp.lang.reflect;

import jcpp.*;
import java.io.*;
import java.lang.reflect.*;
import org.junit.*;

public class MalformedParameterizedTypeExceptionTest extends AbstractTest{
	private static ObjectOutputStream os;

	public MalformedParameterizedTypeExceptionTest(){
	}

	@BeforeClass
	public static void setUp() throws Exception{
		File file=createOutputFile(MalformedParameterizedTypeExceptionTest.class);
		os=new ObjectOutputStream(new FileOutputStream(file));
	}

	@AfterClass
	public static void tearDown() throws Exception{
		os.close();
	}

	@Test
	public void testWrite() throws Exception{
		MalformedParameterizedTypeException cause=new MalformedParameterizedTypeException();
		MalformedParameterizedTypeException exception=new MalformedParameterizedTypeException();
		exception.initCause(cause);
		os.writeObject(exception);	
	}
}