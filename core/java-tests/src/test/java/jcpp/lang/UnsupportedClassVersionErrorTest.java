package jcpp.lang;

import jcpp.*;
import java.io.*;
import org.junit.*;

public class UnsupportedClassVersionErrorTest extends AbstractTest{
	private static ObjectOutputStream os;

	public UnsupportedClassVersionErrorTest(){
	}

	@BeforeClass
	public static void setUp() throws Exception{
		File file=createOutputFile(UnsupportedClassVersionErrorTest.class);
		os=new ObjectOutputStream(new FileOutputStream(file));
	}

	@AfterClass
	public static void tearDown() throws Exception{
		os.close();
	}

	@Test
	public void testWrite() throws Exception{
		UnsupportedClassVersionError cause=new UnsupportedClassVersionError("This is the cause");
		UnsupportedClassVersionError exception=new UnsupportedClassVersionError("The exception to test");
		exception.initCause(cause);
		os.writeObject(exception);	
	}
}