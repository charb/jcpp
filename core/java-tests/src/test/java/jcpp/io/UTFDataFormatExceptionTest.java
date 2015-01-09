package jcpp.io;

import jcpp.*;
import java.io.*;
import org.junit.*;

public class UTFDataFormatExceptionTest extends AbstractTest{
	private static ObjectOutputStream os;

	public UTFDataFormatExceptionTest(){
	}

	@BeforeClass
	public static void setUp() throws Exception{
		File file=createOutputFile(UTFDataFormatExceptionTest.class);
		os=new ObjectOutputStream(new FileOutputStream(file));
	}

	@AfterClass
	public static void tearDown() throws Exception{
		os.close();
	}

	@Test
	public void testWrite() throws Exception{
		UTFDataFormatException cause=new UTFDataFormatException("This is the cause");
		UTFDataFormatException exception=new UTFDataFormatException("The exception to test");
		exception.initCause(cause);
		os.writeObject(exception);	
	}
}