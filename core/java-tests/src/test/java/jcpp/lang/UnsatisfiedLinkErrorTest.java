package jcpp.lang;

import jcpp.*;
import java.io.*;
import org.junit.*;

public class UnsatisfiedLinkErrorTest extends AbstractTest{
	private static ObjectOutputStream os;

	public UnsatisfiedLinkErrorTest(){
	}

	@BeforeClass
	public static void setUp() throws Exception{
		File file=createOutputFile(UnsatisfiedLinkErrorTest.class);
		os=new ObjectOutputStream(new FileOutputStream(file));
	}

	@AfterClass
	public static void tearDown() throws Exception{
		os.close();
	}

	@Test
	public void testWrite() throws Exception{
		UnsatisfiedLinkError cause=new UnsatisfiedLinkError("This is the cause");
		UnsatisfiedLinkError exception=new UnsatisfiedLinkError("The exception to test");
		exception.initCause(cause);
		os.writeObject(exception);	
	}
}