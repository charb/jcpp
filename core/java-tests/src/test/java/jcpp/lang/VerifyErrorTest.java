package jcpp.lang;

import jcpp.*;
import java.io.*;
import org.junit.*;

public class VerifyErrorTest extends AbstractTest{
	private static ObjectOutputStream os;

	public VerifyErrorTest(){
	}

	@BeforeClass
	public static void setUp() throws Exception{
		File file=createOutputFile(VerifyErrorTest.class);
		os=new ObjectOutputStream(new FileOutputStream(file));
	}

	@AfterClass
	public static void tearDown() throws Exception{
		os.close();
	}

	@Test
	public void testWrite() throws Exception{
		VerifyError cause=new VerifyError("This is the cause");
		VerifyError exception=new VerifyError("The exception to test");
		exception.initCause(cause);
		os.writeObject(exception);	
	}
}