package jcpp.lang;

import jcpp.*;
import java.io.*;
import org.junit.*;

public class BootstrapMethodErrorTest extends AbstractTest{
	private static ObjectOutputStream os;

	public BootstrapMethodErrorTest(){
	}

	@BeforeClass
	public static void setUp() throws Exception{
		File file=createOutputFile(BootstrapMethodErrorTest.class);
		os=new ObjectOutputStream(new FileOutputStream(file));
	}

	@AfterClass
	public static void tearDown() throws Exception{
		os.close();
	}

	@Test
	public void testWrite() throws Exception{
		BootstrapMethodError cause=new BootstrapMethodError("This is the cause");
		BootstrapMethodError exception=new BootstrapMethodError("The exception to test");
		exception.initCause(cause);
		os.writeObject(exception);	
	}
}