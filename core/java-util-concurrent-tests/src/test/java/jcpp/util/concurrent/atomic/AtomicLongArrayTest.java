package jcpp.util.concurrent.atomic;

import jcpp.util.concurrent.*;
import java.io.*;
import org.junit.*;
import java.util.concurrent.atomic.*;

public class AtomicLongArrayTest extends AbstractTest{
	private static ObjectOutputStream os;

	public AtomicLongArrayTest(){
	}

	@BeforeClass
	public static void setUp() throws Exception{
		File file=createOutputFile(AtomicLongArrayTest.class);
		os=new ObjectOutputStream(new FileOutputStream(file));
	}

	@AfterClass
	public static void tearDown() throws Exception{
		os.close();
	}

	@Test
	public void testWrite() throws Exception{
		AtomicLongArray a1=new AtomicLongArray(1);
		a1.set(0,1978);
		os.writeObject(a1);	
	}
}