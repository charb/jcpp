package jcpp.util.concurrent.atomic;

import jcpp.util.concurrent.*;
import java.io.*;
import org.junit.*;
import java.util.concurrent.atomic.*;

public class AtomicIntegerTest extends AbstractTest{
	private static ObjectOutputStream os;

	public AtomicIntegerTest(){
	}

	@BeforeClass
	public static void setUp() throws Exception{
		File file=createOutputFile(AtomicIntegerTest.class);
		os=new ObjectOutputStream(new FileOutputStream(file));
	}

	@AfterClass
	public static void tearDown() throws Exception{
		os.close();
	}

	@Test
	public void testWrite() throws Exception{
		AtomicInteger a1=new AtomicInteger(1978);
		os.writeObject(a1);	
	}
}