package jcpp.util.concurrent;

import jcpp.*;
import java.io.*;
import java.util.*;
import org.junit.*;
import java.util.concurrent.*;

public class ExecutionExceptionTest extends AbstractTest{
	private static ObjectOutputStream os;

	public ExecutionExceptionTest(){
	}

	@BeforeClass
	public static void setUp() throws Exception{
		File file=createOutputFile(ExecutionExceptionTest.class);
		os=new ObjectOutputStream(new FileOutputStream(file));
	}

	@AfterClass
	public static void tearDown() throws Exception{
		os.close();
	}

	@Test
	public void testWrite() throws Exception{
		ExecutionException cause=new ExecutionException("This is the cause",null);
		ExecutionException exception=new ExecutionException("The exception to test",cause);
		os.writeObject(exception);	
	}
}