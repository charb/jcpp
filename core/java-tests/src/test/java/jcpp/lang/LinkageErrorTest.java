package jcpp.lang;

import jcpp.*;
import java.io.*;
import org.junit.*;

public class LinkageErrorTest extends AbstractTest{
	private static ObjectOutputStream os;

	public LinkageErrorTest(){
	}

	@BeforeClass
	public static void setUp() throws Exception{
		File file=createOutputFile(LinkageErrorTest.class);
		os=new ObjectOutputStream(new FileOutputStream(file));
	}

	@AfterClass
	public static void tearDown() throws Exception{
		os.close();
	}

	@Test
	public void testWrite() throws Exception{
		LinkageError cause=new LinkageError("This is the cause");
		LinkageError exception=new LinkageError("The exception to test");
		exception.initCause(cause);
		os.writeObject(exception);	
	}
}