package jcpp.lang;

import jcpp.*;
import java.io.*;
import org.junit.*;

public class AssertionErrorTest extends AbstractTest{
	private static ObjectOutputStream os;

	public AssertionErrorTest(){
	}

	@BeforeClass
	public static void setUp() throws Exception{
		File file=createOutputFile(AssertionErrorTest.class);
		os=new ObjectOutputStream(new FileOutputStream(file));
	}

	@AfterClass
	public static void tearDown() throws Exception{
		os.close();
	}

	@Test
	public void testWrite() throws Exception{
		AssertionError cause=new AssertionError("This is the cause");
		AssertionError exception=new AssertionError("The exception to test",cause);
		os.writeObject(exception);	
	}
}