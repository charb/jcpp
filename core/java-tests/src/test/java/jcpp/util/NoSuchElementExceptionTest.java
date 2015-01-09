package jcpp.util;

import jcpp.*;
import java.io.*;
import java.util.*;
import org.junit.*;

public class NoSuchElementExceptionTest extends AbstractTest{
	private static ObjectOutputStream os;

	public NoSuchElementExceptionTest(){
	}

	@BeforeClass
	public static void setUp() throws Exception{
		File file=createOutputFile(NoSuchElementExceptionTest.class);
		os=new ObjectOutputStream(new FileOutputStream(file));
	}

	@AfterClass
	public static void tearDown() throws Exception{
		os.close();
	}

	@Test
	public void testWrite() throws Exception{
		NoSuchElementException cause=new NoSuchElementException("This is the cause");
		NoSuchElementException exception=new NoSuchElementException("The exception to test");
		exception.initCause(cause);
		os.writeObject(exception);	
	}
}