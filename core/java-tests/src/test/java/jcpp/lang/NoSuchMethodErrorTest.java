package jcpp.lang;

import jcpp.*;
import java.io.*;
import org.junit.*;

public class NoSuchMethodErrorTest extends AbstractTest{
	private static ObjectOutputStream os;

	public NoSuchMethodErrorTest(){
	}

	@BeforeClass
	public static void setUp() throws Exception{
		File file=createOutputFile(NoSuchMethodErrorTest.class);
		os=new ObjectOutputStream(new FileOutputStream(file));
	}

	@AfterClass
	public static void tearDown() throws Exception{
		os.close();
	}

	@Test
	public void testWrite() throws Exception{
		NoSuchMethodError cause=new NoSuchMethodError("This is the cause");
		NoSuchMethodError exception=new NoSuchMethodError("The exception to test");
		exception.initCause(cause);
		os.writeObject(exception);	
	}
}