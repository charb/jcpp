package jcpp.util.concurrent.atomic;

import jcpp.util.concurrent.*;
import java.io.*;
import org.junit.*;
import java.util.concurrent.atomic.*;

public class AtomicIntegerArrayTest extends AbstractTest{
	private static ObjectOutputStream os;

	public AtomicIntegerArrayTest(){
	}

	@BeforeClass
	public static void setUp() throws Exception{
		File file=createOutputFile(AtomicIntegerArrayTest.class);
		os=new ObjectOutputStream(new FileOutputStream(file));
	}

	@AfterClass
	public static void tearDown() throws Exception{
		os.close();
	}

	@Test
	public void testWrite() throws Exception{
		AtomicIntegerArray a1=new AtomicIntegerArray(1);
		a1.set(0,1978);
		os.writeObject(a1);	
	}
}