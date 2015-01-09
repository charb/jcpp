package jcpp.lang;

import jcpp.*;
import java.io.*;
import org.junit.*;

public class InterruptedExceptionTest extends AbstractTest{
	private static ObjectOutputStream os;

	public InterruptedExceptionTest(){
	}

	@BeforeClass
	public static void setUp() throws Exception{
		File file=createOutputFile(InterruptedExceptionTest.class);
		os=new ObjectOutputStream(new FileOutputStream(file));
	}

	@AfterClass
	public static void tearDown() throws Exception{
		os.close();
	}

	@Test
	public void testWrite() throws Exception{
		InterruptedException cause=new InterruptedException("This is the cause");
		InterruptedException exception=new InterruptedException("The exception to test");
		exception.initCause(cause);
		os.writeObject(exception);	
	}
}