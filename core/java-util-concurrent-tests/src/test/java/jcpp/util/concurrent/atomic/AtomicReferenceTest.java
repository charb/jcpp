package jcpp.util.concurrent.atomic;

import jcpp.util.concurrent.*;
import java.io.*;
import org.junit.*;
import java.util.concurrent.atomic.*;

public class AtomicReferenceTest extends AbstractTest{
	private static ObjectOutputStream os;

	public AtomicReferenceTest(){
	}

	@BeforeClass
	public static void setUp() throws Exception{
		File file=createOutputFile(AtomicReferenceTest.class);
		os=new ObjectOutputStream(new FileOutputStream(file));
	}

	@AfterClass
	public static void tearDown() throws Exception{
		os.close();
	}

	@Test
	public void testWrite() throws Exception{
		AtomicReference a1=new AtomicReference(new Long(1978));
		os.writeObject(a1);	
	}
}