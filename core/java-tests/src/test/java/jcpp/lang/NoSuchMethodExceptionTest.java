package jcpp.lang;

import jcpp.*;
import java.io.*;
import org.junit.*;

public class NoSuchMethodExceptionTest extends AbstractTest{
	private static ObjectOutputStream os;

	public NoSuchMethodExceptionTest(){
	}

	@BeforeClass
	public static void setUp() throws Exception{
		File file=createOutputFile(NoSuchMethodExceptionTest.class);
		os=new ObjectOutputStream(new FileOutputStream(file));
	}

	@AfterClass
	public static void tearDown() throws Exception{
		os.close();
	}

	@Test
	public void testWrite() throws Exception{
		NoSuchMethodException cause=new NoSuchMethodException("This is the cause");
		NoSuchMethodException exception=new NoSuchMethodException("The exception to test");
		exception.initCause(cause);
		os.writeObject(exception);	
	}
}