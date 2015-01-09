package jcpp.lang;

import jcpp.*;
import java.io.*;
import org.junit.*;

public class AbstractMethodErrorTest extends AbstractTest{
	private static ObjectOutputStream os;

	public AbstractMethodErrorTest(){
	}

	@BeforeClass
	public static void setUp() throws Exception{
		File file=createOutputFile(AbstractMethodErrorTest.class);
		os=new ObjectOutputStream(new FileOutputStream(file));
	}

	@AfterClass
	public static void tearDown() throws Exception{
		os.close();
	}

	@Test
	public void testWrite() throws Exception{
		AbstractMethodError cause=new AbstractMethodError("This is the cause");
		AbstractMethodError exception=new AbstractMethodError("The exception to test");
		exception.initCause(cause);
		os.writeObject(exception);	
	}
}