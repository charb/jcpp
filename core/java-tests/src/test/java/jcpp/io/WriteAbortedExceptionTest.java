package jcpp.io;

import jcpp.*;
import java.io.*;
import org.junit.*;

public class WriteAbortedExceptionTest extends AbstractTest{
	private static ObjectOutputStream os;

	public WriteAbortedExceptionTest(){
	}

	@BeforeClass
	public static void setUp() throws Exception{
		File file=createOutputFile(WriteAbortedExceptionTest.class);
		os=new ObjectOutputStream(new FileOutputStream(file));
	}

	@AfterClass
	public static void tearDown() throws Exception{
		os.close();
	}

	@Test
	public void testWrite() throws Exception{
		WriteAbortedException cause=new WriteAbortedException("This is the cause",null);
		WriteAbortedException exception=new WriteAbortedException("The exception to test",cause);
		os.writeObject(exception);	
	}
}