package jcpp.io;

import jcpp.*;
import java.io.*;
import org.junit.*;

public class StreamCorruptedExceptionTest extends AbstractTest{
	private static ObjectOutputStream os;

	public StreamCorruptedExceptionTest(){
	}

	@BeforeClass
	public static void setUp() throws Exception{
		File file=createOutputFile(StreamCorruptedExceptionTest.class);
		os=new ObjectOutputStream(new FileOutputStream(file));
	}

	@AfterClass
	public static void tearDown() throws Exception{
		os.close();
	}

	@Test
	public void testWrite() throws Exception{
		StreamCorruptedException cause=new StreamCorruptedException("This is the cause");
		StreamCorruptedException exception=new StreamCorruptedException("The exception to test");
		exception.initCause(cause);
		os.writeObject(exception);	
	}
}