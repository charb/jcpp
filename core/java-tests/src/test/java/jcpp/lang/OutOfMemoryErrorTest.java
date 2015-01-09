package jcpp.lang;

import jcpp.*;
import java.io.*;
import org.junit.*;

public class OutOfMemoryErrorTest extends AbstractTest{
	private static ObjectOutputStream os;

	public OutOfMemoryErrorTest(){
	}

	@BeforeClass
	public static void setUp() throws Exception{
		File file=createOutputFile(OutOfMemoryErrorTest.class);
		os=new ObjectOutputStream(new FileOutputStream(file));
	}

	@AfterClass
	public static void tearDown() throws Exception{
		os.close();
	}

	@Test
	public void testWrite() throws Exception{
		OutOfMemoryError cause=new OutOfMemoryError("This is the cause");
		OutOfMemoryError exception=new OutOfMemoryError("The exception to test");
		exception.initCause(cause);
		os.writeObject(exception);	
	}
}