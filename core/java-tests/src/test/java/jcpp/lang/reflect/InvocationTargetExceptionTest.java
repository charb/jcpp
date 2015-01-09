package jcpp.lang.reflect;

import jcpp.*;
import java.io.*;
import java.lang.reflect.*;
import org.junit.*;

public class InvocationTargetExceptionTest extends AbstractTest{
	private static ObjectOutputStream os;

	public InvocationTargetExceptionTest(){
	}

	@BeforeClass
	public static void setUp() throws Exception{
		File file=createOutputFile(InvocationTargetExceptionTest.class);
		os=new ObjectOutputStream(new FileOutputStream(file));
	}

	@AfterClass
	public static void tearDown() throws Exception{
		os.close();
	}

	@Test
	public void testWrite() throws Exception{
		InvocationTargetException cause=new InvocationTargetException(null,"This is the cause");
		InvocationTargetException exception=new InvocationTargetException(cause,"The exception to test");
		os.writeObject(exception);	
	}
}