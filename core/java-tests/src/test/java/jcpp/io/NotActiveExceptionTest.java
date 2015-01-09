package jcpp.io;

import jcpp.*;
import java.io.*;
import org.junit.*;

public class NotActiveExceptionTest extends AbstractTest{
	private static ObjectOutputStream os;

	public NotActiveExceptionTest(){
	}

	@BeforeClass
	public static void setUp() throws Exception{
		File file=createOutputFile(NotActiveExceptionTest.class);
		os=new ObjectOutputStream(new FileOutputStream(file));
	}

	@AfterClass
	public static void tearDown() throws Exception{
		os.close();
	}

	@Test
	public void testWrite() throws Exception{
		NotActiveException cause=new NotActiveException("This is the cause");
		NotActiveException exception=new NotActiveException("The exception to test");
		exception.initCause(cause);
		os.writeObject(exception);	
	}
}