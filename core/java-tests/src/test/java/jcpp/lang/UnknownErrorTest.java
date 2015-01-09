package jcpp.lang;

import jcpp.*;
import java.io.*;
import org.junit.*;

public class UnknownErrorTest extends AbstractTest{
	private static ObjectOutputStream os;

	public UnknownErrorTest(){
	}

	@BeforeClass
	public static void setUp() throws Exception{
		File file=createOutputFile(UnknownErrorTest.class);
		os=new ObjectOutputStream(new FileOutputStream(file));
	}

	@AfterClass
	public static void tearDown() throws Exception{
		os.close();
	}

	@Test
	public void testWrite() throws Exception{
		UnknownError cause=new UnknownError("This is the cause");
		UnknownError exception=new UnknownError("The exception to test");
		exception.initCause(cause);
		os.writeObject(exception);	
	}
}