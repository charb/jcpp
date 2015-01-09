package jcpp.io;

import jcpp.*;
import java.io.*;
import org.junit.*;

public class NotSerializableExceptionTest extends AbstractTest{
	private static ObjectOutputStream os;

	public NotSerializableExceptionTest(){
	}

	@BeforeClass
	public static void setUp() throws Exception{
		File file=createOutputFile(NotSerializableExceptionTest.class);
		os=new ObjectOutputStream(new FileOutputStream(file));
	}

	@AfterClass
	public static void tearDown() throws Exception{
		os.close();
	}

	@Test
	public void testWrite() throws Exception{
		NotSerializableException cause=new NotSerializableException("This is the cause");
		NotSerializableException exception=new NotSerializableException("The exception to test");
		exception.initCause(cause);
		os.writeObject(exception);	
	}
}