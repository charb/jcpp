package jcpp.lang;

import jcpp.*;
import java.io.*;
import org.junit.*;

public class UnsupportedOperationExceptionTest extends AbstractTest{
	private static ObjectOutputStream os;

	public UnsupportedOperationExceptionTest(){
	}

	@BeforeClass
	public static void setUp() throws Exception{
		File file=createOutputFile(UnsupportedOperationExceptionTest.class);
		os=new ObjectOutputStream(new FileOutputStream(file));
	}

	@AfterClass
	public static void tearDown() throws Exception{
		os.close();
	}

	@Test
	public void testWrite() throws Exception{
		UnsupportedOperationException cause=new UnsupportedOperationException("This is the cause");
		UnsupportedOperationException exception=new UnsupportedOperationException("The exception to test");
		exception.initCause(cause);
		os.writeObject(exception);	
	}
}