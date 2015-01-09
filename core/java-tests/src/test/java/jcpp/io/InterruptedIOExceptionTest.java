package jcpp.io;

import jcpp.*;
import java.io.*;
import org.junit.*;

public class InterruptedIOExceptionTest extends AbstractTest{
	private static ObjectOutputStream os;

	public InterruptedIOExceptionTest(){
	}

	@BeforeClass
	public static void setUp() throws Exception{
		File file=createOutputFile(InterruptedIOExceptionTest.class);
		os=new ObjectOutputStream(new FileOutputStream(file));
	}

	@AfterClass
	public static void tearDown() throws Exception{
		os.close();
	}

	@Test
	public void testWrite() throws Exception{
		InterruptedIOException cause=new InterruptedIOException("This is the cause");
		cause.bytesTransferred=78;
		InterruptedIOException exception=new InterruptedIOException("The exception to test");
		exception.bytesTransferred=78;
		exception.initCause(cause);
		os.writeObject(exception);	
	}
}