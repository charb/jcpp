package jcpp.io;

import jcpp.*;
import java.io.*;
import org.junit.*;

public class SyncFailedExceptionTest extends AbstractTest{
	private static ObjectOutputStream os;

	public SyncFailedExceptionTest(){
	}

	@BeforeClass
	public static void setUp() throws Exception{
		File file=createOutputFile(SyncFailedExceptionTest.class);
		os=new ObjectOutputStream(new FileOutputStream(file));
	}

	@AfterClass
	public static void tearDown() throws Exception{
		os.close();
	}

	@Test
	public void testWrite() throws Exception{
		SyncFailedException cause=new SyncFailedException("This is the cause");
		SyncFailedException exception=new SyncFailedException("The exception to test");
		exception.initCause(cause);
		os.writeObject(exception);	
	}
}