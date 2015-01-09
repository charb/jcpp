package jcpp.lang;

import jcpp.*;
import java.io.*;
import org.junit.*;

public class NoSuchFieldExceptionTest extends AbstractTest{
	private static ObjectOutputStream os;

	public NoSuchFieldExceptionTest(){
	}

	@BeforeClass
	public static void setUp() throws Exception{
		File file=createOutputFile(NoSuchFieldExceptionTest.class);
		os=new ObjectOutputStream(new FileOutputStream(file));
	}

	@AfterClass
	public static void tearDown() throws Exception{
		os.close();
	}

	@Test
	public void testWrite() throws Exception{
		NoSuchFieldException cause=new NoSuchFieldException("This is the cause");
		NoSuchFieldException exception=new NoSuchFieldException("The exception to test");
		exception.initCause(cause);
		os.writeObject(exception);	
	}
}