package jcpp.io;

import jcpp.*;
import java.io.*;
import org.junit.*;

public class IOExceptionTest extends AbstractTest{
	private static ObjectOutputStream os;

	public IOExceptionTest(){
	}

	@BeforeClass
	public static void setUp() throws Exception{
		File file=createOutputFile(IOExceptionTest.class);
		os=new ObjectOutputStream(new FileOutputStream(file));
	}

	@AfterClass
	public static void tearDown() throws Exception{
		os.close();
	}

	@Test
	public void testWrite() throws Exception{
		IOException cause=new IOException("This is the cause");
		IOException exception=new IOException("The exception to test");
		exception.initCause(cause);
		os.writeObject(exception);	
	}
}