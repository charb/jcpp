package jcpp.lang;

import jcpp.*;
import java.io.*;
import org.junit.*;

public class CloneNotSupportedExceptionTest extends AbstractTest{
	private static ObjectOutputStream os;

	public CloneNotSupportedExceptionTest(){
	}

	@BeforeClass
	public static void setUp() throws Exception{
		File file=createOutputFile(CloneNotSupportedExceptionTest.class);
		os=new ObjectOutputStream(new FileOutputStream(file));
	}

	@AfterClass
	public static void tearDown() throws Exception{
		os.close();
	}

	@Test
	public void testWrite() throws Exception{
		CloneNotSupportedException cause=new CloneNotSupportedException("This is the cause");
		CloneNotSupportedException exception=new CloneNotSupportedException("The exception to test");
		exception.initCause(cause);
		os.writeObject(exception);	
	}
}