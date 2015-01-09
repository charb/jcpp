package jcpp.util.concurrent;

import jcpp.*;
import java.io.*;
import java.util.*;
import org.junit.*;
import java.util.concurrent.*;

public class RejectedExecutionExceptionTest extends AbstractTest{
	private static ObjectOutputStream os;

	public RejectedExecutionExceptionTest(){
	}

	@BeforeClass
	public static void setUp() throws Exception{
		File file=createOutputFile(RejectedExecutionExceptionTest.class);
		os=new ObjectOutputStream(new FileOutputStream(file));
	}

	@AfterClass
	public static void tearDown() throws Exception{
		os.close();
	}

	@Test
	public void testWrite() throws Exception{
		RejectedExecutionException cause=new RejectedExecutionException("This is the cause");
		RejectedExecutionException exception=new RejectedExecutionException("The exception to test");
		exception.initCause(cause);
		os.writeObject(exception);	
	}
}