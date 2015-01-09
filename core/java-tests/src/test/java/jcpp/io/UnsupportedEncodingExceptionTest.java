package jcpp.io;

import jcpp.*;
import java.io.*;
import org.junit.*;

public class UnsupportedEncodingExceptionTest extends AbstractTest{
	private static ObjectOutputStream os;

	public UnsupportedEncodingExceptionTest(){
	}

	@BeforeClass
	public static void setUp() throws Exception{
		File file=createOutputFile(UnsupportedEncodingExceptionTest.class);
		os=new ObjectOutputStream(new FileOutputStream(file));
	}

	@AfterClass
	public static void tearDown() throws Exception{
		os.close();
	}

	@Test
	public void testWrite() throws Exception{
		UnsupportedEncodingException cause=new UnsupportedEncodingException("This is the cause");
		UnsupportedEncodingException exception=new UnsupportedEncodingException("The exception to test");
		exception.initCause(cause);
		os.writeObject(exception);	
	}
}