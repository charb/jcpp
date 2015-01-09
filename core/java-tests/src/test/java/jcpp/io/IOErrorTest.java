package jcpp.io;

import jcpp.*;
import java.io.*;
import org.junit.*;

public class IOErrorTest extends AbstractTest{
	private static ObjectOutputStream os;

	public IOErrorTest(){
	}

	@BeforeClass
	public static void setUp() throws Exception{
		File file=createOutputFile(IOErrorTest.class);
		os=new ObjectOutputStream(new FileOutputStream(file));
	}

	@AfterClass
	public static void tearDown() throws Exception{
		os.close();
	}

	@Test
	public void testWrite() throws Exception{
		IOError cause=new IOError(null);
		IOError exception=new IOError(cause);
		os.writeObject(exception);	
	}
}