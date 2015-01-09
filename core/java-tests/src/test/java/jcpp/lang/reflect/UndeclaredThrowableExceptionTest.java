package jcpp.lang.reflect;

import jcpp.*;
import java.io.*;
import java.lang.reflect.*;
import org.junit.*;

public class UndeclaredThrowableExceptionTest extends AbstractTest{
	private static ObjectOutputStream os;

	public UndeclaredThrowableExceptionTest(){
	}

	@BeforeClass
	public static void setUp() throws Exception{
		File file=createOutputFile(UndeclaredThrowableExceptionTest.class);
		os=new ObjectOutputStream(new FileOutputStream(file));
	}

	@AfterClass
	public static void tearDown() throws Exception{
		os.close();
	}

	@Test
	public void testWrite() throws Exception{
		UndeclaredThrowableException cause=new UndeclaredThrowableException(null,"This is the cause");
		UndeclaredThrowableException exception=new UndeclaredThrowableException(cause,"The exception to test");
		os.writeObject(exception);	
	}
}