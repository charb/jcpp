package jcpp.lang;

import jcpp.*;
import java.io.*;
import org.junit.*;

public class ClassCastExceptionTest extends AbstractTest{
	private static ObjectOutputStream os;

	public ClassCastExceptionTest(){
	}

	@BeforeClass
	public static void setUp() throws Exception{
		File file=createOutputFile(ClassCastExceptionTest.class);
		os=new ObjectOutputStream(new FileOutputStream(file));
	}

	@AfterClass
	public static void tearDown() throws Exception{
		os.close();
	}

	@Test
	public void testWrite() throws Exception{
		ClassCastException cause=new ClassCastException("This is the cause");
		ClassCastException exception=new ClassCastException("The exception to test");
		exception.initCause(cause);
		os.writeObject(exception);	
	}
}