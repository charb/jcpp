package jcpp.lang;

import jcpp.*;
import java.io.*;
import org.junit.*;

public class NoClassDefFoundErrorTest extends AbstractTest{
	private static ObjectOutputStream os;

	public NoClassDefFoundErrorTest(){
	}

	@BeforeClass
	public static void setUp() throws Exception{
		File file=createOutputFile(NoClassDefFoundErrorTest.class);
		os=new ObjectOutputStream(new FileOutputStream(file));
	}

	@AfterClass
	public static void tearDown() throws Exception{
		os.close();
	}

	@Test
	public void testWrite() throws Exception{
		NoClassDefFoundError cause=new NoClassDefFoundError("This is the cause");
		NoClassDefFoundError exception=new NoClassDefFoundError("The exception to test");
		exception.initCause(cause);
		os.writeObject(exception);	
	}
}