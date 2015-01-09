package jcpp.lang;

import jcpp.*;
import java.io.*;
import org.junit.*;

public class IncompatibleClassChangeErrorTest extends AbstractTest{
	private static ObjectOutputStream os;

	public IncompatibleClassChangeErrorTest(){
	}

	@BeforeClass
	public static void setUp() throws Exception{
		File file=createOutputFile(IncompatibleClassChangeErrorTest.class);
		os=new ObjectOutputStream(new FileOutputStream(file));
	}

	@AfterClass
	public static void tearDown() throws Exception{
		os.close();
	}

	@Test
	public void testWrite() throws Exception{
		IncompatibleClassChangeError cause=new IncompatibleClassChangeError("This is the cause");
		IncompatibleClassChangeError exception=new IncompatibleClassChangeError("The exception to test");
		exception.initCause(cause);
		os.writeObject(exception);	
	}
}