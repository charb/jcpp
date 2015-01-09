package jcpp.lang;

import jcpp.*;
import java.io.*;
import org.junit.*;

public class ReflectiveOperationExceptionTest extends AbstractTest{
	private static ObjectOutputStream os;

	public ReflectiveOperationExceptionTest(){
	}

	@BeforeClass
	public static void setUp() throws Exception{
		File file=createOutputFile(ReflectiveOperationExceptionTest.class);
		os=new ObjectOutputStream(new FileOutputStream(file));
	}

	@AfterClass
	public static void tearDown() throws Exception{
		os.close();
	}

	@Test
	public void testWrite() throws Exception{
		ReflectiveOperationException cause=new ReflectiveOperationException("This is the cause");
		ReflectiveOperationException exception=new ReflectiveOperationException("The exception to test");
		exception.initCause(cause);
		os.writeObject(exception);	
	}
}