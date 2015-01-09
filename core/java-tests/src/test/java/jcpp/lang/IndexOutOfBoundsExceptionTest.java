package jcpp.lang;

import jcpp.*;
import java.io.*;
import org.junit.*;

public class IndexOutOfBoundsExceptionTest extends AbstractTest{
	private static ObjectOutputStream os;

	public IndexOutOfBoundsExceptionTest(){
	}

	@BeforeClass
	public static void setUp() throws Exception{
		File file=createOutputFile(IndexOutOfBoundsExceptionTest.class);
		os=new ObjectOutputStream(new FileOutputStream(file));
	}

	@AfterClass
	public static void tearDown() throws Exception{
		os.close();
	}

	@Test
	public void testWrite() throws Exception{
		IndexOutOfBoundsException cause=new IndexOutOfBoundsException("This is the cause");
		IndexOutOfBoundsException exception=new IndexOutOfBoundsException("The exception to test");
		exception.initCause(cause);
		os.writeObject(exception);	
	}
}