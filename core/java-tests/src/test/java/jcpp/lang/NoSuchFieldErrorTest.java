package jcpp.lang;

import jcpp.*;
import java.io.*;
import org.junit.*;

public class NoSuchFieldErrorTest extends AbstractTest{
	private static ObjectOutputStream os;

	public NoSuchFieldErrorTest(){
	}

	@BeforeClass
	public static void setUp() throws Exception{
		File file=createOutputFile(NoSuchFieldErrorTest.class);
		os=new ObjectOutputStream(new FileOutputStream(file));
	}

	@AfterClass
	public static void tearDown() throws Exception{
		os.close();
	}

	@Test
	public void testWrite() throws Exception{
		NoSuchFieldError cause=new NoSuchFieldError("This is the cause");
		NoSuchFieldError exception=new NoSuchFieldError("The exception to test");
		exception.initCause(cause);
		os.writeObject(exception);	
	}
}