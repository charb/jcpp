package jcpp.util.concurrent;

import jcpp.*;
import java.io.*;
import java.util.*;
import org.junit.*;
import java.util.concurrent.*;

public class CancellationExceptionTest extends AbstractTest{
	private static ObjectOutputStream os;

	public CancellationExceptionTest(){
	}

	@BeforeClass
	public static void setUp() throws Exception{
		File file=createOutputFile(CancellationExceptionTest.class);
		os=new ObjectOutputStream(new FileOutputStream(file));
	}

	@AfterClass
	public static void tearDown() throws Exception{
		os.close();
	}

	@Test
	public void testWrite() throws Exception{
		CancellationException cause=new CancellationException("This is the cause");
		CancellationException exception=new CancellationException("The exception to test");
		exception.initCause(cause);
		os.writeObject(exception);	
	}
}