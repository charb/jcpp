package jcpp.io;

import jcpp.*;
import java.io.*;
import org.junit.*;

public class UncheckedIOExceptionTest extends AbstractTest{
	private static ObjectOutputStream os;

	public UncheckedIOExceptionTest(){
	}

	@BeforeClass
	public static void setUp() throws Exception{
		File file=createOutputFile(UncheckedIOExceptionTest.class);
		os=new ObjectOutputStream(new FileOutputStream(file));
	}

	@AfterClass
	public static void tearDown() throws Exception{
		os.close();
	}

	@Test
	public void testWrite() throws Exception{
		//TODO reactivate when on java8
/*		IOException cause=new IOException("This is the cause");
		UncheckedIOException exception=new UncheckedIOException("The exception to test",cause);
		os.writeObject(exception);	
		*/
	}
}