package jcpp.lang;

import jcpp.*;
import java.io.*;
import org.junit.*;

public class NullPointerExceptionTest extends AbstractTest{
	private static ObjectOutputStream os;

	public NullPointerExceptionTest(){
	}

	@BeforeClass
	public static void setUp() throws Exception{
		File file=createOutputFile(NullPointerExceptionTest.class);
		os=new ObjectOutputStream(new FileOutputStream(file));
	}

	@AfterClass
	public static void tearDown() throws Exception{
		os.close();
	}

	@Test
	public void testWrite() throws Exception{
		NullPointerException cause=new NullPointerException("This is the cause");
		NullPointerException exception=new NullPointerException("The exception to test");
		exception.initCause(cause);
		os.writeObject(exception);	
	}
}