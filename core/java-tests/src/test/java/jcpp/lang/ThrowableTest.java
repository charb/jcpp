package jcpp.lang;

import jcpp.*;
import java.io.*;
import org.junit.*;

public class ThrowableTest extends AbstractTest{
	private static ObjectOutputStream os;

	public ThrowableTest(){
	}

	@BeforeClass
	public static void setUp() throws Exception{
		File file=createOutputFile(ThrowableTest.class);
		os=new ObjectOutputStream(new FileOutputStream(file));
	}

	@AfterClass
	public static void tearDown() throws Exception{
		os.close();
	}

	@Test
	public void testWrite() throws Exception{
		Throwable cause=new Throwable("This is the cause");
		Throwable exception=new Throwable("The exception to test");
		exception.initCause(cause);
		os.writeObject(exception);	
	}
}