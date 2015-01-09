package jcpp.util.concurrent.atomic;

import jcpp.util.concurrent.*;
import java.io.*;
import org.junit.*;
import java.util.concurrent.atomic.*;

public class AtomicLongTest extends AbstractTest{
	private static ObjectOutputStream os;

	public AtomicLongTest(){
	}

	@BeforeClass
	public static void setUp() throws Exception{
		File file=createOutputFile(AtomicLongTest.class);
		os=new ObjectOutputStream(new FileOutputStream(file));
	}

	@AfterClass
	public static void tearDown() throws Exception{
		os.close();
	}

	@Test
	public void testWrite() throws Exception{
		AtomicLong a1=new AtomicLong(1978);
		os.writeObject(a1);	
	}
}