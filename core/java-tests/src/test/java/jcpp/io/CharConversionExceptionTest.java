package jcpp.io;

import jcpp.*;
import java.io.*;
import org.junit.*;

public class CharConversionExceptionTest extends AbstractTest{
	private static ObjectOutputStream os;

	public CharConversionExceptionTest(){
	}

	@BeforeClass
	public static void setUp() throws Exception{
		File file=createOutputFile(CharConversionExceptionTest.class);
		os=new ObjectOutputStream(new FileOutputStream(file));
	}

	@AfterClass
	public static void tearDown() throws Exception{
		os.close();
	}

	@Test
	public void testWrite() throws Exception{
		CharConversionException cause=new CharConversionException("This is the cause");
		CharConversionException exception=new CharConversionException("The exception to test");
		exception.initCause(cause);
		os.writeObject(exception);	
	}
}