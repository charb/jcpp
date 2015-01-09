package jcpp.lang;

import jcpp.*;
import java.io.*;
import org.junit.*;

public class ArrayStoreExceptionTest extends AbstractTest{
	private static ObjectOutputStream os;

	public ArrayStoreExceptionTest(){
	}

	@BeforeClass
	public static void setUp() throws Exception{
		File file=createOutputFile(ArrayStoreExceptionTest.class);
		os=new ObjectOutputStream(new FileOutputStream(file));
	}

	@AfterClass
	public static void tearDown() throws Exception{
		os.close();
	}

	@Test
	public void testWrite() throws Exception{
		ArrayStoreException cause=new ArrayStoreException("This is the cause");
		ArrayStoreException exception=new ArrayStoreException("The exception to test");
		exception.initCause(cause);
		os.writeObject(exception);	
	}
}