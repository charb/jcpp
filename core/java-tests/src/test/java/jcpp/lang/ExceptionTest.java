package jcpp.lang;

import jcpp.*;
import java.io.*;
import org.junit.*;

public class ExceptionTest extends AbstractTest{
	private static ObjectOutputStream os;

	public ExceptionTest(){
	}

	@BeforeClass
	public static void setUp() throws Exception{
		File file=createOutputFile(ExceptionTest.class);
		os=new ObjectOutputStream(new FileOutputStream(file));
	}

	@AfterClass
	public static void tearDown() throws Exception{
		os.close();
	}

	@Test
	public void testWrite() throws Exception{
		Exception cause=new Exception("This is the cause");
		Exception exception=new Exception("The exception to test",cause);
		os.writeObject(exception);	
	}
}