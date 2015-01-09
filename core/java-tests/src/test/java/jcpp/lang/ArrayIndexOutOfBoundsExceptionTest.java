package jcpp.lang;

import jcpp.*;
import java.io.*;
import org.junit.*;

public class ArrayIndexOutOfBoundsExceptionTest extends AbstractTest{
	private static ObjectOutputStream os;

	public ArrayIndexOutOfBoundsExceptionTest(){
	}

	@BeforeClass
	public static void setUp() throws Exception{
		File file=createOutputFile(ArrayIndexOutOfBoundsExceptionTest.class);
		os=new ObjectOutputStream(new FileOutputStream(file));
	}

	@AfterClass
	public static void tearDown() throws Exception{
		os.close();
	}

	@Test
	public void testWrite() throws Exception{
		ArrayIndexOutOfBoundsException cause=new ArrayIndexOutOfBoundsException("This is the cause");
		ArrayIndexOutOfBoundsException exception=new ArrayIndexOutOfBoundsException("The exception to test");
		exception.initCause(cause);
		os.writeObject(exception);	
	}
}