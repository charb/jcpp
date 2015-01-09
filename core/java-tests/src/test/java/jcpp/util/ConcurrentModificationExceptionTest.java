package jcpp.util;

import jcpp.*;
import java.io.*;
import java.util.*;
import org.junit.*;

public class ConcurrentModificationExceptionTest extends AbstractTest{
	private static ObjectOutputStream os;

	public ConcurrentModificationExceptionTest(){
	}

	@BeforeClass
	public static void setUp() throws Exception{
		File file=createOutputFile(ConcurrentModificationExceptionTest.class);
		os=new ObjectOutputStream(new FileOutputStream(file));
	}

	@AfterClass
	public static void tearDown() throws Exception{
		os.close();
	}

	@Test
	public void testWrite() throws Exception{
		ConcurrentModificationException cause=new ConcurrentModificationException("This is the cause");
		ConcurrentModificationException exception=new ConcurrentModificationException("The exception to test");
		exception.initCause(cause);
		os.writeObject(exception);	
	}
}