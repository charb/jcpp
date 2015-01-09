package jcpp.lang;

import jcpp.*;
import java.io.*;
import org.junit.*;

public class ClassFormatErrorTest extends AbstractTest{
	private static ObjectOutputStream os;

	public ClassFormatErrorTest(){
	}

	@BeforeClass
	public static void setUp() throws Exception{
		File file=createOutputFile(ClassFormatErrorTest.class);
		os=new ObjectOutputStream(new FileOutputStream(file));
	}

	@AfterClass
	public static void tearDown() throws Exception{
		os.close();
	}

	@Test
	public void testWrite() throws Exception{
		ClassFormatError cause=new ClassFormatError("This is the cause");
		ClassFormatError exception=new ClassFormatError("The exception to test");
		exception.initCause(cause);
		os.writeObject(exception);	
	}
}