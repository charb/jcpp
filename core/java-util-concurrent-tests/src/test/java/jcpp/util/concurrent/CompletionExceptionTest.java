package jcpp.util.concurrent;

import jcpp.*;
import java.io.*;
import java.util.*;
import org.junit.*;
import java.util.concurrent.*;

public class CompletionExceptionTest extends AbstractTest{
	private static ObjectOutputStream os;

	public CompletionExceptionTest(){
	}

	@BeforeClass
	public static void setUp() throws Exception{
		File file=createOutputFile(CompletionExceptionTest.class);
		os=new ObjectOutputStream(new FileOutputStream(file));
	}

	@AfterClass
	public static void tearDown() throws Exception{
		os.close();
	}

	@Test
	public void testWrite() throws Exception{
		/*TODO activate when using jdk8
		CompletionException cause=new CompletionException("This is the cause",null);
		CompletionException exception=new CompletionException("The exception to test",cause);
		os.writeObject(exception);	*/
	}
}