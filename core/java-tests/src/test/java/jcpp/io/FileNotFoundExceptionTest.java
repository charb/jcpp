package jcpp.io;

import jcpp.*;
import java.io.*;
import org.junit.*;

public class FileNotFoundExceptionTest extends AbstractTest{
	private static ObjectOutputStream os;

	public FileNotFoundExceptionTest(){
	}

	@BeforeClass
	public static void setUp() throws Exception{
		File file=createOutputFile(FileNotFoundExceptionTest.class);
		os=new ObjectOutputStream(new FileOutputStream(file));
	}

	@AfterClass
	public static void tearDown() throws Exception{
		os.close();
	}

	@Test
	public void testWrite() throws Exception{
		FileNotFoundException cause=new FileNotFoundException("This is the cause");
		FileNotFoundException exception=new FileNotFoundException("The exception to test");
		exception.initCause(cause);
		os.writeObject(exception);	
	}
}