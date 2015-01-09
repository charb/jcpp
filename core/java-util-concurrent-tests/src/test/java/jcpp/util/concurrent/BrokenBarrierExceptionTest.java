package jcpp.util.concurrent;

import jcpp.*;
import java.io.*;
import java.util.*;
import org.junit.*;
import java.util.concurrent.*;

public class BrokenBarrierExceptionTest extends AbstractTest{
	private static ObjectOutputStream os;

	public BrokenBarrierExceptionTest(){
	}

	@BeforeClass
	public static void setUp() throws Exception{
		File file=createOutputFile(BrokenBarrierExceptionTest.class);
		os=new ObjectOutputStream(new FileOutputStream(file));
	}

	@AfterClass
	public static void tearDown() throws Exception{
		os.close();
	}

	@Test
	public void testWrite() throws Exception{
		BrokenBarrierException cause=new BrokenBarrierException("This is the cause");
		BrokenBarrierException exception=new BrokenBarrierException("The exception to test");
		exception.initCause(cause);
		os.writeObject(exception);	
	}
}