package jcpp.util.concurrent.atomic;

import jcpp.util.concurrent.*;
import java.io.*;
import org.junit.*;
import java.util.concurrent.atomic.*;

public class AtomicReferenceArrayTest extends AbstractTest{
	private static ObjectOutputStream os;

	public AtomicReferenceArrayTest(){
	}

	@BeforeClass
	public static void setUp() throws Exception{
		File file=createOutputFile(AtomicReferenceArrayTest.class);
		os=new ObjectOutputStream(new FileOutputStream(file));
	}

	@AfterClass
	public static void tearDown() throws Exception{
		os.close();
	}

	@Test
	public void testWrite() throws Exception{
		AtomicReferenceArray a1=new AtomicReferenceArray(1);
		a1.set(0,new Long(1978));
		os.writeObject(a1);	
	}
}