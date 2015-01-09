package jcpp.lang;

import jcpp.*;
import java.io.*;
import org.junit.*;

public class ClassNotFoundExceptionTest extends AbstractTest{
	private static ObjectOutputStream os;

	public ClassNotFoundExceptionTest(){
	}

	@BeforeClass
	public static void setUp() throws Exception{
		File file=createOutputFile(ClassNotFoundExceptionTest.class);
		os=new ObjectOutputStream(new FileOutputStream(file));
	}

	@AfterClass
	public static void tearDown() throws Exception{
		os.close();
	}

	@Test
	public void testWrite() throws Exception{
		ClassNotFoundException cause=new ClassNotFoundException("This is the cause");
		ClassNotFoundException exception=new ClassNotFoundException("The exception to test",cause);
		os.writeObject(exception);	
	}
}