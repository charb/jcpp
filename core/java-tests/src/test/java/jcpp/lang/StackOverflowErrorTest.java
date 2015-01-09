package jcpp.lang;

import jcpp.*;
import java.io.*;
import org.junit.*;

public class StackOverflowErrorTest extends AbstractTest{
	private static ObjectOutputStream os;

	public StackOverflowErrorTest(){
	}

	@BeforeClass
	public static void setUp() throws Exception{
		File file=createOutputFile(StackOverflowErrorTest.class);
		os=new ObjectOutputStream(new FileOutputStream(file));
	}

	@AfterClass
	public static void tearDown() throws Exception{
		os.close();
	}

	@Test
	public void testWrite() throws Exception{
		StackOverflowError cause=new StackOverflowError("This is the cause");
		StackOverflowError exception=new StackOverflowError("The exception to test");
		exception.initCause(cause);
		os.writeObject(exception);	
	}
}