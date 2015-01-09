package jcpp.lang;

import jcpp.*;
import java.io.*;
import org.junit.*;

public class InstantiationExceptionTest extends AbstractTest{
	private static ObjectOutputStream os;

	public InstantiationExceptionTest(){
	}

	@BeforeClass
	public static void setUp() throws Exception{
		File file=createOutputFile(InstantiationExceptionTest.class);
		os=new ObjectOutputStream(new FileOutputStream(file));
	}

	@AfterClass
	public static void tearDown() throws Exception{
		os.close();
	}

	@Test
	public void testWrite() throws Exception{
		InstantiationException cause=new InstantiationException("This is the cause");
		InstantiationException exception=new InstantiationException("The exception to test");
		exception.initCause(cause);
		os.writeObject(exception);	
	}
}