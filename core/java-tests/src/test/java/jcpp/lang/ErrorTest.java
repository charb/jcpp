package jcpp.lang;

import jcpp.*;
import java.io.*;
import org.junit.*;

public class ErrorTest extends AbstractTest{
	private static ObjectOutputStream os;

	public ErrorTest(){
	}

	@BeforeClass
	public static void setUp() throws Exception{
		File file=createOutputFile(ErrorTest.class);
		os=new ObjectOutputStream(new FileOutputStream(file));
	}

	@AfterClass
	public static void tearDown() throws Exception{
		os.close();
	}

	@Test
	public void testWrite() throws Exception{
		Error cause=new Error("This is the cause");
		Error exception=new Error("The exception to test",cause);
		os.writeObject(exception);	
	}
}