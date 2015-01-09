package jcpp.io;

import jcpp.*;
import java.io.*;
import org.junit.*;

public class EOFExceptionTest extends AbstractTest{
	private static ObjectOutputStream os;

	public EOFExceptionTest(){
	}

	@BeforeClass
	public static void setUp() throws Exception{
		File file=createOutputFile(EOFExceptionTest.class);
		os=new ObjectOutputStream(new FileOutputStream(file));
	}

	@AfterClass
	public static void tearDown() throws Exception{
		os.close();
	}

	@Test
	public void testWrite() throws Exception{
		EOFException cause=new EOFException("This is the cause");
		EOFException exception=new EOFException("The exception to test");
		exception.initCause(cause);
		os.writeObject(exception);	
	}
}